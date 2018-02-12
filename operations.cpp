#include "operations.h"

// replaces all ".." and "." with correct absolute path
// "spath" have to be an correct absolute path
std::string& process_absolute_path(std::string& spath);

std::experimental::filesystem::path to_real_absolute(const std::experimental::filesystem::path& path)
{
	std::string spath;			// string of "path"

	// check if "path" is relativ; if so, extend to absolute path
	if(path.is_relative())
		spath = std::experimental::filesystem::absolute(path).string();
	else
		spath = path.string();

	// check if "/.." or "/." could be in "path"
	if(spath.find("/.") != std::string::npos)
	{
		process_absolute_path(spath);			// substitutes ".." and "." with right absolute path
	}

	// do not add '/' to files
	if(spath[spath.length() - 1] != '/' && std::experimental::filesystem::is_directory(spath))
		spath += '/';

	return std::experimental::filesystem::path(spath);
}

std::string& process_absolute_path(std::string& spath)
{
	std::size_t pos = 0;
	while((pos = spath.find("/..")) != std::string::npos)
	{
		if(spath[pos + 3] == '/')
		{
			int last_slash = spath.find_last_of('/', pos - 1);
			spath.erase(last_slash, pos - last_slash + 3);
		}
		else if(pos == spath.length() - 3)
		{
			spath.resize(spath.find_last_of('/', spath.length() - 4) + 1);
		}
	}

	pos = 0;

	while((pos = spath.find("/.", pos)) != std::string::npos)
	{
		spath.erase(pos + 1, 1);
	}

	return spath;
}

bool is_sub_equal_directory(const std::experimental::filesystem::path& sub, const std::experimental::filesystem::path& parent)
{
	if(sub.string().length() < parent.string().length())
		return false;

	std::size_t pos = 0;

	while(pos < parent.string().length())
	{
		if(sub.string()[pos] == parent.string()[pos])
			++pos;
		else
			return false;
	}

	return true;
}

bool is_sub_directory(const std::experimental::filesystem::path& sub, const std::experimental::filesystem::path& parent)
{
	if(sub.string().length() == parent.string().length())
		return false;
	else
		return is_sub_equal_directory(sub, parent);
}

bool is_parent_equal_directory(const std::experimental::filesystem::path& parent, const std::experimental::filesystem::path& sub)
{
	if(sub.string().length() < parent.string().length())
		return false;

	std::size_t pos = 0;

	while(pos < parent.string().length())
	{
		if(sub.string()[pos] == parent.string()[pos])
			++pos;
		else
			return false;
	}

	return true;
}

bool is_parent_directory(const std::experimental::filesystem::path& parent, const std::experimental::filesystem::path& sub)
{
	if(sub.string().length() == parent.string().length())
		return false;
	else
		return is_parent_equal_directory(parent, sub);
}
