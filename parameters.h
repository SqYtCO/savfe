#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <experimental/filesystem>
#include <vector>
#include <string>
#include <chrono>

/*
 * -u / --update / -R / --run
 * -v / --verbose
 * -r <dirs/files> / --remove <dirs/files>
 * -a <dirs/files> / --add <dirs/files>
 * -d <dir/file> / --destination <dir/file>
 * -c / --check
 * --behavior <already-existing-behavior> <symlink-behavior>
 * -l / --list
 * --log
 * --show-config
 * -? / --help
*/

struct Data
{
	bool verbose {false};
	std::vector<std::string> removed;
	std::vector<std::string> added;
	std::experimental::filesystem::path destination;
	bool update {false};
	bool terminal {false};
	bool check_list {false};
};

Data analyze_parameters(const int& args, char* argv[]);

#endif // PARAMETERS_H
