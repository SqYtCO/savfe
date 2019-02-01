#ifndef CHECK_EXCEPTION_H
#define CHECK_EXCEPTION_H

#include "exception.h"

struct Check_Exception : public Exception
{
	virtual void exec() const noexcept override
	{
	//	check_list();
	}

	virtual const char* which() const noexcept override
	{
		return "Check_Exception";
	}
};

#endif // CHECK_EXCEPTION_H
