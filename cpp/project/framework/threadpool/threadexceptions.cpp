
#include <stdexcept>
#include "threadexceptions.hpp"

namespace ilrd
{

InsufficientResources::InsufficientResources(const char *msg)
: std::runtime_error(msg)
{}

SearchError::SearchError(const char *msg)
: std::runtime_error(msg)
{}

Deadlock::Deadlock(const char *msg)
: std::runtime_error(msg)
{}

SelfTermination::SelfTermination(const char *msg)
: std::runtime_error(msg)
{}

} // ilrd
