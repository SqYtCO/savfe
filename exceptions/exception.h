#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace savfe
{
struct Exception
{
	virtual ~Exception() = default;
	virtual void exec() const noexcept = 0;
	virtual const char* which() const noexcept = 0;
};
}

#endif // EXCEPTION_H
