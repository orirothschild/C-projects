#define _POSIX_C_SOURCE 200809

#include <stdio.h>      /* printf */
#include <unistd.h>     /* close */
#include <errno.h>      /* errno, perror */
#include <string.h>     /* memset */
#include <netdb.h>      /* addrinfo */
#include "tcp_server.h" /* API */

const char *g_TCP_PORT = "7203";
const int g_TCP_BACKLOG = 20;
const char *g_TCP_ADDRESS = NULL;
#define g_MAX_DATA_SIZE (100)


/* int RunServer(); */

/* int main()
{
    int retval = RunTCPServer();
    if (0 != retval)
    {
        printf("retval is : %d\n", retval);
        perror("blerg");
        return __LINE__;
    }

    return 0;
} */


void TCPInitAddrinfo(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
}


int GetSocketFD()
{
    int sockfd = 0;
    int retval = 0;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p;
    int yes = 1;

    TCPInitAddrinfo(&hints);

    retval = getaddrinfo(g_TCP_ADDRESS, g_TCP_PORT, &hints, &servinfo);
    if (0 != retval)
    {
        return __LINE__;
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
            perror("error in setsockopt");
            return __LINE__;
        }

        retval = bind(sockfd, p->ai_addr, p->ai_addrlen);
        if (-1 == retval)
        {
            close(sockfd);
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);

    if (p == NULL)
    {
        return __LINE__;
    }

    return sockfd;
}


int Handshake(int sockfd)
{
    int retval = 0;
    int fd = 0;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);

    retval = listen(sockfd, g_TCP_BACKLOG);
    if (-1 == retval)
    {
        return __LINE__;
    }

    printf("server waiting for connection\n");

    fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    if (-1 == fd)
    {
        return __LINE__;
    }

    return fd;
}


int RunTCPServer()
{
    int sockfd = 0;
    int newfd = 0;
    char buff[g_MAX_DATA_SIZE];
    int retval = 0;
    int num_of_bytes = 0;
    int n = 10;

    sockfd = GetSocketFD();
    if (-1 == sockfd)
    {
        perror("GetSocket:");
        return __LINE__;
    }

    newfd = Handshake(sockfd);
    if (-1 == newfd)
    {
        perror("Hanshake:");
        return __LINE__;
    }
    printf("newfd is :%d\n", newfd);

    while(n)
    {
        num_of_bytes = recv(newfd, buff, g_MAX_DATA_SIZE -1, 0);
        if (-1 == num_of_bytes)
        {
            return __LINE__;
        }

        buff[num_of_bytes] = '\0';
        printf("client: received message - %s\n", buff);

        retval = send(newfd, "Pong", 4, 0);
        if (-1 == retval)
        {
            return __LINE__;
        }

        --n;
    }

    close(newfd);
    close(sockfd);

    return 0;
}

