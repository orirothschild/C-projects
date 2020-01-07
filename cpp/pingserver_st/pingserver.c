#define _POSIX_C_SOURCE 200809

#include <stdio.h>         /* printf */
#include <stdlib.h>        /* exit */
#include <unistd.h>        /* close */
#include <errno.h>         /* errno, perror */
#include <string.h>        /* memset */
#include <netdb.h>         /* addrinfo */
#include <sys/select.h>    /* select, fd_set */
#include <pthread.h>       /* threads */
#include "./../utils.h"    /* utils */
#include "udp_server.h"    /* API */
#include "tcp_server.h"    /* API */

enum PROTOCOL
{
    UDP = 0,
    TCP
};

const char *g_PORT = "8080";
const char *g_UDP_ADDRESS = NULL;
const char *g_TCP_ADDRESS = NULL;
const int g_BACKLOG = 20;

size_t g_TCP_CONNECTIONS = 0;
#define g_MAX_BUFF_SIZE (100)

struct thread_args
{
    int sockfd;
};

void TCPInitAddrinfo(struct addrinfo *hints);

int GetSocketFD(const char *address, const char *port, int protocol);
int TCPRecvAndSend(int sockfd);
int UDPRecvAndSend(int sockfd);
int RunServers();
int RunKonsole();


int main()
{
    RunServers();

    return 0;
}


int RunServers()
{
    int stdinfd = 0;
    int tcpfd = 0;
    int udpfd = 0;
    int i = 0;
    int newfd = 0;
    int max_fd_set_size = 0;

    int retval = 0;
    int backlog_size = 20;
    struct sockaddr send_to_addr;
    socklen_t addr_len = sizeof(send_to_addr);
    fd_set active_fd_set, read_fd_set;
    
    tcpfd = GetSocketFD(g_TCP_ADDRESS, g_PORT, TCP);
    if (-1 == tcpfd)
    {
        perror("TCPGetSocket:");
        return errno;
    }
    printf("tcpfd is: %d\n", tcpfd);
    
    retval = listen(tcpfd, backlog_size);
    if (-1 == retval)
    {
        perror("Listen");
        return errno;
    }

    udpfd = GetSocketFD(g_UDP_ADDRESS, g_PORT, UDP);
    if (-1 == udpfd)
    {
        perror("UDPGetSocketFD");
        return errno;
    }
    printf("udpfd is: %d\n", udpfd);

    FD_ZERO(&active_fd_set);
    FD_SET(stdinfd, &active_fd_set);
    FD_SET(tcpfd, &active_fd_set);
    FD_SET(udpfd, &active_fd_set);


    max_fd_set_size = MAX(tcpfd, udpfd) + 1;
    while(1)
    {
        read_fd_set = active_fd_set;
        
        printf("please enter ping, numtcp or exit\n");
        retval = select(max_fd_set_size, &read_fd_set, NULL, NULL, NULL);
        if (0 > retval)
        {
            perror("Select");
            return errno;
        }
        for (i = 0; i < max_fd_set_size; ++i)
        {
            if (!FD_ISSET(i, &read_fd_set))
            {
                continue;
            }
            if (i == stdinfd)
            {
                retval = RunKonsole();
                if (0 > retval)
                {
                    perror("Konsole");
                    return errno;
                }
            }
            else if (i == tcpfd)
            {
                newfd = accept(i, &send_to_addr, &addr_len);
                if (0 > newfd)
                {
                    perror("Accept");
                    return errno;
                }
                FD_SET(newfd, &active_fd_set);
                max_fd_set_size = MAX(max_fd_set_size, newfd) + 1;

                ++g_TCP_CONNECTIONS;
            }
            
            else if (i == udpfd)
            {
                retval = UDPRecvAndSend(i);
                if (0 > retval)
                {
                    perror("UDPRecvAndSend");
                    return errno;
                }
            }
            else
            {
                retval = TCPRecvAndSend(i);
                if (-1 == retval)
                {
                    perror("TCPRecvAndSend");
                    return errno;
                }
                if (-2 == retval)
                {
                    FD_CLR(i, &active_fd_set);
                }
            }
        }        
    }

    return 0;    
}

int UDPRecvAndSend(int sockfd)
{
    int num_of_bytes = 0;
    int retval = 0;
    char buff[g_MAX_BUFF_SIZE];
    struct sockaddr send_to_addr;
    socklen_t addr_len = sizeof(send_to_addr);

    num_of_bytes = recvfrom(sockfd, buff, g_MAX_BUFF_SIZE -1, 0,
                            &send_to_addr, &addr_len);
    if (-1 == num_of_bytes)
    {
        return errno;
    }
    if (0 == num_of_bytes)
    {
        return -2;
    }
    buff[num_of_bytes] = '\0';

    retval = sendto(sockfd, "Pong", 4, 0, &send_to_addr, 
                    sizeof(send_to_addr));
    if (-1 == retval)
    {
        return errno;
    }

    return 0;
}


int TCPRecvAndSend(int sockfd)
{
    size_t conversation_counter = 0;
    int retval = 0;
    char buff[g_MAX_BUFF_SIZE] = {'\0'};
    char msg[g_MAX_BUFF_SIZE] = {'\0'};
    int num_of_bytes = 0;

    num_of_bytes = recv(sockfd, buff, g_MAX_BUFF_SIZE -1, 0);
    if (0 > num_of_bytes)
    {
        perror("recv");
        return errno;
    }
    if (0 == num_of_bytes)
    {
        return -2;
    }
    
    if (!strcmp(buff, "Ping"))
    {
        ++conversation_counter;
        sprintf(msg, "Pong %lu", conversation_counter);
        retval = send(sockfd, msg, sizeof(msg) - 1, 0);
        if (-1 == retval)
        {
            return errno;
        }
    }

    return 0;
}



int RunKonsole()
{
    char input[100];
    const char *ping = "ping";
    const char *numtcp = "numtcp";
    const char *konsole_exit = "exit";

    
    scanf("%s", input);
    
    if (!strcmp(input, ping))
    {
        printf("pong\n");
    }
    else if (!strcmp(input, numtcp))
    {
        printf("number of tcp connections since starting server: %lu\n",
                g_TCP_CONNECTIONS);
    }
    else if(!strcmp(input, konsole_exit))
    {
        printf("exiting\n");
        exit(1);
    }
    else
    {
        printf("incorrect input, try again\n");
    }

    return 0;
}

int GetSocketFD(const char *address, const char *port, int protocol)
{
    int sockfd = 0;
    int retval = 0;
    int yes = 1;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p;
    
    if (UDP == protocol)
    {
        UDPInitAddrinfo(&hints);
    }
    else
    {
        TCPInitAddrinfo(&hints);    
    }
    
    retval = getaddrinfo(address, port, &hints, &servinfo);
    if (0 != retval)
    {
        return errno;
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
            return errno;
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
        return errno;
    }

    return sockfd;
}

void TCPInitAddrinfo(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
}

void UDPInitAddrinfo(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_DGRAM;
    hints->ai_flags = AI_PASSIVE;
}