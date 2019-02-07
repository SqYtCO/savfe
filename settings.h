#ifndef SETTINGS_H
#define SETTINGS_H

#include "exceptions/no_directory_exception.h"
#include "constants.h"
#include "dir_functions.h"
#include <string>
#include <filesystem>

namespace savfe
{
class Configuration
{
public:
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

private:
    std::string destination;
    bool keep_old_indexfiles;
    std::pair<Already_Existing_Behavior, Symlinks_Behavior> behavior;
    bool verbose;

public:
    Configuration();
    void read_configuration();
    void write_configuration();

    void set_destination(const std::filesystem::path& path)
    {
	if(!std::filesystem::is_directory(path))
	    throw No_Directory_Exception(path);
	destination = path_to_string(format_path(path));
	write_configuration();
    }
    void set_behavior(Configuration::Already_Existing_Behavior aeb, Configuration::Symlinks_Behavior sb) { behavior = {aeb, sb}; write_configuration(); }
    void set_keep_old_indexfiles(bool new_keep_old_indexfiles) { keep_old_indexfiles = new_keep_old_indexfiles; write_configuration(); }
    void set_verbose(bool new_verbose) { verbose = new_verbose; write_configuration(); }

    const std::string& get_destination() const { return destination; }
    const auto& get_behavior() const { return behavior; }
    bool get_keep_old_indexfiles() const { return keep_old_indexfiles; }
    bool get_verbose() const { return verbose; }
};

// global config
inline Configuration config;

// add path "path" to given list
// can throw "No_path_Or_Directory_Exception" and "Already_On_The_List_Exception"
void add_path(const std::filesystem::path& path, const std::string& listfile = FILES::LIST_NAME);

// removes path "path" from list in file FILES::LIST_NAME
// creates temporary file "filedirectorylist-2"
// "path" will be passed to "to_real_absolute", so it is unimportant if "path" is absolute or relative
// can throw "No_Path_Or_Directory_Exception" and "Error_Exception"
void remove_path(const std::filesystem::path& path, const std::string& listfile = FILES::LIST_NAME, const std::string& templistfile = FILES::TEMP_LIST_NAME);

// removes all deleted and not anymore existing paths from list in file FILES::LIST_NAME
// creates temporary file "filedirectorylist-2"
// return-value is the number of removed paths
int remove_not_existing_paths(const std::string& listfile = FILES::LIST_NAME, const std::string& templistfile = FILES::TEMP_LIST_NAME);
}

#endif // SETTINGS_H
