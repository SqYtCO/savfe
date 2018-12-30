#ifndef REMOVE_EXCEPTION_H
#define REMOVE_EXCEPTION_H

#include "exceptions.h"
#include "success_exception.h"
#include "../messages.h"
#include "../settings.h"
#include "../log.h"
#include <vector>
#include <string>

struct Remove_Exception : public Exception
{
	Remove_Exception(const std::string& file) { files_to_remove.push_back(file); }
	Remove_Exception(const std::vector<std::string>& files) : files_to_remove(files) {	}
	std::vector<std::string> files_to_remove;

	virtual void exec() const override
	{
		for(const auto& a : files_to_remove)
		{
			try
			{
				remove_path(a);
				log(("\"" + a + "\"" + std::string(" removed")).c_str());
				throw Success_Exception(MSG::SUCCESSFULLY_REMOVED_W_ARG, a);
			}
			catch (const Exception& exc)
			{
				exc.exec();
			}
		}
	}

	virtual const char* which() const override
	{
		return "Remove_Exception";
	}
};

#endif // REMOVE_EXCEPTION_H
