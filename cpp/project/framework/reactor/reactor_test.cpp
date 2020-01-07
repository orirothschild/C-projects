#define _POSIX_C_SOURCE (200112L)
#include <iostream>
#include <stdio.h>  // puts                     
#include <unistd.h> // recv, send, close, sleep 
#include <errno.h>  // errno                    
#include <string.h> // memset                   
#include <netdb.h>  // getaddrinfo              
#include <stdlib.h> // exit                     
#include <iostream> // std::cout
#include <fcntl.h>  // open  
#include <boost/bind.hpp>
#include "reactor.hpp"
#include <stdexcept>
#include <exception>

#include "reactor_exceptions.hpp"


using namespace ilrd;

class StopTest
{
public:
    explicit StopTest(Reactor& reactor, const char *string) : m_reactor(reactor) { strcpy(m_string, string); }
    void Foo(int x);

private:
    char m_string[20];
    Reactor& m_reactor;
};

class TcpServer
{
public:
    explicit TcpServer(Reactor& reactor, const char *port);
    int GetTcpServerSocket();
    void StartCommunication(int fd);
    void CommunicateWithSingelClient(int socket_fd, int new_fd);

private:
    Reactor &m_reactor;
    char m_port[10];

    static const int ERROR_VALUE = -1;

    int PrepareForBind(struct addrinfo **servinfo);
    int BindSocket(int *socket_fd, struct addrinfo *servinfo);
    void SetHints(struct addrinfo *hints);
    int SetNumOfListeners(int socket_fd);
};

class UdpServer
{
public:
    explicit UdpServer(Reactor& reactor, const char *port);
    int GetUdpServerSocket();
    void CommunicateWithClient(int socket_fd);

private:
    Reactor &m_reactor;
    char m_port[10];

    static const int ERROR_VALUE = -1;

    void SetHints(struct addrinfo *hints);
    int PrepareForBind(struct addrinfo **servinfo);
    int BindSocket(int *socket_fd, struct addrinfo *servinfo);
};

class PipeReader
{
public:
    explicit PipeReader(Reactor& reactor, const char *fifo);
    int GetReadFd();
    void ActionFunc(int fd);

private:
    Reactor &m_reactor;
    char m_fifo[20];
};

int main()
{
    Reactor reactor;
    
    StopTest stopTest(reactor, "stop");
    boost::function<void(int)> f1 = boost::bind(&StopTest::Foo, stopTest, _1);
    reactor.Add(READ, 0, f1);

    TcpServer tcpServer(reactor, "8080");
    boost::function<void(int)> tcpAction = 
        boost::bind(&TcpServer::StartCommunication, tcpServer, _1);
    reactor.Add(READ, tcpServer.GetTcpServerSocket(), tcpAction);

    UdpServer udpServer(reactor, "8080");
    boost::function<void(int)> udpAction = 
        boost::bind(&UdpServer::CommunicateWithClient, udpServer, _1);
    reactor.Add(READ, udpServer.GetUdpServerSocket(), udpAction);


    reactor.Start();
/*    boost::function<void (int)> f;
    try
    {
        reactor.Add(READ, 5, f);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        //exit(0);
    }
    
    try
    {
        reactor.Add(READ, -1, udpAction);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(0);
    }

    try
    {
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
*/    
    


/* 
    try
    {
        reactor.Start();
    }
    catch(const ilrd::reactor::ReactorException& e)
    {
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cerr << e.what() << '\n';
    }
     */
    

    return 0;
}

TcpServer::TcpServer(Reactor& reactor, const char *port)
: m_reactor(reactor)
{
    strcpy(m_port, port);
}

int TcpServer::GetTcpServerSocket()
{
    int socket_fd;
    struct addrinfo *servinfo = NULL;

    if (ERROR_VALUE == PrepareForBind(&servinfo) ||
        ERROR_VALUE == BindSocket(&socket_fd, servinfo))
    {
        return ERROR_VALUE;
    }

    freeaddrinfo(servinfo);
    SetNumOfListeners(socket_fd);

    return socket_fd;
}

int TcpServer::PrepareForBind(struct addrinfo **servinfo)
{
    int status = SUCCESS;
    struct addrinfo hints;

    SetHints(&hints);

    if ((status = getaddrinfo(NULL, m_port, &hints, servinfo)) != SUCCESS)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    }

    return status;
}

int TcpServer::BindSocket(int *socket_fd, struct addrinfo *servinfo)
{
    int yes = 1;
    struct addrinfo *runner = servinfo;

    for (runner = servinfo; runner != NULL; runner = runner->ai_next)
    {
        if ((*socket_fd = socket(runner->ai_family, runner->ai_socktype,
                                 runner->ai_protocol)) == ERROR_VALUE)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == ERROR_VALUE)
        {
            perror("setsockopt");

            return ERROR_VALUE;
        }

        if (bind(*socket_fd, runner->ai_addr, runner->ai_addrlen) == ERROR_VALUE)
        {
            perror("server: bind");
            continue;
        }

        break;
    }

    if (runner == NULL)
    {
        errno = ENOTCONN;
        close(*socket_fd);

        return ERROR_VALUE;
    }

    return SUCCESS;
}

void TcpServer::SetHints(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
}

int TcpServer::SetNumOfListeners(int socket_fd)
{
    int backlog = 10;
    int status = SUCCESS;

    if ((status = listen(socket_fd, backlog)) == ERROR_VALUE)
    {
        perror("listen");
    }

    return status;
}

void TcpServer::StartCommunication(int fd)
{
    int new_fd;
    struct sockaddr_storage connector_addr;
    socklen_t sin_size = sizeof(connector_addr);

    new_fd = accept(fd,
                    (struct sockaddr *)&connector_addr,
                    &sin_size);
    if (new_fd == ERROR_VALUE)
    {
        m_reactor.Remove(READ, fd);
    }
    else
    {
        boost::function<void(int)> f = 
            boost::bind(&TcpServer::CommunicateWithSingelClient, *this, fd, _1);
        m_reactor.Add(READ, new_fd, f);
    }
}

void TcpServer::CommunicateWithSingelClient(int socket_fd, int new_fd)
{
    char buf[10];
    char msg[] = "Pong";

    if (recv(new_fd, buf, sizeof(buf), 0) <= 0)
    {
        m_reactor.Remove(READ, new_fd);
        m_reactor.Remove(READ, socket_fd);
        close(new_fd);
        close(socket_fd);
    }

    else if (0 == strcmp("Ping", buf))
    {
        if (send(new_fd, msg, sizeof(msg), 0) == ERROR_VALUE)
        {
            m_reactor.Remove(READ, new_fd);
            m_reactor.Remove(READ, socket_fd);
            close(new_fd);
            close(socket_fd);
        }
    }

    else if (0 == strcmp("exit", buf))
    {
        close(new_fd);
        close(socket_fd);
        m_reactor.Stop();
    }
}

void StopTest::Foo(int x)
{
    (void)x;

    char user_input[20];

    fgets(user_input, 20, stdin);
    user_input[strlen(user_input) - 1] = '\0';

    if (0 == strcmp(user_input, m_string))
    {
        m_reactor.Stop();
    }
}
UdpServer::UdpServer(Reactor& reactor, const char *port)
: m_reactor(reactor)
{
    strcpy(m_port, port);
}

int UdpServer::GetUdpServerSocket()
{
    int socket_fd;
    struct addrinfo *servinfo = NULL;

    if (ERROR_VALUE == PrepareForBind(&servinfo) ||
        ERROR_VALUE == BindSocket(&socket_fd, servinfo))
    {
        return ERROR_VALUE;
    }

    freeaddrinfo(servinfo);

    return socket_fd;
}

void UdpServer::CommunicateWithClient(int socket_fd)
{
    struct sockaddr_storage remote_addr;
    socklen_t input_size = sizeof(remote_addr);
    char buf[10];
    char msg[] = "Pong";

    if (ERROR_VALUE == recvfrom(socket_fd,
                                buf,
                                sizeof(buf),
                                0,
                                (struct sockaddr *)&remote_addr,
                                &input_size))
    {
        m_reactor.Remove(READ, socket_fd);
        close(socket_fd);
    }

    else if (0 == strcmp("Ping", buf))
    {
        if (ERROR_VALUE == sendto(socket_fd,
                                  msg,
                                  sizeof(msg),
                                  0,
                                  (struct sockaddr *)&remote_addr,
                                  input_size))
        {
            m_reactor.Remove(READ, socket_fd);
            close(socket_fd);
        }
    }

    else if (0 == strcmp("exit", buf))
    {
        m_reactor.Stop();
        close(socket_fd);
    }
}


void UdpServer::SetHints(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_DGRAM;
    hints->ai_flags = AI_PASSIVE;
}

int UdpServer::PrepareForBind(struct addrinfo **servinfo)
{
    int status = SUCCESS;
    struct addrinfo hints;

    SetHints(&hints);

    if ((status = getaddrinfo(NULL, m_port, &hints, servinfo)) != SUCCESS)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    }

    return status;
}

int UdpServer::BindSocket(int *socket_fd, struct addrinfo *servinfo)
{
    int yes = 1;
    struct addrinfo *runner = servinfo;

    for (runner = servinfo; runner != NULL; runner = runner->ai_next)
    {
        if ((*socket_fd = socket(runner->ai_family, runner->ai_socktype,
                                 runner->ai_protocol)) == ERROR_VALUE)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == ERROR_VALUE)
        {
            perror("setsockopt");

            return ERROR_VALUE;
        }

        if (bind(*socket_fd, runner->ai_addr, runner->ai_addrlen) == ERROR_VALUE)
        {
            perror("server: bind");
            continue;
        }

        break;
    }

    if (runner == NULL)
    {
        errno = ENOTCONN;
        close(*socket_fd);

        return ERROR_VALUE;
    }

    return SUCCESS;
}

// PipeReader::PipeReader(Reactor& reactor, const char *fifo)
// : m_reactor(reactor)
// {
//     strcpy(m_fifo, fifo);
// }

// int PipeReader::GetReadFd()
// {
//     return open(m_fifo, O_RDONLY);
// }

// void PipeReader::ActionFunc(int fd)
// {
//     char buffer[50];
//     read(fd, buffer, sizeof(buffer));
//     puts(buffer);
//     m_reactor.Remove(READ, fd);
//     close(fd);
// }
