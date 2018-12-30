#ifndef CONFIG_EXCEPTION_H
#define CONFIG_EXCEPTION_H

#include "exceptions.h"
#include "error_exception.h"
#include "../constants.h"
#include <iostream>
#include <fstream>
#include <string>

struct Config_Exception : public Exception
{
	virtual void exec() const override
	{
		try
		{
			std::ifstream in(FILES::CONFIG_NAME);
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
				throw Error_Exception(MSG::NO_CONFIGFILE_FOUND);
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}
	}

	virtual const char* which() const override
	{
		return "Config_Exception";
	}
};

#endif // CONFIG_EXCEPTION_H
