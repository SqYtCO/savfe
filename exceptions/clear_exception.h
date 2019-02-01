#ifndef CLEAR_EXCEPTION_H
#define CLEAR_EXCEPTION_H

#include "exception.h"
#include "../constants.h"
#include "../messages.h"
#include "../log.h"
#include <iostream>
#include <fstream>
#include <algorithm>	// std::transform
#include <cctype>		// std::tolower

struct Clear_Exception : public Exception
{
	virtual void exec() const noexcept override
	{
		std::string choice;
		std::cout << MSG::CLEAR_LIST_REQUEST_ANSWER;
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::transform(choice.begin(), choice.end(), choice.begin(),
				[](unsigned char c){ return std::tolower(c); });
		if(choice == "y" || choice == "ye" || choice == "yes")
		{
			std::ofstream of(FILES::LIST_NAME, std::ios::trunc);
			log(LOG_MSG::LIST_CLEARED);
		}
		else
			std::cerr << MSG::OPERATION_CANCELED << '\n';
	}

	virtual const char* which() const noexcept override
	{
		return "Clear_Exception";
	}
};

#endif // CLEAR_EXCEPTION_H
