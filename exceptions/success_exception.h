#ifndef SUCCESS_EXCEPTION_H
#define SUCCESS_EXCEPTION_H

#include "exceptions.h"
#include "../messages.h"
#include <iostream>

struct Success_Exception : public Exception
{
	Success_Exception(const std::string& successmsg, const std::string& arg = std::string())
		: successmsg(successmsg) {	}
	std::string arg;
	std::string successmsg;

	virtual void exec() const override
	{
		if(arg.empty())
			std::cerr << successmsg << '\n';
		else
			std::cerr << '\"' << arg << '\"' << successmsg << '\n';
	}

	virtual const char* which() const override
	{
		return "Success_Exception";
	}
};

#endif // SUCCESS_EXCEPTION_H
