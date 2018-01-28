#include "input.h"
#include "exceptions.h"
#include <sstream>
#include <iterator>

void analyze_input(const std::string& input)
{
    std::istringstream iss(input);
    std::vector<std::string> words
    {
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{ }
    };

    for(std::size_t i = 0; i < words.size(); ++i)
    {
        if(words[i] == "R" || words[i] == "run")
        {
            throw Run_Exception();
        }
        else if(words[i] == "quit" || words[i] == "q" || words[i] == "exit")
        {
            throw Quit_Exception();
        }
        else if(words[i] == "add" || words[i] == "a")
        {
			// erase first element ("add")
            words.erase(words.begin());
			if(words.empty())
				throw(MSG::NO_FILE_TO_ADD_SPECIFIED_MSG);
			else
            	throw Add_Exception(words);
        }
        else if(words[i] == "remove" || words[i] == "r" || words[i] == "x")
        {
			// erase first element ("remove")
            words.erase(words.begin());
			if(words.empty())
				throw(MSG::NO_FILE_TO_REMOVE_SPECIFIED_MSG);
            else
				throw Remove_Exception(words);
        }
		else if((words[i] == "d" || words[i] == "destination"))
		{
			// erase first element ("destination")
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
		else if(words[i] == "show" && words.size() > i + 1)
        {
			++i;
			if(words[i] == "config")
				throw Config_Exception();
			else if(words[i] == "list")
				throw List_Exception();
			else if(words[i] == "log")
				throw Log_Exception();
		}
		else if(words[i] == "config")
		{
			Configuration::Already_Existing_Behavior aeb;
			Configuration::Symlinks_Behavior sb;

			if(++i < words.size())
			{
				aeb = static_cast<Configuration::Already_Existing_Behavior>(std::stoul(words[i]));
				if(++i < words.size())
				{
					sb = static_cast<Configuration::Symlinks_Behavior>(std::stoul(words[i]));
					throw Behavior_Exception(aeb, sb);
				}
			}
		}
        else if(words[i] == "")
        {
			// skip empty lines
            continue;
        }
        else
        {
            throw Invalid_Input_Exception(words[i]);
        }
    }
}
