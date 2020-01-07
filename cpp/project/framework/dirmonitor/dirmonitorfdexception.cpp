

#include "dirmonitorfdexception.hpp"

namespace ilrd
{

InotifyException::InotifyException(const char * msg)
: runtime_error(msg)
{}

InotifyInitExceptionBadAlloc::InotifyInitExceptionBadAlloc(const char * msg)
: InotifyException(msg)
{}

InotifyInitExceptionLimitReached::InotifyInitExceptionLimitReached(const char * msg)
: InotifyException(msg)
{}

InotifyAddExceptionBadAlloc::InotifyAddExceptionBadAlloc(const char * msg)
: InotifyException(msg)
{}

InotifyAddExceptionPermissionError::InotifyAddExceptionPermissionError(const char * msg)
: InotifyException(msg)
{}

InotifyAddExceptionLongPath::InotifyAddExceptionLongPath(const char * msg)
: InotifyException(msg)
{}

InotifyAddExceptionKernelMemory::InotifyAddExceptionKernelMemory(const char * msg)
: InotifyException(msg)
{}

InotifyAddExceptionLimitReached::InotifyAddExceptionLimitReached(const char * msg)
: InotifyException(msg)
{}

} // ilrd