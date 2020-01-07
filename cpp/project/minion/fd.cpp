#define _POSIX_C_SOURCE 200809

#include <string.h>     /* memset */
#include <netdb.h>      /* addrinfo */
#include <unistd.h>     /* close */
#include <errno.h>      /* errno */
#include <iostream>     /* strerror */
#include <stdexcept>    /* exception */

#include "slogger_header.hpp"
#include "fd.hpp"  /* FD */

namespace ilrd
{

FD::FD(const char *address, const char *port)
: m_status(0)
, m_fdproxy_fd(InitFD(address, port))
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: Ctor" << std::endl;
}

FD::~FD()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: Dtor" << std::endl;
    
    CloseFD();
}

int FD::InitFD(const char *address, const char *port)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: Init FD" << std::endl;
    //Slogger::GetInstance().Log(Logger::DEBUG) << "FD: address: " << address << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: port: " << port << std::endl;

    struct sockaddr send_to_addr;

    return UDPGetSocketFD(&send_to_addr, address, port);
}

int FD::GetFD() const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: GetFD" << std::endl;

    return m_fdproxy_fd;
}

bool FD::GetStatus() const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: GetStatus" << std::endl;

    return m_status;
}

void FD::CloseFD()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: CloseFD" << std::endl;

    close(m_fdproxy_fd);
}

void FD::UDPInitAddrinfo(struct addrinfo *hints)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: UDPInitAddrinfo" << std::endl;

    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_DGRAM;
    hints->ai_flags = AI_PASSIVE;
}

int FD::UDPGetSocketFD(struct sockaddr *send_to_addr, const char *address,
                       const char *port)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: UDPGetSocketFD" << std::endl;
    //Slogger::GetInstance().Log(Logger::DEBUG) << "FD: address: " << address << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "FD: port: " << port << std::endl;

    int sockfd = 0;
    int retval = 0;
    int yes = 1;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p;

    UDPInitAddrinfo(&hints);
    
    retval = getaddrinfo(address, port, &hints, &servinfo);
    if (0 != retval)
    {
        Slogger::GetInstance().Log(Logger::ERROR) << "FD: getaddrinfo in fd error" << std::endl;
        throw std::runtime_error("getaddrinfo in fd error");
    }

    for (p = servinfo; NULL != p; p = p->ai_next)
    {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (-1 == sockfd)
        {
            continue;
        }

        retval = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                            sizeof(int));
        if (-1 == retval)
        {       
            Slogger::GetInstance().Log(Logger::ERROR) << "FD: setsockopt in fd error" << std::endl;
            throw std::runtime_error("setsockopt in fd error");
        }

        retval = bind(sockfd, p->ai_addr, p->ai_addrlen);
        if (-1 == retval)
        {
            close(sockfd);
            continue;
        }

        break;
    }

    *send_to_addr = *(p->ai_addr);

    freeaddrinfo(servinfo);

    if (p == NULL)
    {
        close(sockfd);
        Slogger::GetInstance().Log(Logger::ERROR) << "FD: close in fd error" << std::endl;
        throw std::runtime_error("close in fd error");
    }

    return sockfd;
}

} // ilrd


