#include "constants.h"
#include "input.h"
#include "exceptions/exception.h"
#include "exceptions/quit_exception.h"
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
		catch(const Quit_Exception& exc)
		{
			throw exc;
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}
	}
}
