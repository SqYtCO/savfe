#ifndef RUN_EXCEPTION_H
#define RUN_EXCEPTION_H

#include "exceptions.h"
#include "../run.h"
#include "../settings.h"

struct Run_Exception : public Exception
{
	virtual void exec() const override
	{
		Configuration config;
		try
		{
			config = read_configuration();
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}

		// verbose always active
		run(config, true);
	}

	virtual const char* which() const override
	{
		return "Run_Exception";
	}
};

#endif // RUN_EXCEPTION_H
