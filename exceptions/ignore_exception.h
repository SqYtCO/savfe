#ifndef IGNORE_EXCEPTION_H
#define IGNORE_EXCEPTION_H

#include "exception.h"
#include "success_exception.h"
#include "../log.h"
#include "../settings.h"
#include <vector>
#include <string>

struct Ignore_Exception : public Exception
{
	Ignore_Exception(const std::string& file) { files_to_ignore.push_back(file); }
	Ignore_Exception(const std::vector<std::string>& files) : files_to_ignore(files) {    }

	virtual void exec() const noexcept override
	{
		for(const auto& a : files_to_ignore)
		{
			try
			{
				add_ignore_path(a);
				log(("\"" + a + "\"" + std::string(" ignored")).c_str());
				throw Success_Exception(MSG::SUCCESSFULLY_IGNORED_W_ARG, a);
			}
			catch(const Exception& exc)
			{
				exc.exec();
			}
			catch(const std::exception& exc)
			{
				log(exc.what(), Log_Type::Error);
			}
		}
	}

	virtual const char* which() const noexcept override
	{
		return "Add_Exception";
	}

private:
	std::vector<std::string> files_to_ignore;
};

#endif // IGNORE_EXCEPTION_H
