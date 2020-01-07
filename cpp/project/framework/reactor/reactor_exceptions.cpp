#include "reactor_exceptions.hpp"    /* API */


namespace ilrd
{

namespace reactor
{

Exception::Exception(const char * msg)
: runtime_error(msg)
{}

ExceptionEmptyFunction::ExceptionEmptyFunction(const char * msg)
: Exception(msg)
{}

ExceptionDuplicateKey::ExceptionDuplicateKey(const char * msg)
: Exception(msg)
{}

ExceptionBadFD::ExceptionBadFD(const char * msg)
: Exception(msg)
{}

ListenerExceptionBadFD::ListenerExceptionBadFD(const char * msg)
: ExceptionBadFD(msg)
{}

}

} // ilrd
