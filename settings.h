#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <filesystem>

struct Configuration
{
    enum Already_Existing_Behavior
    {
	Rename_Existing = 0,
	Skip_Existing = 1,
	Overwrite_Existing = 2,
	Update_Existing = 4
	};

	enum Symlinks_Behavior
	{
	Follow_Symlinks = 0,
	Copy_Symlinks = 16,
	Skip_Symlinks = 32
	};

	std::string destination;

	bool keep_old_indexfiles = true;

	Already_Existing_Behavior aeb = Already_Existing_Behavior::Rename_Existing;
	Symlinks_Behavior sb = Symlinks_Behavior::Follow_Symlinks;
};

Configuration read_configuration();

// adds path "path" to list in file FILES::LIST_NAME
// "path" will be passed to "to_real_absolute", so it is unimportant if "path" is absolute or relative
// can throw "No_path_Or_Directory_Exception" and "Already_On_The_List_Exception"
void add_path(std::filesystem::path path);

// removes path "path" from list in file FILES::LIST_NAME
// creates temporary file "filedirectorylist-2"
// "path" will be passed to "to_real_absolute", so it is unimportant if "path" is absolute or relative
// can throw "No_Path_Or_Directory_Exception" and "Error_Exception"
void remove_path(const std::filesystem::path& path);

// removes all deleted and not anymore existing paths from list in file FILES::LIST_NAME
// creates temporary file "filedirectorylist-2"
// return-value is the number of removed paths
int remove_not_existing_paths();

void set_destination(const std::filesystem::path& path);

void set_behavior(Configuration::Already_Existing_Behavior aeb, Configuration::Symlinks_Behavior sb);

void add_ignore_path(std::filesystem::path path);

#endif // SETTINGS_H
