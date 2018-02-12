#include "constants.h"
#include "input.h"
#include "exceptions.h"
#include "log.h"
#include <iostream>
#include <exception>

void terminal()
{
	while(true)
	{
		std::string input;
		std::cout << CONST::TERMINAL_PROMT;
		std::getline(std::cin, input);
		try
		{
			analyze_input(input);
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}
	}
}
