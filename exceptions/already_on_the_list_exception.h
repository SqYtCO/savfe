#ifndef ALREADY_ON_THE_LIST_EXCEPTION_H
#define ALREADY_ON_THE_LIST_EXCEPTION_H

#include "exceptions.h"
#include "remove_exception.h"
#include "add_exception.h"
#include "../messages.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>	// std::transform
#include <limits>		// std::numeric_limits
#include <cctype>		// std::tolower

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

	virtual void exec() const override
	{
		if(!sub_dirs.empty())
		{
			std::cerr << MSG::REMOVE_TO_ADD_REQUEST_ANSWER_1_W_ARG << '\n';

			for(const auto& a : sub_dirs)
				std::cerr << MSG::REMOVE_TO_ADD_SPACES_FOR_LISTING << "- " << '\"' << a << '\"' << '\n';

			std::cerr << MSG::REMOVE_TO_ADD_REQUEST_ANSWER_2_W_ARG << '\"' << file << '\"'
					<< MSG::REMOVE_TO_ADD_REQUEST_ANSWER_3_W_ARG;

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
				std::cerr << MSG::OPERATION_CANCELED << '\n';
		}
		else if(parent.empty())
			std::cerr << '\"' << file << '\"' << MSG::ALREADY_ON_THE_LIST_W_ARG << '\n';
		else
			std::cerr << '\"' << file << '\"' << MSG::ALREADY_ON_THE_LIST_INCLUDED_IN_PARENT_1_W_ARG
			 		<< '\"' << parent << '\"' << MSG::ALREADY_ON_THE_LIST_INCLUDED_IN_PARENT_2_W_ARG << '\n';
	}

	virtual const char* which() const override
	{
		return "Already_On_The_List_Exception";
	}
};

#endif // ALREADY_ON_THE_LIST_EXCEPTION_H
