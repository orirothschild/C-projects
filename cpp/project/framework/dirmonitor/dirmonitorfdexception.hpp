#ifndef ILRD_DIRMONITORFDEXCEPTIONS_HPP
#define ILRD_DIRMONITORFDEXCEPTIONS_HPP

#include <stdexcept>    /* exceptions */


namespace ilrd
{

class InotifyException : public std::runtime_error
{
public:
    explicit InotifyException(const char * msg = "Reactor Exception\n");
};

class InotifyInitExceptionBadAlloc : public InotifyException
{
public:
    explicit InotifyInitExceptionBadAlloc(const char * msg = "DirMonitorFD Exception: Bad Allocation\n");
};

class InotifyInitExceptionLimitReached : public InotifyException
{
public:
    explicit InotifyInitExceptionLimitReached(const char * msg = "DirMonitorFD Exception: Inotify Limit Reached\n");
};




class InotifyAddExceptionBadAlloc : public InotifyException
{
public:
    explicit InotifyAddExceptionBadAlloc(const char * msg = "DirMonitorFD Exception: Bad Allocation\n");
};

class InotifyAddExceptionPermissionError : public InotifyException
{
public:
    explicit InotifyAddExceptionPermissionError(const char * msg = "DirMonitorFD Exception: Permission Error\n");
};

class InotifyAddExceptionLongPath : public InotifyException
{
public:
    explicit InotifyAddExceptionLongPath(const char * msg = "DirMonitorFD Exception: Path name too long\n");
};

class InotifyAddExceptionKernelMemory : public InotifyException
{
public:
    explicit InotifyAddExceptionKernelMemory(const char * msg = "DirMonitorFD Exception: Insufficient Kernel Memory\n");
};

class InotifyAddExceptionLimitReached : public InotifyException
{
public:
    explicit InotifyAddExceptionLimitReached(const char * msg = "DirMonitorFD Exception: Inotify Limit Reached\n");
};



}


#endif // ILRD_DIRMONITORFDEXCEPTIONS_HPP