#include "dir_functions.h"
#include <string>

namespace savfe
{
namespace stdfs = std::filesystem;

bool is_equal(const std::string& a, const std::string& b)
{
	int diff = static_cast<int>(a.length()) - static_cast<int>(b.length());
	if((diff == 0 || (diff == -1 && b.back() == stdfs::path::preferred_separator)) &&
		b.find(a) == 0)
			return true;
	else if(diff == 1 && a.back() == stdfs::path::preferred_separator &&
			a.find(b) == 0)
		return true;

	return false;
}

bool is_equal(const stdfs::path& a, const stdfs::path& b)
{
	return is_equal(a.string(), b.string());
}

bool is_sub_equal_directory(const std::string& sub, const std::string& parent)
{
//	if(stdfs::equivalent(sub, parent))
	if(is_equal(sub, parent))
		return true;

	if(sub.length() <= parent.length())
		return false;

	if(sub.find(parent) == 0 &&
			(sub[parent.length()] == stdfs::path::preferred_separator ||
			 parent.back() == stdfs::path::preferred_separator))
		return true;
	else
		return false;
}

bool is_sub_equal_directory(const stdfs::path& sub, const stdfs::path& parent)
{
	return is_sub_equal_directory(sub.string(), parent.string());
}

bool is_sub_directory(const std::string& sub, const std::string& parent)
{
//	if(stdfs::equivalent(sub, parent))
	if(is_equal(sub, parent))
		return false;
	else
		return is_sub_equal_directory(sub, parent);
}

bool is_sub_directory(const stdfs::path& sub, const stdfs::path& parent)
{
	return is_sub_directory(sub.string(), parent.string());
}

bool is_parent_equal_directory(const stdfs::path& parent, const stdfs::path& sub)
{
	return is_sub_equal_directory(sub, parent);
}

bool is_parent_directory(const stdfs::path& parent, const stdfs::path& sub)
{
	return is_sub_directory(sub, parent);
}

stdfs::path format_path(const stdfs::path& path)
{
	stdfs::path return_path = stdfs::absolute(path.lexically_normal().make_preferred());
//	return_path = path_to_string(return_path);
	return return_path;
}

std::string path_to_string(const stdfs::path& path)
{
	std::string return_string = path.string();
	if(stdfs::is_directory(path) && return_string.back() != stdfs::path::preferred_separator)
		return_string += stdfs::path::preferred_separator;
	return return_string;
}
}
