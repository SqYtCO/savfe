#ifndef NO_FILE_ORDIRECTORY_EXCEPTION_H
#define NO_FILE_ORDIRECTORY_EXCEPTION_H

#include "exceptions.h"
#include "../messages.h"
#include <iostream>
#include <vector>
#include <string>

struct No_File_Or_Directory_Exception : public Exception
{
	No_File_Or_Directory_Exception(const std::string& file) { files.push_back(file); }
	No_File_Or_Directory_Exception(const std::vector<std::string>& files) : files(files) {   }
	std::vector<std::string> files;

	virtual void exec() const override
	{
		for(const auto& a : files)
			std::cerr << '\"' << a << '\"' << MSG::NO_SUCH_FILE_OR_DIRECTORY_W_ARG << '\n';
	}

	virtual const char* which() const override
	{
		return "No_File_Or_Directory_Exception";
	}
};

#endif // NO_FILE_ORDIRECTORY_EXCEPTION_H
