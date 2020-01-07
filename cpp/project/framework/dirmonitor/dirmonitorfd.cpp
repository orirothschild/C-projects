

#include <stdexcept>
#include <errno.h>
#include <unistd.h>
#include <sys/inotify.h>    /* inotify_init */
#include <cassert>

#include "dirmonitorfd.hpp"
#include "dirmonitorfdexception.hpp"




namespace ilrd
{

DirMonitorFD::DirMonitorFD()
: m_fd(InitFDInitializer())
{}

int DirMonitorFD::InitFDInitializer()
{
    int retval = inotify_init();
    if (-1 == retval)
    {
        switch (errno)
        {
            case (EMFILE):
                throw InotifyInitExceptionBadAlloc();
                break;
            case (ENOMEM):
                throw InotifyInitExceptionLimitReached();
                break;
            default:
                assert(!"InitFDInitializer: unknown error");
        }
    }

    return retval;
}

DirMonitorFD::DirMonitorFD(DirMonitorFD& fd, const std::string& path)
: m_fd(WatchFDInitializer(fd, path))
{}

int DirMonitorFD::WatchFDInitializer(DirMonitorFD& fd, const std::string& path)
{
    int retval = inotify_add_watch(fd.GetDirMonitorFD(), path.c_str(), IN_MOVED_TO | IN_CREATE);
    if (-1 == retval)
    {
        switch (errno)
        {
            case (EACCES):
                throw InotifyAddExceptionPermissionError();
                break;
            case (ENAMETOOLONG):
                throw InotifyAddExceptionLongPath();
                break;
            case (EBADF):
                throw InotifyAddExceptionBadAlloc();
                break;
            case (ENOMEM):
                throw InotifyAddExceptionKernelMemory();
                break;
            case (ENOSPC):
                throw InotifyAddExceptionLimitReached();
                break;
            default:
                assert(!"InitFDInitializer: unknown error");
        };
    }

    return retval;
}


DirMonitorFD::~DirMonitorFD()
{
    try
    {
        close(m_fd);
    }
    catch(const std::exception& e)
    {
        //swallow
    }
}

int DirMonitorFD::GetDirMonitorFD() const
{
    return m_fd;
}




} // ilrd