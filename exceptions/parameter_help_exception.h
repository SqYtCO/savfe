#ifndef PARAMETER_HELP_EXCEPTION_H
#define PARAMETER_HELP_EXCEPTION_H

#include "exception.h"
#include "../help_texts.h"
#include <iostream>

namespace savfe
{
struct Parameter_Help_Exception : public Exception
{
	virtual void exec() const noexcept override
	{
		std::cout << get_help() << '\n';
	}

	virtual const char* which() const noexcept override
	{
		return "Parameter_Help_Exception";
	}

	static const char* get_help()
	{
		return HELP_TXT::PARAMETER_HELP_TXT;
	}
};
}

#endif // PARAMETER_HELP_EXCEPTION_H
