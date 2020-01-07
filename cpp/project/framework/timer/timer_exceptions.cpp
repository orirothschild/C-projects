#include "timer_exceptions.hpp"    /* API */


namespace ilrd
{

namespace timer
{

Exception::Exception(const char *msg)
: runtime_error(msg)
{}

EmptyFunction::EmptyFunction(const char *msg)
: Exception(msg)
{}

BadFD::BadFD(const char *msg)
: Exception(msg)
{}

BadTimerFD::BadTimerFD(const char *msg)
: Exception(msg)
{}

}


} // ilrd
