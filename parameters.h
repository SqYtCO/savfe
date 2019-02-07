#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <filesystem>
#include <vector>
#include <string>
#include <chrono>

namespace savfe
{
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

struct Parameter_Data
{
	bool verbose {false};
	std::vector<std::string> removed;
	std::vector<std::string> added;
	std::vector<std::string> ignored;
	std::filesystem::path destination;
	bool update {false};
	bool terminal {false};
	bool check_list {false};
};

// throws:
// Error_Exception
// List_Exception
// Log_Exception
// Behavior_Exception
// Config_Exception
// Parameter_Help_Exception
Parameter_Data analyze_parameters(const int& args, char* argv[]);
}

#endif // PARAMETERS_H
