#ifndef CHECK_EXCEPTION_H
#define CHECK_EXCEPTION_H

#include "exceptions.h"

struct Check_Exception : public Exception
{
	virtual void exec() const override
	{
	//	check_list();
	}

	virtual const char* which() const override
	{
		return "Check_Exception";
	}
};

#endif // CHECK_EXCEPTION_H
