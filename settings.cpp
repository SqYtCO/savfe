#include "settings.h"
#include "constants.h"
#include "log.h"
#include "exceptions/no_directory_exception.h"
#include "exceptions/error_exception.h"
#include "exceptions/already_on_the_list_exception.h"
#include "exceptions/no_file_or_directory_exception.h"
#include "exceptions/error_exception.h"
#include "dir_functions.h"
#include <fstream>
#include <filesystem>
#include <cctype>					// std::isspace
#include <string>					// std::stoul

namespace savfe
{
namespace stdfs = std::filesystem;

void add_path(const stdfs::path& path, const std::string& listfile)
{
	if(!stdfs::exists(path))
		throw No_File_Or_Directory_Exception(path.string());
	else
	{
		// format "path" correctly
		std::string path_string = path_to_string(format_path(path));

		std::ifstream in(listfile);
		std::string temp;				// stores single read in paths
		std::vector<std::string> sub_dirs;		// subdirectories
								// which are already on the list and have to be removed

		// read in paths and check if the path to add is already on the list;
		// if so, "Already_On_The_List_Exception" will be thrown
		while(in)
		{
			std::getline(in, temp);

			if(temp.empty())
				continue;

			if(is_equal(temp, path_string))
				throw Already_On_The_List_Exception(path_string);
			else if(is_sub_directory(path_string, temp))
				throw Already_On_The_List_Exception(path_string, temp);
			else if(is_parent_directory(path_string, temp))
				sub_dirs.push_back(temp);
		}

		if(!sub_dirs.empty())
			throw Already_On_The_List_Exception(path_string, sub_dirs);

		in.close();

		std::ofstream of(listfile, std::ios::app);
		of << path_string << '\n';
	}
}

void remove_path(const stdfs::path& path, const std::string& listfile, const std::string& templistfile)
{
	if(!stdfs::exists(path))
		throw No_File_Or_Directory_Exception(path);			// path does not exist

	std::ifstream in(listfile);
	std::ofstream of(templistfile);		// temp copy of list
	std::string temp;			// stores single read paths FILES::LIST_NAME

	bool skip = false;		// skip writing (removed files)
	bool failed = true;		// file not on the list

	// read paths out of FILES::LIST_NAME and check if they are equal to "path"; then they will be skipped
	while(in)
	{
		skip = false;
		std::getline(in, temp);		// read path out of the list

		if(temp.length() < 1)		// skip empty lines
			continue;

		// check if read path "temp" is equal to "file", which has to be removed
		if(path_to_string(format_path(path)) == temp)
		{
			skip = true;		// skip writing this (to remove) path to the list-copy
			failed = false;		// is on the list and can be removed
		}

		// write out to file if path is not removed
		if(!skip)
			of << temp << '\n';
	}

	// not on the list
	if(failed)
		throw Error_Exception(MSG::NOT_ON_THE_LIST_W_ARG, path);

	in.close();
	of.close();

	stdfs::rename(templistfile, listfile);  // updates name of copy
}

int remove_not_existing_paths(const std::string& listfile, const std::string& templistfile)
{
	std::ifstream in(listfile);
	std::ofstream of(templistfile);
	std::string temp;			// stores single read paths FILES::LIST_NAME
	int num = 0;					// number of removed paths (return-value)

	// read paths out of FILES::LIST_NAME and check if they still exist
	while(in)
	{
		std::getline(in, temp);		// read path out of the list

		if(temp.length() < 1)		// skip empty lines
			continue;

		// write to file if path exists; skip all not-existing paths
		if(stdfs::exists(temp))
		{
			temp += '\n';
			of << temp;
		}
		else
			++num;
	}

	stdfs::rename(templistfile, listfile);

	return num;
}

Configuration::Configuration() : keep_old_indexfiles(true), behavior({ Already_Existing_Behavior::Rename_Existing, Symlinks_Behavior::Follow_Symlinks }), verbose(true)
{
	read_configuration();
}

void Configuration::read_configuration()
{
	std::ifstream in(FILES::CONFIG_NAME);

	if(in)
	{
		std::string type;
		char space;
		std::string value;

		while(in)
		{
			// read in type of configuration
			std::getline(in, type, ':');

			// skip whitespaces after configuration-type
			do
			{
				in >> space;
			} while(std::isspace(space));

			// put last non-space-character back
			in.seekg(-1, std::ios::cur);

			// read in value of configuration
			std::getline(in, value);

			if(type == "destination-path")
				destination = value;
			else if(type == "already-existing-behavior")
				behavior.first = static_cast<Configuration::Already_Existing_Behavior>(std::stoul(value));
			else if(type == "symlink-behavior")
				behavior.second = static_cast<Configuration::Symlinks_Behavior>(std::stoul(value));
			else if(type == "verbose")
				verbose = std::stoi(value);
			else if(type == "keep-old-indexfiles")
				keep_old_indexfiles = std::stoi(value);
		}
	}
	else
		throw Error_Exception(MSG::NO_CONFIGFILE_FOUND);
}

void Configuration::write_configuration()
{
	std::ofstream of(FILES::CONFIG_NAME);
	if(of)
	{
		of << "destination-path: " << destination << '\n'
			<< "already-existing-behavior: " << behavior.first << '\n'
			<< "symlink-behavior: " << behavior.second << '\n'
			<< "keep-old-indexfiles: " << keep_old_indexfiles << '\n'
			<< "verbose: " << verbose << '\n';
	}
	else
		throw Error_Exception(MSG::UNABLE_TO_OPEN_FILE);
}
}
