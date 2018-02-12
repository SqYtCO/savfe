#include "parameters.h"
#include "terminal.h"
#include "settings.h"
#include "run.h"
#include "log.h"
#include "exceptions.h"
#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <ctime>

int main(int args, char* argv[])
{
	// stores parameters
	Data params;

	try
	{
		params = analyze_parameters(args, argv);
	}
	catch(const Exception& exc)
	{
		try
		{
			exc.exec();
		}
		catch(const Exception& exc)
		{
			log(exc.which(), Log_Type::Error);
			std::cerr << '\n' << exc.which() << '\n';
		}
	}
	catch(...)
	{
		log(LOG_MSG::UNKNOWN_PARAMETER_ERROR, Log_Type::Fatale_Error);
	}

	try
	{
		if(params.terminal)
		{
			try
			{
				terminal();
			}
			catch(const Exception& exc)
			{
				log(exc.which(), Log_Type::Error);
				std::cerr << '\n' << exc.which() << '\n';
			}
			catch(const std::exception& e)
			{
				log(e.what());
				std::cerr << e.what() << '\n';
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
		{
			for(const auto& a : params.added)
				Add_Exception(a).exec();
		}
		if(!params.removed.empty())
		{
			for(const auto& a : params.removed)
				Remove_Exception(a).exec();
		}
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
			catch(const std::exception& e)
			{
				log(e.what());
				std::cerr << e.what() << '\n';
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
