#ifndef NO_DIRECTORY_EXCEPTION
#define NO_DIRECTORY_EXCEPTION

#include "../messages.h"
#include "exceptions.h"
#include <iostream>

struct No_Directory_Exception : public Exception
{
	No_Directory_Exception(const std::string& not_dir) : not_dir(not_dir) {	}
	std::string not_dir;

	virtual void exec() const override
	{
		std::cerr << '\"' << not_dir << '\"' << MSG::IS_NO_DIRECTORY_W_ARG << '\n';
	}

	virtual const char* which() const override
	{
		return "No_Directory_Exception";
	}
};

#endif // NO_DIRECTORY_EXCEPTION
