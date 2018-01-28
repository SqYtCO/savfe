#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <vector>
#include <string>
#include <chrono>
#include <experimental/filesystem>

struct Data
{
	bool verbose {false};
	std::vector<std::string> removed;
	std::vector<std::string> added;
	bool repeating {false};
	std::chrono::seconds repeating_rate {0};
	bool update {false};
	bool terminal {false};
	bool overwrite_old_files {false};
	bool check_list {false};
	std::experimental::filesystem::path destination;
};

Data analyze_parameters(const int& args, char* argv[]);

#endif // PARAMETERS_H
