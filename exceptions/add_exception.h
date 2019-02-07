#ifndef ADD_EXCEPTION_H
#define ADD_EXCEPTION_H

#include "exception.h"
#include "success_exception.h"
#include "../settings.h"
#include "../log.h"
#include "../constants.h"
#include <string>
#include <vector>

namespace savfe
{
struct Add_Exception : public Exception
{
	Add_Exception(const std::string& file, bool ignore = false) : files_to_add({file}), ignore(ignore) {	}
	Add_Exception(const std::vector<std::string>& files, bool ignore = false) : files_to_add(files), ignore(ignore) {    }

	virtual void exec() const noexcept override
	{
		for(const auto& a : files_to_add)
		{
			try
			{
				if(!ignore)
				{
					add_path(a, FILES::LIST_NAME);
					log(("\"" + a + "\"" + std::string(" added")).c_str(), Log_Type::Info, Log_Output::Fileoutput);
					throw Success_Exception(MSG::SUCCESSFULLY_ADDED_W_ARG, a);
				}
				else
				{
					add_path(a, FILES::IGNORELIST_NAME);
					log(("\"" + a + "\"" + std::string(" ignored")).c_str(), Log_Type::Info, Log_Output::Fileoutput);
					throw Success_Exception(MSG::SUCCESSFULLY_IGNORED_W_ARG, a);
				}
			}
			catch(const Exception& exc)
			{
				exc.exec();
			}
			catch(const std::exception& exc)
			{
				log(exc.what(), Log_Type::Error, Log_Output::File_And_Stdout);
			}
		}
	}

	virtual const char* which() const noexcept override
	{
		return "Add_Exception";
	}

private:
	std::vector<std::string> files_to_add;
	bool ignore;
};
}

#endif // ADD_EXCEPTION_H
