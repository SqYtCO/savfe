#include "run.h"
#include "log.h"
#include "constants.h"
#include "messages.h"
#include "exceptions/error_exception.h"
#include <experimental/filesystem>
#include <fstream>
#include <condition_variable>
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

void run(const Configuration& config, const bool& verbose)
{
	log("running service");

	std::ifstream in(FILES::LIST_NAME);
	std::vector<std::string> list;

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
	else
		throw Error_Exception(MSG::NO_LISTFILE_FOUND);

	for(auto& a : list)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		std::experimental::filesystem::path path(a);
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

		if(std::experimental::filesystem::is_directory(path))
		{
			// add last sub-directory to destination
			final_dest += a.substr(a.find_last_of("/", a.length() - 2));

			if(!std::experimental::filesystem::exists(final_dest))
				std::experimental::filesystem::create_directory(final_dest);

			std::experimental::filesystem::copy(a, final_dest,
					std::experimental::filesystem::copy_options::recursive |
					static_cast<std::experimental::filesystem::copy_options>(config.aeb | config.sb));
		}
		else
		{
			// add filename to destination
			final_dest += path.filename();

			std::experimental::filesystem::copy_file(path, final_dest,
				static_cast<std::experimental::filesystem::copy_options>(config.aeb | config.sb));
		}

		finished = 1;
		if(verbose)
		{
			condition->notify_one();
			busy_thread->join();

			auto end = std::chrono::high_resolution_clock::now();
			std::cout << " (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << ')' << std::endl;
		}
	}
}
