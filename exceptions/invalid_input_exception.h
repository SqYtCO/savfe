#ifndef INVALID_INPUT_EXCEPTION_H
#define INVALID_INPUT_EXCEPTION_H

#include "exceptions.h"
#include "help_exception.h"
#include "../messages.h"
#include <iostream>
#include <string>

struct Invalid_Input_Exception : public Exception
{
	Invalid_Input_Exception(const std::string& in) : input(in) {	}
	std::string input;

	virtual void exec() const override
	{
		std::cout << MSG::UNKNOWN_COMMAND_W_ARG << input << '\n'
			<< Help_Exception::get_help();
	}

	virtual const char* which() const override
	{
		return "Invalid_Input_Exception";
	}
};

#endif // INVALID_INPUT_EXCEPTION_H
