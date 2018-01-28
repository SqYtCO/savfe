#include "log.h"
#include "exceptions.h"
#include <experimental/filesystem>
#include <fstream>
#include <vector>

void run(const Configuration& config, const bool& verbose)
{
    log("running service");

	std::ifstream in("filedirectorylist");
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
		throw Failure_Exception("No list found!");

	for(auto& a : list)
	{
		std::experimental::filesystem::path path(a);
		std::string final_dest = config.destination;

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

		if(verbose)
			std::cout << a << " -> " << final_dest << '\n';
	}
}
