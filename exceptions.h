#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "run.h"
#include "settings.h"
#include "help_texts.h"
#include "messages.h"
#include "log.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>    // std::transform
#include <limits>       // std::numeric_limits for std::cin.ignore()
#include <cctype>		// std::tolower

struct Exception
{
    virtual void exec() const = 0;
	virtual const char* which() const = 0;
};

struct Success_Exception : public Exception
{
    Success_Exception(const std::string& successmsg = MSG::OPERATION_SUCCESS_MSG)
        : msg(successmsg) {    }
    std::string msg;

    virtual void exec() const
    {
        std::cout << msg << '\n';
    }

	virtual const char* which() const
	{
		return "Success_Exception";
	}
};

struct Failure_Exception : public Exception
{
	Failure_Exception(const std::string& failuremsg = MSG::OPERATION_FAILURE_MSG)
		: msg(failuremsg) {		}
	std::string msg;

	virtual void exec() const
	{
		std::cerr << msg << '\n';
	}

	virtual const char* which() const
	{
		return "Failure_Exception";
	}
};

struct Run_Exception : public Exception
{
    virtual void exec() const
    {
		Configuration config;
		try
		{
			config = read_configuration();
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}

        run(config);
    }

	virtual const char* which() const
	{
		return "Run_Exception";
	}
};

// throw Quit_Exception (itself)
struct Quit_Exception : public Exception
{
	Quit_Exception(const int& ret = 0) : return_value(ret) {	}
	int return_value;

    virtual void exec() const
    {
        throw *this;
    }

	virtual const char* which() const
	{
		return "Quit_Exception";
	}
};

struct Add_Exception : public Exception
{
	Add_Exception(const std::string& file) { files_to_add.push_back(file); }
    Add_Exception(const std::vector<std::string>& files) : files_to_add(files) {    }
    std::vector<std::string> files_to_add;

    virtual void exec() const
    {
        for(const auto& a : files_to_add)
        {
            try
            {
                add_path(a);
				log(("\"" + a + "\"" + std::string(" added")).c_str());
                throw Success_Exception('\"' + a + '\"' + MSG::SUCCESSFUL_ADDED_W_ARG_MSG);
            }
            catch(const Exception& exc)
            {
                exc.exec();
            }
        }
    }

	virtual const char* which() const
	{
		return "Add_Exception";
	}
};

struct Remove_Exception : public Exception
{
	Remove_Exception(const std::string& file) { files_to_remove.push_back(file); }
    Remove_Exception(const std::vector<std::string>& files) : files_to_remove(files) {    }
    std::vector<std::string> files_to_remove;

    virtual void exec() const
    {
        for(const auto& a : files_to_remove)
        {
            try
            {
                remove_path(a);
				log(("\"" + a + "\"" + std::string(" removed")).c_str());
                throw Success_Exception('\"' + a + '\"' + MSG::SUCCESSFUL_REMOVED_W_ARG_MSG);
            }
            catch (const Exception& exc)
            {
                exc.exec();
            }
        }
    }

	virtual const char* which() const
	{
		return "Remove_Exception";
	}
};

struct Destination_Exception : public Exception
{
	Destination_Exception(const std::string& dest) : destination(dest) {	}
	std::string destination;

	virtual void exec() const
	{
		try
		{
			set_destination(destination);
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}
	}

	virtual const char* which() const
	{
		return "Destination_Exception";
	}
};

struct Behavior_Exception : public Exception
{
	Behavior_Exception(Configuration::Already_Existing_Behavior aeb,
			Configuration::Symlinks_Behavior sb) : aeb(aeb), sb(sb) {	}
	Configuration::Already_Existing_Behavior aeb;
	Configuration::Symlinks_Behavior sb;

	virtual void exec() const
	{
		if((sb == 0 || sb == 16 || sb == 32) &&
			(aeb == 0 || aeb == 1 || aeb == 2 || aeb == 4))
				set_behavior(aeb, sb);
	}

	virtual const char* which() const
	{
		return "Behavior_Exception";
	}
};

struct List_Exception : public Exception
{
    virtual void exec() const
    {
        std::ifstream in("filedirectorylist");
        std::string temp;
        while(in)
        {
            std::getline(in, temp);
            std::cout << temp << '\n';
        }
    }

	virtual const char* which() const
	{
		return "List_Exception";
	}
};

struct Clear_Exception : public Exception
{
    virtual void exec() const
    {
        std::string choice;
        std::cout << MSG::CLEAR_LIST_REQUEST_ANSWER_MSG;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::transform(choice.begin(), choice.end(), choice.begin(),
				[](unsigned char c){ return std::tolower(c); });
        if(choice == "y" || choice == "ye" || choice == "yes")
        {
            std::ofstream of("filedirectorylist", std::ios::trunc);
            log("list cleared!");
        }
		else
			std::cerr << MSG::OPERATION_CANCELED_MSG << '\n';
    }

	virtual const char* which() const
	{
		return "Clear_Exception";
	}
};

struct Log_Exception : public Exception
{
	virtual void exec() const
	{
		try
		{
			std::ifstream in("logfile");
			if(in)
			{
				std::string temp;

				while(in)
				{
					std::getline(in, temp);
					std::cout << temp << '\n';
				}
			}
			else
				throw Failure_Exception("No logfile found!");
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}
	}

	virtual const char* which() const
	{
		return "Log_Exception";
	}
};

struct Config_Exception : public Exception
{
	virtual void exec() const
	{
		try
		{
			std::ifstream in("configuration");
			if(in)
			{
				std::string temp;

				while(in)
				{
					std::getline(in, temp);
					std::cout << temp << '\n';
				}
			}
			else
				throw Failure_Exception("No configuration found!");
		}
		catch(const Exception& exc)
		{
			exc.exec();
		}
	}

	virtual const char* which() const
	{
		return "Config_Exception";
	}
};

struct Help_Exception : public Exception
{
    virtual void exec() const
    {
        std::cout << get_help();
    }

    static std::string get_help()
    {
        return HELP_TXT::TERMINAL_HELP_TXT;
    }

	virtual const char* which() const
	{
		return "Help_Exception";
	}
};

struct Parameter_Help_Exception : public Exception
{
    virtual void exec() const
    {
        std::cout << get_help() << '\n';
    }

    static std::string get_help()
    {
        return HELP_TXT::PARAMETER_HELP_TXT;
    }

	virtual const char* which() const
	{
		return "Parameter_Help_Exception";
	}
};

// throw Quit_Exception
struct Invalid_Parameter_Exception : public Exception
{
	Invalid_Parameter_Exception(const std::string& arg) : arg(arg) {	}
	std::string arg;

	virtual void exec() const
	{
		std::cerr << MSG::INVALID_ARGUMENT_W_ARG_MSG << arg << '\n'
				<< Parameter_Help_Exception::get_help();

		throw Quit_Exception();
	}

	virtual const char* which() const
	{
		return "Invalid_Parameter_Exception";
	}
};

struct Invalid_Input_Exception : public Exception
{
    Invalid_Input_Exception(const std::string& in) : input(in) {    }
    std::string input;

    virtual void exec() const
    {
        std::cout << MSG::UNKNOWN_COMMAND_W_ARG_MSG << input << '\n'
                << Help_Exception::get_help();
    }

	virtual const char* which() const
	{
		return "Invalid_Input_Exception";
	}
};

struct No_File_Or_Directory_Exception : public Exception
{
    No_File_Or_Directory_Exception(const std::string& file) { files.push_back(file); }
    No_File_Or_Directory_Exception(const std::vector<std::string>& files) : files(files) {   }
    std::vector<std::string> files;

    virtual void exec() const
    {
        for(const auto& a : files)
            std::cerr << '\"' << a << '\"' << MSG::NO_SUCH_FILE_OR_DIRECTORY_W_ARG_MSG << '\n';
    }

	virtual const char* which() const
	{
		return "No_File_Or_Directory_Exception";
	}
};

struct Already_On_The_List_Exception : public Exception
{
	Already_On_The_List_Exception(const std::string& file) : file(file) {	}
	Already_On_The_List_Exception(const std::string& file, const std::string& parent)
	 		: file(file), parent(parent) {	}
	Already_On_The_List_Exception(const std::string& file,
		const std::vector<std::string>& sub_dirs_to_be_removed)
	 		: file(file), sub_dirs(sub_dirs_to_be_removed) {	}
	std::string file;
	std::string parent;
	std::vector<std::string> sub_dirs;

	virtual void exec() const
	{
		if(!sub_dirs.empty())
		{
			std::cerr << MSG::REMOVE_TO_ADD_REQUEST_ANSWER_1_W_ARG_MSG << '\n';

			for(const auto& a : sub_dirs)
				std::cerr << MSG::REMOVE_TO_ADD_SPACES_FOR_LISTING_MSG << "- " << '\"' << a << '\"' << '\n';

			std::cerr << MSG::REMOVE_TO_ADD_REQUEST_ANSWER_2_W_ARG_MSG << '\"' << file << '\"'
					<< MSG::REMOVE_TO_ADD_REQUEST_ANSWER_3_W_ARG_MSG;

			std::string choice;
			std::cin >> choice;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::transform(choice.begin(), choice.end(), choice.begin(),
					[](unsigned char c){ return std::tolower(c); });
			if(choice == "y" || choice == "ye" || choice == "yes")
			{
				Remove_Exception(sub_dirs).exec();
				Add_Exception(file).exec();
			}
			else
				std::cerr << MSG::OPERATION_CANCELED_MSG << '\n';
		}
		else if(parent.empty())
			std::cerr << '\"' << file << '\"' << MSG::ALREADY_ON_THE_LIST_W_ARG_MSG << '\n';
		else
			std::cerr << '\"' << file << '\"' << MSG::ALREADY_ON_THE_LIST_INCLUDED_IN_PARENT_1_W_ARG_MSG
			 		<< '\"' << parent << '\"' << MSG::ALREADY_ON_THE_LIST_INCLUDED_IN_PARENT_2_W_ARG_MSG << '\n';
	}

	virtual const char* which() const
	{
		return "Already_On_The_List_Exception";
	}
};

struct Not_On_The_List_Exception : public Exception
{
    Not_On_The_List_Exception(const std::string& file) : file(file) {   }
    std::string file;

    virtual void exec() const
    {
        std::cerr << '\"' << file << '\"' << MSG::NOT_ON_THE_LIST_W_ARG_MSG << '\n';
    }

	virtual const char* which() const
	{
		return "Not_On_The_List_Exception";
	}
};

#endif // EXCEPTIONS_H
