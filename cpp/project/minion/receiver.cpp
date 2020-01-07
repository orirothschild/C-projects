
#include <stdio.h>      /* printf */
#include <unistd.h>     /* close */
#include <errno.h>      /* errno */
#include <string.h>     /* memset, strerror */
#include <netdb.h>      /* addrinfo */
#include <stdexcept>    /* exceptions */

#include <iostream>

#define g_MAX_BUFFER_SIZE (4096 + 17)

#include "slogger_header.hpp"
#include "receiver.hpp"     /* receiver */

namespace ilrd
{

Receiver::Receiver()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Receiver: Ctor " << std::endl;
}

Receiver::~Receiver()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Receiver: Dtor " << std::endl;
}

char Receiver::ReceiveData(int fd, char *read_buffer, struct sockaddr *address, socklen_t *addrLen)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Receiver: ReceiveData " << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Receiver: FD: " << fd << std::endl;
    int flags = 0;

    int num_of_bytes = recvfrom(fd, read_buffer, g_MAX_BUFFER_SIZE, flags,
                                address, addrLen);
    if (0 >= num_of_bytes)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Receiver: recvfrom in Receiver error";
        throw std::runtime_error("recvfrom in Receiver error");
    }

    return read_buffer[0];
}

} // ilrd
