#ifndef DESTINATION_EXCEPTION_H
#define DESTINATION_EXCEPTION_H

#include "exception.h"
#include "success_exception.h"
#include "../messages.h"
#include "../log.h"
#include "../settings.h"
#include <iostream>
#include <string>

struct Destination_Exception : public Exception
{
	Destination_Exception(const std::string& dest) : destination(dest) {	}

	virtual void exec() const noexcept override
	{
		try
		{
			set_destination(destination);
			log(("\"" + destination + "\"" + std::string(" set as destination")).c_str());
			throw Success_Exception(MSG::SUCCESSFULLY_SET_AS_DESTINAION_W_ARG, destination);
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
		return "Destination_Exception";
	}

private:
	std::string destination;
};

#endif // DESTINATION_EXCEPTION_H
