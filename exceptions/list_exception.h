#ifndef LIST_EXCEPTION_H
#define LIST_EXCEPTION_H

#include "exception.h"
#include "../constants.h"
#include <iostream>
#include <fstream>
#include <string>

struct List_Exception : public Exception
{
	virtual void exec() const noexcept override
	{
		std::ifstream in(FILES::LIST_NAME);
		std::string temp;
		while(in)
		{
			std::getline(in, temp);
			if(!temp.empty())
				std::cout << temp << '\n';
		}
		std::cout << "Ignored:\n";
		in.close();
		in.clear();
		in.open(FILES::IGNORELIST_NAME);
		while(in)
		{
			std::getline(in, temp);
			if(!temp.empty())
				std::cout << temp << '\n';
		}
	}

	virtual const char* which() const noexcept override
	{
		return "List_Exception";
	}
};

#endif // LIST_EXCEPTION_H
