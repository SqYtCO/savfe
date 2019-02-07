#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

#include "exception.h"
#include <iostream>
#include <string>

namespace savfe
{
struct Error_Exception : public Exception
{
	Error_Exception(const std::string& errormsg,
		const std::string& arg = std::string(),
		const std::string& help = std::string())
		: errormsg(errormsg), arg(arg), help(help){	}

	virtual void exec() const noexcept override
	{
		if(arg.empty())
			std::cerr << errormsg << '\n';
		else if(help.empty())
			std::cerr << '\"' << arg << '\"' << errormsg << '\n';
		else
			std::cerr << errormsg << arg << '\n' << help;
	}

	virtual const char* which() const noexcept override
	{
		return "Error_Exception";
	}

private:
	std::string errormsg;
	std::string arg;
	std::string help;
};
}

#endif // ERROR_EXCEPTION_H
