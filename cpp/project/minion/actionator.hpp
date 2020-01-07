#ifndef ILRD_ACTIONATOR_HPP
#define ILRD_ACTIONATOR_HPP

#include <netdb.h>              /* addrinfo */
#include "reactor_header.hpp"

namespace ilrd
{

class Actionator;

typedef boost::shared_ptr<Actionator> (*Creator) (std::vector<void *> &args);

struct ActionatorAPI
{
    char (*GetKey)();
    Creator (*GetCreator)();
};

class Actionator
{
public:
    //explicit Actionator() {}
    //virtual ~Actionator() {}

    virtual void PerformAction(int fd, sockaddr address,
                               socklen_t addrSize, char *requestPacket) = 0;

private:
};

} // ilrd


#endif // ILRD_ACTIONATOR_HPP