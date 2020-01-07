#define _POSIX_C_SOURCE 200809

#include <stdio.h>      /* printf */
#include <unistd.h>     /* clsoe */
#include <errno.h>      /* errno, perror */
#include <string.h>     /* memset */
#include <netdb.h>      /* addrinfo */
#include "udp_server.h" /* API */


const char *g_UDP_PORT = "8080";
const int g_UDP_BACKLOG = 20;
const char *g_UDP_ADDRESS = NULL;
#define g_MAX_DATA_SIZE (100)


/* int main()
{
    int retval = RunUDPServer();
    if (0 != retval)
    {
        printf("%d\n", errno);
        perror("blerg: ");
        return errno;
    }
    
    return 0;
} */

int RunUDPServer()
{
    int sockfd = 0;
    char buff[g_MAX_DATA_SIZE];
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p;
    int yes = 1;
    int retval = 0;
    int num_of_bytes = 0;
    int n = 10;
    struct sockaddr send_to_addr;
    socklen_t addr_len = sizeof(send_to_addr);

    UDPInitAddrinfo(&hints);

    retval = getaddrinfo(g_UDP_ADDRESS, g_UDP_PORT, &hints, &servinfo);
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

    send_to_addr = *(p->ai_addr);

    freeaddrinfo(servinfo);

    if (p == NULL)
    {
        return errno;
    }

    printf("server waiting for connection\n");

    while(n)
    {
        num_of_bytes = recvfrom(sockfd, buff, g_MAX_DATA_SIZE -1, 0,
                                &send_to_addr, &addr_len);
        if (-1 == num_of_bytes)
        {
            return errno;
        }

        buff[num_of_bytes] = '\0';
        printf("client: received message - %s\n", buff);

        retval = sendto(sockfd, "Pong", 4, 0, &send_to_addr, 
                        sizeof(send_to_addr));
        if (-1 == retval)
        {
            return errno;
        }

        /* --n; */
    }

    close(sockfd);

    return 0;
}

void UDPInitAddrinfo(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_DGRAM;
    hints->ai_flags = AI_PASSIVE;
}
