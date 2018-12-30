#ifndef BEHAVIOR_EXCEPTION_H
#define BEHAVIOR_EXCEPTION_H

#include "exceptions.h"
#include "../settings.h"

struct Behavior_Exception : public Exception
{
	Behavior_Exception(Configuration::Already_Existing_Behavior aeb,
			Configuration::Symlinks_Behavior sb) : aeb(aeb), sb(sb) {	}
	Configuration::Already_Existing_Behavior aeb;
	Configuration::Symlinks_Behavior sb;

	virtual void exec() const override
	{
		if((sb == 0 || sb == 16 || sb == 32) &&
			(aeb == 0 || aeb == 1 || aeb == 2 || aeb == 4))
				set_behavior(aeb, sb);
	}

	virtual const char* which() const override
	{
		return "Behavior_Exception";
	}
};

#endif // BEHAVIOR_EXCEPTION_H
