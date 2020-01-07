#define _POSIX_C_SOURCE 200809

#include <stdio.h>      /* printf */
#include <unistd.h>     /* close */
#include <errno.h>      /* errno, perror */
#include <string.h>     /* memset */
#include <netdb.h>      /* addrinfo */


const char *g_PORT = "8080";
const int g_BACKLOG = 20;
const char *g_ADDRESS = NULL;
#define g_MAX_DATA_SIZE (100)

int RunClient();

int main()
{
    int retval = RunClient();
    if (0 != retval)
    {
        return errno;
    }

    return 0;
}


void InitAddrinfo(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_DGRAM;
    hints->ai_flags = AI_PASSIVE;
}

int RunClient()
{
    char buff[g_MAX_DATA_SIZE];
    int sockfd = 0;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p;
    int retval = 0;
    int num_of_bytes = 0;
    int n = 10;
    struct sockaddr send_to_addr;
    socklen_t addr_len = sizeof(send_to_addr);

    InitAddrinfo(&hints);

    retval = getaddrinfo(g_ADDRESS, g_PORT, &hints, &servinfo);
    if (0 != retval)
    {
        return errno;
    }

    for (p = servinfo; NULL != p; p = p->ai_next)
    {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (-1 == sockfd)
        {
            printf("debug1\n");
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

    printf("client connected\n");

    while(n)
    {
        retval = sendto(sockfd, "Ping", 4, 0, &send_to_addr,
                        sizeof(send_to_addr));
        if (-1 == retval)
        {
            printf("debug3\n");
            return errno;
        }
        
        num_of_bytes = recvfrom(sockfd, buff, g_MAX_DATA_SIZE -1, 0,
                                &send_to_addr, &addr_len);
        if (-1 == num_of_bytes)
        {
            printf("debug4\n");
            return errno;
        }
        buff[num_of_bytes] = '\0';
        
        printf("client: received message - %s\n", buff);

        --n;
    }

    close(sockfd);

    return 0;
}