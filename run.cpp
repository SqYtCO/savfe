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

namespace savfe
{
namespace stdfs = std::filesystem;

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

std::string path_to_filename(const stdfs::path& path)
{
	std::string temp = path.string();
	std::replace(temp.begin(), temp.end(), stdfs::path::preferred_separator, '_');
	return temp;
}

#define INDEXFILE path_to_filename(path) + ".indexfile"
#define TEMP_INDEXFILE path_to_filename(path) + ".new_indexfile"
#define INDEXFILE_PATH config.get_destination() + INDEXFILE
#define TEMP_INDEXFILE_PATH config.get_destination() + TEMP_INDEXFILE

void save_path(const stdfs::path& path, const std::string& save_folder);

void update_save(const bool& verbose)
{
	log("update", Log_Type::Info, Log_Output::Fileoutput);

	std::vector<std::string> list = read_list(FILES::LIST_NAME);

	if(list.empty())
	{
		log("update failed - no listfile", Log_Type::Info, Log_Output::Fileoutput);
		throw Error_Exception(MSG::NO_LISTFILE_FOUND);
	}

	std::string save_folder = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	stdfs::create_directory(config.get_destination() + save_folder);
	for(auto& a : list)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		stdfs::path path(a);
		std::string final_dest = config.get_destination();

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

		save_path(path, save_folder);

		finished = 1;
		if(verbose)
		{
			condition->notify_one();
			busy_thread->join();

			auto end = std::chrono::high_resolution_clock::now();
			std::cout << " (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << ')' << std::endl;
		}

		stdfs::rename(TEMP_INDEXFILE_PATH, INDEXFILE_PATH);
		if(config.get_keep_old_indexfiles() && stdfs::exists(INDEXFILE_PATH) &&
				stdfs::exists(config.get_destination() + save_folder + stdfs::path::preferred_separator + path_to_filename(path)))
			stdfs::copy_file(INDEXFILE_PATH, config.get_destination() + save_folder + stdfs::path::preferred_separator + INDEXFILE);
	}
}

struct Path_Last_Mod
{
	std::string name;
	long long last_modification = 0;
	std::vector<std::unique_ptr<Path_Last_Mod>> children;
	Path_Last_Mod* parent = nullptr;
	std::size_t level = 0;
};

Path_Last_Mod read_savefile(const stdfs::path& path, const std::string& indexfile)
{
	Path_Last_Mod saved_root;

	std::ifstream in(indexfile);
	if(in)
	{
		std::string input;
		Path_Last_Mod* current_path = &saved_root;
		while(std::getline(in, input))
		{
			if(input.empty())
				continue;
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
					current_path->children.push_back(std::unique_ptr<Path_Last_Mod>(new Path_Last_Mod()));
					current_path->children.back()->level = level;
					current_path->children.back()->parent = current_path;
					current_path = current_path->children.back().get();
				}
				else if(level < current_path->level)
				{
					std::size_t diff = current_path->level - level;
					for(; diff; --diff)
						current_path = current_path->parent;
					current_path->parent->children.push_back(std::unique_ptr<Path_Last_Mod>(new Path_Last_Mod()));
					current_path->parent->children.back()->level = level;
					current_path->parent->children.back()->parent = current_path->parent;
					current_path = current_path->parent->children.back().get();
				}
				else if(!saved_root.name.empty())
				{
					current_path->parent->children.push_back(std::unique_ptr<Path_Last_Mod>(new Path_Last_Mod()));
					current_path->parent->children.back()->level = level;
					current_path->parent->children.back()->parent = current_path->parent;
					current_path = current_path->parent->children.back().get();
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

Path_Last_Mod* find_node(Path_Last_Mod* root, const stdfs::path& path)
{
	static Path_Last_Mod empty;
	Path_Last_Mod* current = root;
	std::string relative_path = stdfs::relative(path, root->name);
	std::string test_path = root->name;
	if(root->name.empty())
		return &empty;
	std::string::size_type pos = 0, last_pos = 0;
	while(true)
	{
		auto it = current->children.begin();
		pos = relative_path.find(stdfs::path::preferred_separator, last_pos);
		if(pos == last_pos)
			pos = std::string::npos;
		std::string name = relative_path.substr(last_pos, pos - last_pos);
		last_pos = pos + 1;
		for(; it != current->children.end(); ++it)
		{
			if(name == (*it)->name)
			{
				test_path += (*it)->name;
				current = it->get();
				if(stdfs::equivalent(path, stdfs::path(test_path)))
					return current;
				test_path += stdfs::path::preferred_separator;
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
	No_Changes = 'N',
	Ignored = 'I',
	Skipped = 'S',
	Downgraded = 'D'
};

State get_state(long long last_mod, long long saved_last_mod)
{
	if(saved_last_mod < last_mod && saved_last_mod != 0)
		return Changed;
	else if(saved_last_mod == last_mod)
		return No_Changes;
	else if(last_mod == 0 && saved_last_mod != 0)
		return Removed;
	else if(saved_last_mod > last_mod && last_mod != 0)
		return Downgraded;
	else
		return Added;
}

void save_path(const stdfs::path& path, const std::string& save_folder)
{
	Path_Last_Mod saved_root = read_savefile(path, INDEXFILE_PATH);
	std::vector<std::string> ignore_list = read_list(FILES::IGNORELIST_NAME);
	long long last_modification = 0;
	if(stdfs::exists(path))
		last_modification = stdfs::last_write_time(path).time_since_epoch().count();
	State state = get_state(last_modification, saved_root.last_modification);

	std::ofstream out(TEMP_INDEXFILE_PATH);
	out << last_modification << '\t' << static_cast<char>(state) << '\t' << path.string() << '\n';
	if(stdfs::is_directory(path))
	{
		for(auto it = stdfs::recursive_directory_iterator(path, stdfs::directory_options::skip_permission_denied); it != stdfs::recursive_directory_iterator(); ++it)
		{
			try
			{
				if(std::find_if(ignore_list.begin(), ignore_list.end(), [&it](const auto& a){ return is_sub_equal_directory(*it, a); }) != ignore_list.end())
				{
					out << std::string(it.depth() + 1, '\t') << "0\t" << static_cast<char>(Ignored) << '\t' << it->path().filename().string() << '\n';
					continue;
				}
				Path_Last_Mod* current = find_node(&saved_root, it->path());
				last_modification = it->last_write_time().time_since_epoch().count();
				// symlinks will be ignored
				if(it->is_symlink())
					state = Skipped;
				else if(current->name.empty())
					state = Added;
				else
					state = get_state(last_modification, current->last_modification);

				if(state != Removed && state != No_Changes && state != Skipped && state != Ignored)
				{
					if(!it->is_directory())
					{
						std::string relative_path = stdfs::path::preferred_separator + stdfs::relative(it->path(), path).remove_filename().string();
						if(relative_path.back() == stdfs::path::preferred_separator)
							relative_path.pop_back();
						stdfs::create_directories(config.get_destination() +
																save_folder + stdfs::path::preferred_separator +
																path_to_filename(path) +
																relative_path);
						stdfs::copy_file(it->path(), config.get_destination() +
																save_folder + stdfs::path::preferred_separator +
																path_to_filename(path) +
																relative_path + stdfs::path::preferred_separator +
																it->path().filename().string());
											//	   static_cast<stdfs::copy_options>(config.aeb | config.sb));
					}
					else
					{
						stdfs::create_directories(config.get_destination() +
															save_folder + stdfs::path::preferred_separator +
															path_to_filename(path) + stdfs::path::preferred_separator +
															stdfs::relative(it->path(), path).string());
					}
				}
				out << std::string(static_cast<std::size_t>(it.depth() + 1), '\t')
					<< last_modification << '\t'
					<< static_cast<char>(state) << '\t'
					<< it->path().filename().string() << '\n';
			}
			catch(const std::exception& exc)
			{
				log(exc.what(), Log_Type::Error, Log_Output::Stdout);
			}
		}
	}
	else
	{
		if(state != Removed && state != No_Changes)
		{
			stdfs::create_directories(config.get_destination() +
													save_folder + stdfs::path::preferred_separator +
													path_to_filename(path));
			stdfs::copy_file(path, config.get_destination() +
													save_folder + stdfs::path::preferred_separator +
													path_to_filename(path) + stdfs::path::preferred_separator +
													path.filename().string());
		}
	}
}
}
