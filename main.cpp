#include "parameters.h"
#include "terminal.h"
#include "settings.h"
#include "run.h"
#include "log.h"
#include "exceptions/quit_exception.h"
#include "exceptions/add_exception.h"
#include "exceptions/ignore_exception.h"
#include "exceptions/remove_exception.h"
#include "exceptions/destination_exception.h"
#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <ctime>

int main(int args, char* argv[])
{
	// store parameters
	Parameter_Data params;

	try
	{
		params = analyze_parameters(args, argv);
	}
	catch(const Exception& exc)
	{
		exc.exec();
	}
	catch(...)
	{
		log(LOG_MSG::UNKNOWN_PARAMETER_ERROR, Log_Type::Fatale_Error);
		return -1;
	}

	try
	{
		if(params.terminal)
		{
			try
			{
				terminal();
			}
			catch(const Quit_Exception& exc)
			{
				return exc.return_value;
			}
			catch(const Exception& exc)
			{
				log(exc.which(), Log_Type::Error);
				std::cerr << '\n' << exc.which() << '\n';
			}
			catch(const std::exception& exc)
			{
				log(exc.what(), Log_Type::Error);
				std::cerr << exc.what() << '\n';
			}
			catch(...)
			{
				std::cerr << MSG::FATALE_TERMINAL_ERROR;
				log(LOG_MSG::UNKNOWN_TERMINAL_ERROR, Log_Type::Fatale_Error);
			}
		}
		if(!params.destination.empty())
		{
			Destination_Exception(params.destination).exec();
		}
		if(!params.added.empty())
			Add_Exception(params.added).exec();
		if(!params.ignored.empty())
			Ignore_Exception(params.ignored);
		if(!params.removed.empty())
			Remove_Exception(params.removed).exec();
		if(params.update)
		{
			try
			{
				Configuration config = read_configuration();

				run(config, params.verbose);
			}
			catch (const Exception& exc)
			{
				exc.exec();
			}
			catch(const std::exception& exc)
			{
				log(exc.what());
				std::cerr << exc.what() << '\n';
			}
			catch(...)
			{
				std::cerr << MSG::FATALE_RUNNING_ERROR;
				log(LOG_MSG::RUN_ERROR, Log_Type::Fatale_Error);
			}
		}
	}
	catch(const Exception& exc)
	{
		exc.exec();
	}

	return 0;
}
