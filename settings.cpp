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

Configuration read_configuration()
{
	Configuration config;

	std::ifstream in(FILES::CONFIG_NAME);

	if(in)
	{
		std::string type;
		char c;
		std::string value;

		while(in)
		{
			// read in type of configuration
			std::getline(in, type, ':');

			// skip whitespaces after configuration-type
			do
			{
				in >> c;
			} while(std::isspace(c));

			// put last non-space-character back
			in.seekg(-1, std::ios::cur);

			// read in value of configuration
			std::getline(in, value);

			if(type == "destination-path")
				config.destination = value;
			else if(type == "already-existing-behavior")
				config.aeb = static_cast<Configuration::Already_Existing_Behavior>(std::stoul(value));
			else if(type == "symlink-behavior")
				config.sb = static_cast<Configuration::Symlinks_Behavior>(std::stoul(value));
		}
	}
	else
		throw Error_Exception(MSG::NO_CONFIGFILE_FOUND);

	return config;
}

void add_path(std::filesystem::path path)
{
	if(!std::filesystem::exists(path))
		throw No_File_Or_Directory_Exception(path.string());
	else
	{
		// format "path" correctly
		path = to_real_absolute(path);

		std::ifstream in(FILES::LIST_NAME);
		std::string temp;				// stores single read in paths
		std::vector<std::string> sub_dirs;		// subdirectories
								// which are already on the list and have to be removed

		// read in paths and check if the path to add is already on the list;
		// if so, "Already_On_The_List_Exception" will be thrown
		while(in)
		{
			std::getline(in, temp);

			if(temp == "")
				break;

			if(temp == path.string())
				throw Already_On_The_List_Exception(path.string());
			else
			{
				if(is_sub_directory(path, temp))
					throw Already_On_The_List_Exception(path, temp);
				else if(is_parent_directory(path, temp))
					sub_dirs.push_back(temp);
			}
		}

		if(!sub_dirs.empty())
			throw Already_On_The_List_Exception(path.string(), sub_dirs);

		in.close();

		std::ofstream of(FILES::LIST_NAME, std::ios::app);
		of << path.string() << '\n';
	}
}

void remove_path(const std::filesystem::path& path)
{
	if(!std::filesystem::exists(path))
		throw No_File_Or_Directory_Exception(path);			// path does not exist

	std::ifstream in(FILES::LIST_NAME);
	std::ofstream of(FILES::TEMP_LIST_NAME);		// temp copy of list
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
		if(to_real_absolute(path).string() == temp)
		{
			skip = true;		// skip writing this (to remove) path to the list-copy
			failed = false;		// is on the list and can be removed
		}

		// write out to file if path is not removed
		if(!skip)
		{
			temp += '\n';
			of.write(temp.c_str(), temp.length());
		}
	}

	// not on the list
	if(failed)
		throw Error_Exception(MSG::NOT_ON_THE_LIST_W_ARG, path);

	in.close();
	of.close();

	std::filesystem::rename(FILES::TEMP_LIST_NAME, FILES::LIST_NAME);  // updates name of copy
}

int remove_not_existing_paths()
{
	std::ifstream in(FILES::LIST_NAME);
	std::ofstream of(FILES::TEMP_LIST_NAME);
	std::string temp;			// stores single read paths FILES::LIST_NAME
	int num = 0;					// number of removed paths (return-value)

	// read paths out of FILES::LIST_NAME and check if they still exist
	while(in)
	{
		std::getline(in, temp);		// read path out of the list

		if(temp.length() < 1)		// skip empty lines
			continue;

		// write to file if path exists; skip all not-existing paths
		if(std::filesystem::exists(temp))
		{
			++num;
			temp += '\n';
			of.write(temp.c_str(), temp.length());
		}
	}

	std::filesystem::rename(FILES::TEMP_LIST_NAME, FILES::LIST_NAME);

	return num;
}

void set_destination(const std::filesystem::path& path)
{
	if(!std::filesystem::is_directory(path))
		throw No_Directory_Exception(path);

	else
	{
		std::ifstream in(FILES::CONFIG_NAME);
		std::ofstream of(FILES::TEMP_CONFIG_NAME);
		std::string temp;

		of.write("destination-path: ", 18);
		of.write(to_real_absolute(path).string().c_str(), to_real_absolute(path).string().length());
		of.write("\n", 1);
		while(in)
		{
			// read in config-line
			std::getline(in, temp);

			// skip empty lines
			if(temp.empty())
				continue;

			temp += '\n';

			// check if temp does not contain "destination-path: "
			if(temp.find("destination-path: ") == std::string::npos)
				of.write(temp.c_str(), temp.length());
		}
	}

	std::filesystem::rename(FILES::TEMP_CONFIG_NAME, FILES::CONFIG_NAME);
}

void set_behavior(Configuration::Already_Existing_Behavior aeb, Configuration::Symlinks_Behavior sb)
{
	std::fstream file(FILES::CONFIG_NAME, std::ios::in | std::ios::out);
	std::string temp;

	while(file)
	{
		file >> temp;

		if(temp == "already-existing-behavior:")
			file << ' ' << aeb;
		else if(temp == "symlink-behavior:")
			file << ' ' << sb;
	}
/*	std::ifstream in(FILES::CONFIG_NAME);
	std::ofstream of("configuration-2");
	std::string temp;

	of.write("already-existing-behavior: ", 27);
	of << aeb << '\n';

	of.write("symlink-behavior: ", 18);
	of << sb << '\n';

	while(in)
	{
		// read in config-line
		std::getline(in, temp);

		// skip empty lines
		if(temp.empty())
			continue;

		temp += '\n';

		// check if temp does not contain "already-existing-behavior: " and "symlink-behavior: "
		if(temp.find("already-existing-behavior: ") == std::string::npos &&
			temp.find("symlink-behavior: ") == std::string::npos)
			of.write(temp.c_str(), temp.length());
	}

	std::filesystem::rename("configuration-2", FILES::CONFIG_NAME);*/
}

void add_ignore_path(std::filesystem::path path)
{
	if(!std::filesystem::exists(path))
		throw No_File_Or_Directory_Exception(path.string());
	else
	{
		// format "path" correctly
		path = to_real_absolute(path);

		std::ifstream in(FILES::IGNORELIST_NAME);
		std::string temp;				// stores single read in paths
		std::vector<std::string> sub_dirs;		// subdirectories
								// which are already on the list and have to be removed

		// read in paths and check if the path to add is already on the list;
		// if so, "Already_On_The_List_Exception" will be thrown
		while(in)
		{
			std::getline(in, temp);

			if(temp == "")
				break;

			if(temp == path.string())
				throw Already_On_The_List_Exception(path.string());
			else
			{
				if(is_sub_directory(path, temp))
					throw Already_On_The_List_Exception(path, temp);
				else if(is_parent_directory(path, temp))
					sub_dirs.push_back(temp);
			}
		}

		if(!sub_dirs.empty())
			throw Already_On_The_List_Exception(path.string(), sub_dirs);

		in.close();

		std::ofstream of(FILES::IGNORELIST_NAME, std::ios::app);
		of << path.string() << '\n';
	}
}
