#ifndef ILRD_RECEIVER_HPP
#define ILRD_RECEIVER_HPP

#include <netdb.h>      /* addrinfo */

#include "utils.hpp"    /* utils */
namespace ilrd
{

class Receiver : private Uncopyable
{
public:
    explicit Receiver();
    ~Receiver();

    char ReceiveData(int fd, char *read_buffer, struct sockaddr *addr, socklen_t *size);

private:
    //nothing in private
};

}

#endif // ILRD_RECEIVER_HPP
