#ifndef PARAMETER_HELP_EXCEPTION_H
#define PARAMETER_HELP_EXCEPTION_H

#include "exceptions.h"
#include "../help_texts.h"
#include <iostream>

struct Parameter_Help_Exception : public Exception
{
	virtual void exec() const override
	{
		std::cout << get_help() << '\n';
	}

	static const char* get_help()
	{
		return HELP_TXT::PARAMETER_HELP_TXT;
	}

	virtual const char* which() const override
	{
		return "Parameter_Help_Exception";
	}
};

#endif // PARAMETER_HELP_EXCEPTION_H
