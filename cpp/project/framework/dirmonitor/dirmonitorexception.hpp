#ifndef ILRD_DIRMONITORFDEXCEPTIONS_HPP
#define ILRD_DIRMONITORFDEXCEPTIONS_HPP

#include <stdexcept>    /* exceptions */


namespace ilrd
{

class DirMonitorException : public std::runtime_error
{
public:
    explicit DirMonitorException(const char * msg = "Reactor Exception\n");
};

class ExceptionBadFD : public DirMonitorException
{
public:
    explicit ExceptionBadFD(const char * msg = "DirMonitor Exception: Bad FD\n");
};

class ExceptionLimitReached : public DirMonitorException
{
public:
    explicit ExceptionLimitReached(const char * msg = "DirMonitorFD Exception:  Limit Reached\n");
};




class ExceptionBadAlloc : public DirMonitorException
{
public:
    explicit ExceptionBadAlloc(const char * msg = "DirMonitorFD Exception: Bad Allocation\n");
};

class ExceptionPermissionError : public DirMonitorException
{
public:
    explicit ExceptionPermissionError(const char * msg = "DirMonitorFD Exception: Permission Error\n");
};

class ExceptionLongPath : public DirMonitorException
{
public:
    explicit ExceptionLongPath(const char * msg = "DirMonitorFD Exception: Path name too long\n");
};

class ExceptionKernelMemory : public DirMonitorException
{
public:
    explicit ExceptionKernelMemory(const char * msg = "DirMonitorFD Exception: Insufficient Kernel Memory\n");
};




}


#endif // ILRD_DIRMONITORFDEXCEPTIONS_HPP