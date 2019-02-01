#include "run.h"
#include "log.h"
#include "constants.h"
#include "messages.h"
#include "exceptions/error_exception.h"
#include "dir_functions.h"
#include <filesystem>
#include <fstream>
#include <condition_variable>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

void busy_points(std::condition_variable* condition, std::atomic<int>* finished)
{
	std::mutex mut;

	while(true)
	{
		for(int i = 0; i < 3; ++i)
		{
			std::unique_lock<std::mutex> lock(mut);
			// interruptable sleep, if interrupted return
			if(condition->wait_for(lock, std::chrono::milliseconds(600), [&]() { return finished->load(); } ))
				return;
			std::cout << " ." << std::flush;
		}

		// clear last 6 signs (" . . .")
		std::cout << "\b\b\b\b\b\b      \b\b\b\b\b\b";
	}
}

std::vector<std::string> read_list(const std::string& file)
{
	std::vector<std::string> list;
	std::ifstream in(file);
	if(in)
	{
		std::string temp;

		while(in)
		{
			std::getline(in, temp);
			// skip empty lines
			if(!temp.empty())
				list.push_back(temp);
		}
	}

	return list;
}

void save_path(const std::filesystem::path& path, const std::string& save_folder, const Configuration& config);

std::string path_to_filename(const std::filesystem::path& path)
{
	std::string temp = path.string();
	std::replace(temp.begin(), temp.end(), std::filesystem::path::preferred_separator, '_');
	return temp;
}

#define INDEXFILE path_to_filename(path) + ".indexfile"
#define TEMP_INDEXFILE path_to_filename(path) + ".new_indexfile"
#define INDEXFILE_PATH config.destination + INDEXFILE
#define TEMP_INDEXFILE_PATH config.destination + TEMP_INDEXFILE

void run(const Configuration& config, const bool& verbose)
{
	log("update");

	std::vector<std::string> list = read_list(FILES::LIST_NAME);

	if(list.empty())
	{
		log("update failed - no listfile");
		throw Error_Exception(MSG::NO_LISTFILE_FOUND);
	}

	std::string save_folder = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	std::filesystem::create_directory(config.destination + save_folder);
	for(auto& a : list)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		std::filesystem::path path(a);
		std::string final_dest = config.destination;

		std::thread* busy_thread = nullptr;
		std::condition_variable* condition = nullptr;
		std::atomic<int> finished;
		finished = 0;

		if(verbose)
		{
			std::cout << a << " -> " << final_dest << std::flush;
			condition = new std::condition_variable();
			busy_thread = new std::thread(busy_points, condition, &finished);
		}

		save_path(path, save_folder, config);

		finished = 1;
		if(verbose)
		{
			condition->notify_one();
			busy_thread->join();

			auto end = std::chrono::high_resolution_clock::now();
			std::cout << " (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << ')' << std::endl;
		}

		std::filesystem::rename(TEMP_INDEXFILE_PATH, INDEXFILE_PATH);
		if(config.keep_old_indexfiles && std::filesystem::exists(INDEXFILE_PATH) && std::filesystem::exists(config.destination + save_folder + std::filesystem::path::preferred_separator + path_to_filename(path)))
			std::filesystem::copy_file(INDEXFILE_PATH, config.destination + save_folder + std::filesystem::path::preferred_separator + INDEXFILE);
	}
}

struct Path_Last_Mod
{
	std::string name;
	std::size_t last_modification = 0;
	std::vector<Path_Last_Mod> children;
	Path_Last_Mod* parent = nullptr;
	std::size_t level = 0;
};

Path_Last_Mod read_savefile(const std::filesystem::path& path, const std::string& indexfile)
{
	Path_Last_Mod saved_root;

	std::ifstream in(indexfile);
	if(in)
	{
		std::string input;
		Path_Last_Mod* current_path = &saved_root;
		while(std::getline(in, input))
		{
			if(!std::isdigit(input[0]) && !std::isblank(input[0]))
			{
				log("update failed - corrupted indexfile");
				throw Error_Exception(MSG::INVALID_INDEXFILE);
			}

			if(!std::isblank(input[0]) && !saved_root.name.empty())
				break;
			else if(std::isblank(input[0]) && saved_root.name.empty())
				continue;
			else
			{
				std::size_t level = 0;
				for(; input[level] == '\t'; ++level)
					;
				if(level > current_path->level)
				{
					current_path->children.push_back(Path_Last_Mod());
					current_path->children.back().level = level;
					current_path->children.back().parent = current_path;
					current_path = &current_path->children.back();
				}
				else if(level < current_path->level)
				{
					std::size_t diff = current_path->level - level;
					for(; diff; --diff)
						current_path = current_path->parent;
					current_path->parent->children.push_back(Path_Last_Mod());
					current_path->parent->children.back().level = level;
					current_path->parent->children.back().parent = current_path->parent;
					current_path = &current_path->parent->children.back();
				}
				else if(!saved_root.name.empty())
				{
					current_path->parent->children.push_back(Path_Last_Mod());
					current_path->parent->children.back().level = level;
					current_path->parent->children.back().parent = current_path->parent;
					current_path = &current_path->parent->children.back();
				}

				for(; std::isdigit(input[level]) && level < input.size(); ++level)
				{
					current_path->last_modification *= 10;
					current_path->last_modification += input[level] - '0';
				}
				level += 3;
				for(; level < input.size(); ++level)
					current_path->name += input[level];

				if(saved_root.name != path)
					current_path->name.clear();
			}
		}
	}

	return saved_root;
}

Path_Last_Mod* find_node(Path_Last_Mod* root, const std::filesystem::path& path)
{
	static Path_Last_Mod empty;
	Path_Last_Mod* current = root;
	std::string relative_path = std::filesystem::relative(path, root->name);
	std::string test_path = root->name;
	if(root->name.empty())
		return &empty;
	std::string::size_type pos = 0, last_pos = 0;
	while(true)
	{
		auto it = current->children.begin();
		pos = relative_path.find(std::filesystem::path::preferred_separator, last_pos);
		if(pos == last_pos)
			pos = std::string::npos;
		std::string name = relative_path.substr(last_pos, pos - last_pos);
		last_pos = pos + 1;
		for(; it != current->children.end(); ++it)
		{
			if(name == it->name)
			{
				test_path += it->name;
				current = &*it;
				if(std::filesystem::equivalent(path, std::filesystem::path(test_path)))
					return current;
				test_path += std::filesystem::path::preferred_separator;
				break;
			}
		}

		// if file is new
		if(it == current->children.end())
			return &empty;
	}
}

enum State : char
{
	Changed = 'C',
	Added = 'A',
	Removed = 'R',
	No_Changes = 'N'
};

State get_state(std::size_t last_mod, std::size_t saved_last_mod)
{
	if(saved_last_mod < last_mod && saved_last_mod != 0)
		return Changed;
	else if(saved_last_mod == last_mod)
		return No_Changes;
	else if(last_mod == 0 && saved_last_mod != 0)
		return Removed;
	else
		return Added;
}

void save_path(const std::filesystem::path& path, const std::string& save_folder, const Configuration& config)
{
	Path_Last_Mod saved_root = read_savefile(path, INDEXFILE_PATH);
	std::vector<std::string> ignore_list = read_list(FILES::IGNORELIST_NAME);
	std::size_t last_modification = 0;
	if(std::filesystem::exists(path))
		last_modification = std::filesystem::last_write_time(path).time_since_epoch().count();
	State state = get_state(last_modification, saved_root.last_modification);

	std::ofstream out(TEMP_INDEXFILE_PATH);
	out << last_modification << '\t' << static_cast<char>(state) << '\t' << path.string() << '\n';
	if(std::filesystem::is_directory(path))
	{
//		std::filesystem::create_directories(config.destination +
//										  save_folder + std::filesystem::path::preferred_separator +
//										  path_to_filename(path));
		for(auto it = std::filesystem::recursive_directory_iterator(path); it != std::filesystem::recursive_directory_iterator(); ++it)
		{
			if(std::find_if(ignore_list.begin(), ignore_list.end(), [&it](const auto& a){ return (std::filesystem::equivalent(*it, a) || is_sub_directory(*it, a)); }) != ignore_list.end())
			{
				out << std::string(it.depth() + 1, '\t') << "0\tI\t" << it->path().filename().string() << '\n';
				continue;
			}
			Path_Last_Mod* current = find_node(&saved_root, it->path());
			last_modification = it->last_write_time().time_since_epoch().count();
			if(current->name.empty())
				state = Added;
			else
				state = get_state(last_modification, current->last_modification);

			out << std::string(it.depth() + 1, '\t') << last_modification << '\t' << static_cast<char>(state) << '\t' << it->path().filename().string() << '\n';
			if(state != Removed && state != No_Changes)
			{
				if(!it->is_directory())
				{
					std::string relative_path = std::filesystem::relative(it->path(), path).remove_filename().string();
					if(relative_path.back() == std::filesystem::path::preferred_separator)
						relative_path.pop_back();
					std::filesystem::create_directories(config.destination +
															save_folder + std::filesystem::path::preferred_separator +
															path_to_filename(path) + std::filesystem::path::preferred_separator +
															relative_path);
					std::filesystem::copy_file(it->path(), config.destination +
															save_folder + std::filesystem::path::preferred_separator +
															path_to_filename(path) + std::filesystem::path::preferred_separator +
															relative_path + std::filesystem::path::preferred_separator +
															it->path().filename().string());
										//	   static_cast<std::filesystem::copy_options>(config.aeb | config.sb));
				}
				else
				{
					std::filesystem::create_directories(config.destination +
													  save_folder + std::filesystem::path::preferred_separator +
													  path_to_filename(path) + std::filesystem::path::preferred_separator +
													  std::filesystem::relative(it->path(), path).string());
				}
			}
		}
	}
	else
	{
		if(state != Removed && state != No_Changes)
		{
			std::filesystem::create_directories(config.destination +
													save_folder + std::filesystem::path::preferred_separator +
													path_to_filename(path));
			std::filesystem::copy_file(path, config.destination +
													save_folder + std::filesystem::path::preferred_separator +
													path_to_filename(path) + std::filesystem::path::preferred_separator +
													path.filename().string());
		}
	}
}
