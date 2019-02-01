#ifndef HELP_EXCEPTION_H
#define HELP_EXCEPTION_H

#include "exception.h"
#include "../help_texts.h"
#include <iostream>

struct Help_Exception : public Exception
{
	virtual void exec() const noexcept override
	{
		std::cout << get_help();
	}

	virtual const char* which() const noexcept override
	{
		return "Help_Exception";
	}

	static const char* get_help()
	{
		return HELP_TXT::TERMINAL_HELP_TXT;
	}
};

#endif // HELP_EXCEPTION_H
