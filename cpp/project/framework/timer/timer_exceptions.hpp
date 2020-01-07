#ifndef ILRD_TIMER_EXCEPTIONS_HPP
#define ILRD_TIMER_EXCEPTIONS_HPP

#include <stdexcept>    /* exceptions */

namespace ilrd
{

namespace timer
{

class Exception : public std::runtime_error
{
public:
    explicit Exception(const char *msg = "Timer Exception\n");
};

class EmptyFunction : public Exception
{
public:
    explicit EmptyFunction(const char *msg = "Timer Exception: Empty Function\n");
};

class BadFD : public Exception
{
public:
    explicit BadFD(const char *msg = "Timer Exception: Bad File Descriptor\n");
};

class BadTimerFD : public Exception
{
public:
    explicit BadTimerFD(const char *msg = "Timer Exception: Bad File Descriptor\n");
};


} // timer

} // ilrd

#endif
