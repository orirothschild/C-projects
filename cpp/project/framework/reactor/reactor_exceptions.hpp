#ifndef ILRD_REACTOR_EXCEPTIONS_HPP
#define ILRD_REACTOR_EXCEPTIONS_HPP

#include <stdexcept>    /* exceptions */

namespace ilrd
{

namespace reactor
{

class Exception : public std::runtime_error
{
public:
    explicit Exception(const char * msg = "Reactor Exception\n");
};

class ExceptionEmptyFunction : public Exception
{
public:
    explicit ExceptionEmptyFunction(const char * msg = "Reactor Exception: Empty Function\n");
};

class ExceptionDuplicateKey : public Exception
{
public:
    explicit ExceptionDuplicateKey(const char * msg = "Reactor Exception: Duplicate Key\n");
};

class ExceptionBadFD : public Exception
{
public:
    explicit ExceptionBadFD(const char * msg = "Reactor Exception: Bad File Descriptor\n");
};

class ListenerExceptionBadFD : public ExceptionBadFD
{
public:
    explicit ListenerExceptionBadFD(const char * msg = "Listener Exception: Bad File Descriptor\n");
};

}

} // ilrd

#endif
