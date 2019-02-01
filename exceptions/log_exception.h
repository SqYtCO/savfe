#ifndef LOG_EXCEPTION_H
#define LOG_EXCEPTION_H

#include "exception.h"
#include "error_exception.h"
#include "../constants.h"
#include "../messages.h"
#include "../log.h"
#include <iostream>
#include <fstream>
#include <string>

struct Log_Exception : public Exception
{
	virtual void exec() const noexcept override
	{
		try
		{
			std::ifstream in(FILES::LOG_NAME);
			if(in)
			{
				std::string temp;

				while(in)
				{
					std::getline(in, temp);
					std::cout << temp << '\n';
				}
			}
			else
				throw Error_Exception(MSG::NO_LOGFILE_FOUND);
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
		return "Log_Exception";
	}
};

#endif // LOG_EXCEPTION_H
