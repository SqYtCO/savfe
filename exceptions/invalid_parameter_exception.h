#ifndef INVALID_PARAMETER_EXCEPTION_H
#define INVALID_PARAMETER_EXCEPTION_H

#include "exceptions.h"
#include "quit_exception.h"
#include "parameter_help_exception.h"
#include "../messages.h"
#include <iostream>
#include <string>

// throw Quit_Exception
struct Invalid_Parameter_Exception : public Exception
{
	Invalid_Parameter_Exception(const std::string& arg) : arg(arg) {	}
	std::string arg;

	virtual void exec() const override
	{
		std::cerr << MSG::INVALID_ARGUMENT_W_ARG << arg << '\n'
				<< Parameter_Help_Exception::get_help();

		throw Quit_Exception();
	}

	virtual const char* which() const override
	{
		return "Invalid_Parameter_Exception";
	}
};

#endif // INVALID_PARAMETER_EXCEPTION_H
