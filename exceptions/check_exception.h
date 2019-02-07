#ifndef CHECK_EXCEPTION_H
#define CHECK_EXCEPTION_H

#include "exception.h"
#include "../settings.h"
#include "../messages.h"
#include <iostream>

namespace savfe
{
struct Check_Exception : public Exception
{
	virtual void exec() const noexcept override
	{
		std::cout << remove_not_existing_paths(FILES::LIST_NAME, FILES::TEMP_LIST_NAME)
					<< MSG::ELEMENTS_REMOVED_W_ARG << " (list)\n"
					<< remove_not_existing_paths(FILES::IGNORELIST_NAME, FILES::TEMP_IGNORELIST_NAME)
					<< MSG::ELEMENTS_REMOVED_W_ARG << " (ignorelist)\n";
	}

	virtual const char* which() const noexcept override
	{
		return "Check_Exception";
	}
};
}

#endif // CHECK_EXCEPTION_H
