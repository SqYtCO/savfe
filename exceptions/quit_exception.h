#ifndef QUIT_EXCEPTION_H
#define QUIT_EXCEPTION_H

#include "exceptions.h"
#include <cstdlib>

struct Quit_Exception : public Exception
{
	Quit_Exception(const int& ret = 0) : return_value(ret) {	}
	int return_value;

	virtual void exec() const override
	{
		std::exit(return_value);
	}

	virtual const char* which() const override
	{
		return "Quit_Exception";
	}
};

#endif // QUIT_EXCEPTION_H
