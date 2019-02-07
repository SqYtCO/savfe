#ifndef SUCCESS_EXCEPTION_H
#define SUCCESS_EXCEPTION_H

#include "exception.h"
#include "../messages.h"
#include <iostream>

namespace savfe
{
struct Success_Exception : public Exception
{
	Success_Exception(const std::string& successmsg, const std::string& arg = std::string())
		: successmsg(successmsg), arg(arg) {	}

	virtual void exec() const noexcept override
	{
		if(arg.empty())
			std::cout << successmsg << '\n';
		else
			std::cout << '\"' << arg << '\"' << successmsg << '\n';
	}

	virtual const char* which() const noexcept override
	{
		return "Success_Exception";
	}

private:
	std::string arg;
	std::string successmsg;
};
}

#endif // SUCCESS_EXCEPTION_H
