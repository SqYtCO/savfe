#include "input.h"
#include "exceptions/run_exception.h"
#include "exceptions/quit_exception.h"
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
#include "exceptions/invalid_input_exception.h"
#include "exceptions/check_exception.h"
#include <sstream>
#include <iterator>

void analyze_input(const std::string& input)
{
	std::istringstream iss(input);
	std::vector<std::string> words { std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{ } };

	for(std::size_t i = 0; i < words.size(); ++i)
	{
		if(words[i] == "R" || words[i] == "run" || words[i] == "u" || words[i] == "update")
		{
			throw Run_Exception();
		}
		else if(words[i] == "quit" || words[i] == "q" || words[i] == "exit")
		{
			throw Quit_Exception();
		}
		else if(words[i] == "add" || words[i] == "a")
		{
			// erase first element (="add")
			words.erase(words.begin());
			if(words.empty())
				throw Error_Exception(MSG::NO_FILE_TO_ADD_SPECIFIED);
			else
				throw Add_Exception(words);
		}
		else if(words[i] == "remove" || words[i] == "r" || words[i] == "x")
		{
			// erase first element (="remove")
			words.erase(words.begin());
			if(words.empty())
				throw Error_Exception(MSG::NO_FILE_TO_REMOVE_SPECIFIED);
			else
				throw Remove_Exception(words);
		}
		else if((words[i] == "d" || words[i] == "destination"))
		{
			// erase first element (="destination")
			words.erase(words.begin());
			throw Destination_Exception(words.back());
		}
		else if(words[i] == "list" || words[i] == "l")
		{
			throw List_Exception();
		}
		else if(words[i] == "clear" && words.size() > i + 1)
		{
			if(words[++i] == "list")
				throw Clear_Exception();
		}
		else if(words[i] == "help" || words[i] == "h" || words[i] == "?")
		{
			throw Help_Exception();
		}
		else if(words[i] == "log")
		{
			throw Log_Exception();
		}
		else if(words[i] == "config")
		{
			throw Config_Exception();
		}
		else if(words[i] == "behavior")
		{
			Configuration::Already_Existing_Behavior aeb;
			Configuration::Symlinks_Behavior sb;

			if(++i < words.size())
			{
				try
				{
					int temp = std::stoul(words[i]);
					if(temp == 0 || temp == 1 || temp == 2 || temp == 4)
						aeb = static_cast<Configuration::Already_Existing_Behavior>(temp);
					else
						throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, words[i]);
				}
				catch(const std::invalid_argument&)
				{
					throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, words[i]);
				}
				if(++i < words.size())
				{
					try
					{
						int temp = std::stoul(words[i]);
						if(temp == 0 || temp == 16 || temp == 32)
							sb = static_cast<Configuration::Symlinks_Behavior>(temp);
						else
							throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, words[i]);
					}
					catch(const std::invalid_argument&)
					{
						throw Error_Exception(MSG::IS_NO_VALID_BEHAVIOR_W_ARG, words[i]);
					}

					throw Behavior_Exception(aeb, sb);
				}
			}
			else
				throw Error_Exception(MSG::NEEDS_ARGUMENT_W_ARG, words[i - 1]);
		}
		else if(words[i] == "check")
		{
			throw Check_Exception();
		}
		else if(words[i] == "")
		{
			// skip empty lines
			continue;
		}
		else
		{
			throw Error_Exception(MSG::UNKNOWN_COMMAND_W_ARG, words[i], Help_Exception::get_help());
		}
	}
}
