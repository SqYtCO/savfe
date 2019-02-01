#ifndef DIR_FUNCTIONS_H
#define DIR_FUNCTIONS_H

#include <filesystem>

// replaces "/.." and "/." with correct absolute path
// "path" can be absolute or relative
// return-value is the full absolute path
std::filesystem::path to_real_absolute(const std::filesystem::path& path);

// checks if "sub" is a sub-directory or file of "parent" or is equal, return true if "sub"=="parent"
// "sub" and "parent" will be passed to "to_real_absolute", so it is unimportant if they are absolute or relative
bool is_sub_equal_directory(const std::filesystem::path& sub, const std::filesystem::path& parent);

// checks if "sub" is a sub-directory or file of "parent", return false if "sub"=="parent"
// "sub" and "parent" will be passed to "to_real_absolute", so it is unimportant if they are absolute or relative
bool is_sub_directory(const std::filesystem::path& sub, const std::filesystem::path& parent);

//check if "parent" is a parent-directory of "sub", return true if "parent"=="sub"
// "parent" and "sub" will be passed to "to_real_absolute", so it is unimportant if they are absolute or relative
bool is_parent_equal_directory(const std::filesystem::path& parent, const std::filesystem::path& sub);

//check if "parent" is a parent-directory of "sub", return false if "parent"=="sub"
// "parent" and "sub" will be passed to "to_real_absolute", so it is unimportant if they are absolute or relative
bool is_parent_directory(const std::filesystem::path& parent, const std::filesystem::path& sub);

#endif // DIR_FUNCTIONS_H
