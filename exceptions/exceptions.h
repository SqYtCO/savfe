#ifndef EXCEPTION_H
#define EXCEPTION_H

struct Exception
{
	virtual void exec() const = 0;
	virtual const char* which() const = 0;
};

#endif // EXCEPTION_H
