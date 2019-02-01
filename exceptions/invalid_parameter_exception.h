#ifndef INVALID_PARAMETER_EXCEPTION_H
#define INVALID_PARAMETER_EXCEPTION_H

#include "exception.h"
#include "quit_exception.h"
#include "parameter_help_exception.h"
#include "../messages.h"
#include <iostream>
#include <string>

struct Invalid_Parameter_Exception : public Exception
{
	Invalid_Parameter_Exception(const std::string& arg) : arg(arg) {	}

	virtual void exec() const noexcept override
	{
		std::cerr << MSG::INVALID_ARGUMENT_W_ARG << arg << '\n'
				<< Parameter_Help_Exception::get_help();
	}

	virtual const char* which() const noexcept override
	{
		return "Invalid_Parameter_Exception";
	}

private:
	std::string arg;
};

#endif // INVALID_PARAMETER_EXCEPTION_H
