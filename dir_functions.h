#ifndef DIR_FUNCTIONS_H
#define DIR_FUNCTIONS_H

#include <filesystem>

namespace savfe
{
std::filesystem::path format_path(const std::filesystem::path& path);
std::string path_to_string(const std::filesystem::path& path);

// paths with multiple separators one after another (e.g. "/home///") will result in a false result in comparison to "/home/"
bool is_equal(const std::string& a, const std::string& b);
bool is_equal(const std::filesystem::path& a, const std::filesystem::path& b);

// checks if "sub" is a sub-directory or file of "parent" or is equal, return true if "sub"=="parent"
bool is_sub_equal_directory(const std::string& sub, const std::string& parent);
bool is_sub_equal_directory(const std::filesystem::path& sub, const std::filesystem::path& parent);

// checks if "sub" is a sub-directory or file of "parent", return false if "sub"=="parent"
bool is_sub_directory(const std::filesystem::path& sub, const std::filesystem::path& parent);

bool is_parent_equal_directory(const std::filesystem::path& parent, const std::filesystem::path& sub);
bool is_parent_directory(const std::filesystem::path& parent, const std::filesystem::path& sub);
}

#endif // DIR_FUNCTIONS_H
