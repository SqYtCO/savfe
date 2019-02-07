#include "input.h"
#include "exceptions/run_exception.h"
#include "exceptions/error_exception.h"
#include "exceptions/add_exception.h"
#include "exceptions/remove_exception.h"
#include "exceptions/destination_exception.h"
#include "exceptions/list_exception.h"
#include "exceptions/clear_exception.h"
#include "exceptions/help_exception.h"
#include "exceptions/log_exception.h"
#include "exceptions/config_exception.h"
#include "exceptions/behavior_exception.h"
#include "exceptions/check_exception.h"
#include <sstream>
#include <iterator>

namespace savfe
{

static void analyze_behavior_input(const std::string& command, const std::vector<std::string>& arguments);

bool analyze_input(const std::string& input)
{
	std::istringstream iss(input);
	std::string command;
	// skip leading whitespaces
	iss >> std::ws >> command;
	std::vector<std::string> arguments { std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{ } };

	if(command == "add" || command == "a")
	{
		if(arguments.empty())
			throw Error_Exception(MSG::NO_FILE_TO_ADD_SPECIFIED);
		else
			throw Add_Exception(arguments);
	}
	else if(command == "ignore" || command == "i")
	{
		if(arguments.empty())
			throw Error_Exception(MSG::NO_FILE_TO_IGNORE_SPECIFIED);
		else
			throw Add_Exception(arguments, true);
	}
	else if(command == "remove" || command == "r" || command == "x")
	{
		if(arguments.empty())
			throw Error_Exception(MSG::NO_FILE_TO_REMOVE_SPECIFIED);
		else
			throw Remove_Exception(arguments);
	}
	else if(command == "R" || command == "run" || command == "u" || command == "update")
		throw Run_Exception();
	else if((command == "d" || command == "destination"))
		throw Destination_Exception(arguments.back());
	else if(command == "list" || command == "l")
		throw List_Exception();
	else if(command == "clear")
		throw Clear_Exception();
	else if(command == "help" || command == "h" || command == "?")
		throw Help_Exception();
	else if(command == "log")
		throw Log_Exception();
	else if(command == "config")
		throw Config_Exception();
	else if(command == "behavior")
		analyze_behavior_input(command, arguments);
	else if(command == "check")
		throw Check_Exception();
	else if(command == "quit" || command == "q" || command == "exit")
		return false;
	else if(command == "")
		return true;
	else
		throw Error_Exception(MSG::UNKNOWN_COMMAND_W_ARG, command, Help_Exception::get_help());

	return true;
}

void analyze_behavior_input(const std::string& command, const std::vector<std::string>& arguments)
{
	Configuration::Already_Existing_Behavior aeb;
	Configuration::Symlinks_Behavior sb;

	if(!arguments.empty())
	{
		try
		{
			int temp = std::stoul(arguments.front());
			if(temp == 0 || temp == 1 || temp == 2 || temp == 4)
				aeb = static_cast<Configuration::Already_Existing_Behavior>(temp);
			else
				throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, arguments.front());
		}
		catch(const std::invalid_argument&)
		{
			throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, arguments.front());
		}
		if(arguments.size() == 2)
		{
			try
			{
				int temp = std::stoul(arguments[1]);
				if(temp == 0 || temp == 16 || temp == 32)
					sb = static_cast<Configuration::Symlinks_Behavior>(temp);
				else
					throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, arguments[1]);
			}
			catch(const std::invalid_argument&)
			{
				throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, arguments[1]);
			}

			throw Behavior_Exception(aeb, sb);
		}
	}

	throw Error_Exception(MSG::NEEDS_ARGUMENT_W_ARG, command);
}

}
