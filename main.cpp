#include "parameters.h"
#include "terminal.h"
#include "settings.h"
#include "run.h"
#include "log.h"
#include "exceptions/add_exception.h"
#include "exceptions/remove_exception.h"
#include "exceptions/destination_exception.h"
#include "exceptions/check_exception.h"
#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <ctime>

int main(int args, char* argv[])
{
	// store parameters
	savfe::Parameter_Data params;

	try
	{
		params = savfe::analyze_parameters(args, argv);
	}
	catch(const savfe::Exception& exc)
	{
		exc.exec();
	}
	catch(...)
	{
		savfe::log(savfe::LOG_MSG::UNKNOWN_PARAMETER_ERROR, savfe::Log_Type::Fatale_Error, savfe::Log_Output::File_And_Stdout);
		return -1;
	}

	if(!params.destination.empty())
		savfe::Destination_Exception(params.destination).exec();
	if(!params.added.empty())
		savfe::Add_Exception(params.added).exec();
	if(!params.ignored.empty())
		savfe::Add_Exception(params.ignored, true);
	if(!params.removed.empty())
		savfe::Remove_Exception(params.removed).exec();
	if(params.check_list)
		savfe::Check_Exception().exec();
	if(params.update)
	{
		try
		{
			savfe::update_save(params.verbose);
		}
		catch (const savfe::Exception& exc)
		{
			exc.exec();
		}
		catch(const std::exception& exc)
		{
			savfe::log(exc.what(), savfe::Log_Type::Error, savfe::Log_Output::File_And_Stdout);
		}
		catch(...)
		{
			savfe::log(savfe::MSG::FATALE_RUNNING_ERROR, savfe::Log_Type::Fatale_Error, savfe::Log_Output::Stdout);
			savfe::log(savfe::LOG_MSG::RUN_ERROR, savfe::Log_Type::Fatale_Error, savfe::Log_Output::Fileoutput);
			return -2;
		}
	}
	if(params.terminal)
	{
		try
		{
			savfe::terminal();
		}
		catch(const savfe::Exception& exc)
		{
			savfe::log(exc.which(), savfe::Log_Type::Error, savfe::Log_Output::File_And_Stdout);
		}
		catch(const std::exception& exc)
		{
			savfe::log(exc.what(), savfe::Log_Type::Error, savfe::Log_Output::File_And_Stdout);
		}
		catch(...)
		{
			savfe::log(savfe::MSG::FATALE_TERMINAL_ERROR, savfe::Log_Type::Fatale_Error, savfe::Log_Output::Stdout);
			savfe::log(savfe::LOG_MSG::UNKNOWN_TERMINAL_ERROR, savfe::Log_Type::Fatale_Error, savfe::Log_Output::Fileoutput);
			return -3;
		}
	}

	return 0;
}
