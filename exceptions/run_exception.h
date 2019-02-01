#ifndef RUN_EXCEPTION_H
#define RUN_EXCEPTION_H

#include "exception.h"
#include "../run.h"
#include "../settings.h"
#include "../log.h"

struct Run_Exception : public Exception
{
	virtual void exec() const noexcept override
	{
		try
		{
			// verbose always active
			run(read_configuration(), true);
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}
		catch(const std::exception& exc)
		{
			log(exc.what(), Log_Type::Error);
		}
	}

	virtual const char* which() const noexcept override
	{
		return "Run_Exception";
	}
};

#endif // RUN_EXCEPTION_H
