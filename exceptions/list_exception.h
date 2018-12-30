#ifndef LIST_EXCEPTION_H
#define LIST_EXCEPTION_H

#include "exceptions.h"
#include "../constants.h"
#include <iostream>
#include <fstream>
#include <string>

struct List_Exception : public Exception
{
	virtual void exec() const override
	{
		std::ifstream in(FILES::LIST_NAME);
		std::string temp;
		while(in)
		{
			std::getline(in, temp);
			std::cout << temp << '\n';
		}
	}

	virtual const char* which() const override
	{
		return "List_Exception";
	}
};

#endif // LIST_EXCEPTION_H
