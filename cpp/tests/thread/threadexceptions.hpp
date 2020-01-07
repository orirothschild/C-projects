#ifndef ILRD_THREADEXCEPTIONS_HPP
#define ILRD_THREADEXCEPTIONS_HPP

#include <stdexcept>

namespace ilrd
{
struct InsufficientResources : public std::runtime_error
{
    explicit InsufficientResources(const char *msg = "Insufficient Resources\n");
};    

struct SearchError : public std::runtime_error
{
    explicit SearchError(const char *msg = "Thread Not Found\n");
};

struct Deadlock : public std::runtime_error
{
    explicit Deadlock(const char *msg = "Deadlock Detected\n");
};

struct SelfTermination : public std::runtime_error
{
    explicit SelfTermination(const char *msg = "SelfTermination\n");
};


}


#endif //ILRD_THREADEXCEPTIONS_HPP