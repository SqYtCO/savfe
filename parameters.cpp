#include "parameters.h"
#include "exceptions/error_exception.h"
#include "exceptions/list_exception.h"
#include "exceptions/help_exception.h"
#include "exceptions/log_exception.h"
#include "exceptions/config_exception.h"
#include "exceptions/behavior_exception.h"
#include "exceptions/parameter_help_exception.h"
#include "exceptions/no_file_or_directory_exception.h"
#include "exceptions/check_exception.h"
#include "messages.h"

namespace savfe
{
Parameter_Data analyze_parameters(const int& args, char* argv[])
{
	Parameter_Data params;

	if(args < 2)
		params.terminal = true;

	for(int i = 1; i < args; ++i)
	{
		std::string arg(argv[i]);

		if(arg == "-u" || arg == "--update" || arg == "-R" || arg == "--run")
			params.update = true;
		else if(arg == "-r" || arg == "--remove")
		{
			if(++i < args)
				params.removed.push_back(argv[i]);
			else
				throw Error_Exception(MSG::NO_FILE_TO_REMOVE_SPECIFIED);
		}
		else if(arg == "-a" || arg == "--add")
		{
			if(++i < args)
				params.added.push_back(argv[i]);
			else
				throw Error_Exception(MSG::NO_FILE_TO_ADD_SPECIFIED);
		}
		else if(arg == "-i" || arg == "--ignore")
		{
			if(++i < args)
				params.ignored.push_back(argv[i]);
			else
				throw Error_Exception(MSG::NO_FILE_TO_IGNORE_SPECIFIED);
		}
		else if(arg == "-d" || arg == "--destination")
		{
			if(++i < args)
			{
				params.destination = argv[i];
			}
			else
				throw Error_Exception(MSG::NEEDS_ARGUMENT_W_ARG, argv[i]);
		}
		else if(arg == "-v" || arg == "--verbose")
			params.verbose = true;
		else if(arg == "-l" || arg == "--list")
			throw List_Exception();
		else if(arg == "-c" || arg == "--check")
			params.check_list = true;
		else if(arg == "--log")
			throw Log_Exception();
		else if(arg == "--behavior")
		{
			Configuration::Already_Existing_Behavior aeb;
			Configuration::Symlinks_Behavior sb;

			if(++i < args)
			{
				try
				{
					int temp = std::stoul(arg);
					if(temp == 0 || temp == 1 || temp == 2 || temp == 4)
						aeb = static_cast<Configuration::Already_Existing_Behavior>(temp);
					else
						throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, arg);
				}
				catch(const std::invalid_argument&)
				{
					throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, arg);
				}
				if(++i < args)
				{
					try
					{
						int temp = std::stoul(arg);
						if(temp == 0 || temp == 16 || temp == 32)
							sb = static_cast<Configuration::Symlinks_Behavior>(temp);
						else
							throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, arg);
					}
					catch(const std::invalid_argument&)
					{
						throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, arg);
					}

					throw Behavior_Exception(aeb, sb);
				}
			}
		}
		else if(arg == "--show-config")
			throw Config_Exception();
		else if(arg == "--help" || arg == "-?")
			throw Parameter_Help_Exception();
		else
			throw Error_Exception(MSG::INVALID_ARGUMENT_W_ARG, arg, Parameter_Help_Exception::get_help());
	}

	return params;
}
}
