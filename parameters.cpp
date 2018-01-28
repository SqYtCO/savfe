#include "parameters.h"
#include "exceptions.h"
#include "messages.h"

Data analyze_parameters(const int& args, char* argv[])
{
    Data params;

    if(args < 2)
        params.terminal = true;

    for(int i = 1; i < args; ++i)
    {
        std::string arg(argv[i]);

        if(arg == "-u" || arg == "--update")
        {
            params.update = true;
        }
        else if(arg == "-r" || arg == "--remove")
        {
            if(++i < args)
                params.removed.push_back(argv[++i]);
            else
                throw(MSG::NO_FILE_TO_REMOVE_SPECIFIED_MSG);
        }
        else if(arg == "-a" || arg == "--add")
        {
            if(++i < args)
                params.added.push_back(argv[++i]);
            else
                throw(MSG::NO_FILE_TO_ADD_SPECIFIED_MSG);
        }
        else if(arg == "-d" || arg == "--destination")
        {
            if(++i < args)
            {
                params.destination = argv[i];
                if(!std::experimental::filesystem::exists(params.destination))
                    throw No_File_Or_Directory_Exception(argv[i]);
            }
            else
                throw(MSG::NO_DIRECTORY_W_ARG);
        }
        else if(arg == "-v" || arg == "--verbose")
        {
            params.verbose = true;
        }
        else if(arg == "-l" || arg == "--list")
        {
            throw List_Exception();
        }
		else if(arg == "--log")
		{
			throw Log_Exception();
		}
		else if(arg == "--config")
		{
			Configuration::Already_Existing_Behavior aeb;
			Configuration::Symlinks_Behavior sb;

			if(++i < args)
			{
				aeb = static_cast<Configuration::Already_Existing_Behavior>(std::stoul(argv[i]));
				if(++i < args)
				{
					sb = static_cast<Configuration::Symlinks_Behavior>(std::stoul(argv[i]));
					throw Behavior_Exception(aeb, sb);
				}
			}
		}
		else if(arg == "--show-config")
		{
			throw Config_Exception();
		}
        else if(arg == "--help" || arg == "-?")
        {
            throw Parameter_Help_Exception();
        }
        else
        {
            throw Invalid_Parameter_Exception(arg);
        }
    }

    return params;
}
