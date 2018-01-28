#include "settings.h"
#include "log.h"
#include "exceptions.h"
#include "operations.h"
#include <fstream>
#include <experimental/filesystem>
#include <cctype>					// std::isspace
#include <string>					// std::stoul

Configuration read_configuration()
{
	Configuration config;

	std::ifstream in("configuration");

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
			{
				config.destination = value;
			}
			else if(type == "already-existing-behavior")
			{
				config.aeb = static_cast<Configuration::Already_Existing_Behavior>(std::stoul(value));
			}
			else if(type == "symlink-behavior")
			{
				config.sb = static_cast<Configuration::Symlinks_Behavior>(std::stoul(value));
			}
		}
	}
	else
		throw Failure_Exception("No configuration found!");

	return config;
}

void add_path(std::experimental::filesystem::path path)
{
    if(!std::experimental::filesystem::exists(path))
        throw No_File_Or_Directory_Exception(path.string());
    else
    {
		// format "path" correctly
		path = to_real_absolute(path);

		std::ifstream in("filedirectorylist");
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

        std::ofstream of("filedirectorylist", std::ios::app);
        of << path.string() << '\n';
    }
}

void remove_path(const std::experimental::filesystem::path& path)
{
    if(!std::experimental::filesystem::exists(path))
        throw No_File_Or_Directory_Exception(path);         // path does not exist

    std::ifstream in("filedirectorylist");
    std::ofstream of("filedirectorylist-2");    // temp copy of list
    std::string temp;			// stores single read paths "filedirectorylist"

    bool skip = false;		// skip writing (removed files)
    bool failed = true;		// file not on the list

	// read paths out of "filedirectorylist" and check if they are equal to "path"; then they will be skipped
    while(in)
    {
        skip = false;
        std::getline(in, temp);		// read path out of the list

        if(temp.length() < 1)       // skip empty lines
            continue;

        // check if read path "temp" is equal to "file", which has to be removed
        if(to_real_absolute(path).string() == temp)
        {
            skip = true;        // skip writing this (to remove) path to the list-copy
        	failed = false;     // is on the list and can be removed
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
        throw Not_On_The_List_Exception(path);

	in.close();
	of.close();

    std::experimental::filesystem::rename("filedirectorylist-2", "filedirectorylist");  // updates name of copy
}

int remove_not_existing_paths()
{
    std::ifstream in("filedirectorylist");
    std::ofstream of("filedirectorylist-2");
    std::string temp;			// stores single read paths "filedirectorylist"
	int num = 0;					// number of removed paths (return-value)

	// read paths out of "filedirectorylist" and check if they still exist
    while(in)
    {
        std::getline(in, temp);		// read path out of the list

        if(temp.length() < 1)       // skip empty lines
            continue;

		// write to file if path exists; skip all not-existing paths
        if(std::experimental::filesystem::exists(temp))
        {
			++num;
			temp += '\n';
            of.write(temp.c_str(), temp.length());
        }
    }

    std::experimental::filesystem::rename("filedirectorylist-2", "filedirectorylist");

	return num;
}

void set_destination(const std::experimental::filesystem::path& path)
{
	if(!std::experimental::filesystem::exists(path))
		throw No_File_Or_Directory_Exception(path.string());
	else
	{
		std::ifstream in("configuration");
		std::ofstream of("configuration-2");
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

    std::experimental::filesystem::rename("configuration-2", "configuration");
}

void set_behavior(Configuration::Already_Existing_Behavior aeb, Configuration::Symlinks_Behavior sb)
{
	std::ifstream in("configuration");
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

	std::experimental::filesystem::rename("configuration-2", "configuration");
}
