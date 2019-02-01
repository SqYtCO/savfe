#ifndef CONFIG_EXCEPTION_H
#define CONFIG_EXCEPTION_H

#include "exception.h"
#include "error_exception.h"
#include "../constants.h"
#include "../messages.h"
#include <iostream>
#include <fstream>
#include <string>

struct Config_Exception : public Exception
{
	virtual void exec() const noexcept override
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
			Error_Exception(MSG::NO_CONFIGFILE_FOUND).exec();
	}

	virtual const char* which() const noexcept override
	{
		return "Config_Exception";
	}
};

#endif // CONFIG_EXCEPTION_H
