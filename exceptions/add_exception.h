#ifndef ADD_EXCEPTION_H
#define ADD_EXCEPTION_H

#include "exception.h"
#include "success_exception.h"
#include "../settings.h"
#include "../log.h"
#include <string>
#include <vector>

struct Add_Exception : public Exception
{
	Add_Exception(const std::string& file) { files_to_add.push_back(file); }
	Add_Exception(const std::vector<std::string>& files) : files_to_add(files) {    }

	virtual void exec() const noexcept override
	{
		for(const auto& a : files_to_add)
		{
			try
			{
				add_path(a);
				log(("\"" + a + "\"" + std::string(" added")).c_str());
				throw Success_Exception(MSG::SUCCESSFULLY_ADDED_W_ARG, a);
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
	std::vector<std::string> files_to_add;
};

#endif // ADD_EXCEPTION_H
