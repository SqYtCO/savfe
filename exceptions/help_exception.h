#ifndef HELP_EXCEPTION_H
#define HELP_EXCEPTION_H

#include "exceptions.h"
#include "../help_texts.h"
#include <iostream>

struct Help_Exception : public Exception
{
	virtual void exec() const override
	{
		std::cout << get_help();
	}

	static const char* get_help()
	{
		return HELP_TXT::TERMINAL_HELP_TXT;
	}

	virtual const char* which() const override
	{
		return "Help_Exception";
	}
};

#endif // HELP_EXCEPTION_H
