#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

#include "exceptions.h"
#include <iostream>
#include <string>

struct Error_Exception : public Exception
{
	Error_Exception(const std::string& errormsg,
		const std::string& arg = std::string(),
		const std::string& help = std::string())
		: errormsg(errormsg), arg(arg), help(help){	}
	std::string errormsg;
	std::string arg;
	std::string help;

	virtual void exec() const override
	{
		if(arg.empty())
			std::cerr << errormsg << '\n';
		else if(help.empty())
			std::cerr << '\"' << arg << '\"' << errormsg << '\n';
		else
			std::cerr << errormsg << arg << '\n' << help;
	}

	virtual const char* which() const override
	{
		return "Error_Exception";
	}
};

#endif // ERROR_EXCEPTION_H
