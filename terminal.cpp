#include "constants.h"
#include "input.h"
#include "exceptions/exception.h"
#include "log.h"
#include <iostream>
#include <exception>

namespace savfe
{
void terminal()
{
	while(true)
	{
		std::string input;
		std::cout << CONST::TERMINAL_PROMT;
		std::getline(std::cin, input);
		if(std::cin.fail())
			return;

		try
		{
			if(!analyze_input(input))
				break;
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}
	}

	return;
}
}
