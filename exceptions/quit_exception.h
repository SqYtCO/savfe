#ifndef QUIT_EXCEPTION_H
#define QUIT_EXCEPTION_H

#include "exception.h"
#include <cstdlib>

struct Quit_Exception
{
	Quit_Exception(const int& ret = 0) : return_value(ret) {	}
	int return_value;

	[[noreturn]] void exec() const noexcept
	{
		std::exit(return_value);
	}
};

#endif // QUIT_EXCEPTION_H
