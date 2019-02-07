#ifndef BEHAVIOR_EXCEPTION_H
#define BEHAVIOR_EXCEPTION_H

#include "exception.h"
#include "../settings.h"

namespace savfe
{
struct Behavior_Exception : public Exception
{
	Behavior_Exception(Configuration::Already_Existing_Behavior aeb,
			Configuration::Symlinks_Behavior sb) : aeb(aeb), sb(sb) {	}

	virtual void exec() const noexcept override
	{
		if((sb == 0 || sb == 16 || sb == 32) &&
			(aeb == 0 || aeb == 1 || aeb == 2 || aeb == 4))
				config.set_behavior(aeb, sb);
	}

	virtual const char* which() const noexcept override
	{
		return "Behavior_Exception";
	}

private:
	Configuration::Already_Existing_Behavior aeb;
	Configuration::Symlinks_Behavior sb;
};
}

#endif // BEHAVIOR_EXCEPTION_H
