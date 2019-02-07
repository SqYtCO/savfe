#ifndef NO_DIRECTORY_EXCEPTION
#define NO_DIRECTORY_EXCEPTION

#include "../messages.h"
#include "exception.h"
#include <iostream>

namespace savfe
{
struct No_Directory_Exception : public Exception
{
	No_Directory_Exception(const std::string& not_dir) : not_dir(not_dir) {	}

	virtual void exec() const noexcept override
	{
		std::cerr << '\"' << not_dir << '\"' << MSG::IS_NO_DIRECTORY_W_ARG << '\n';
	}

	virtual const char* which() const noexcept override
	{
		return "No_Directory_Exception";
	}

private:
	std::string not_dir;
};
}

#endif // NO_DIRECTORY_EXCEPTION
