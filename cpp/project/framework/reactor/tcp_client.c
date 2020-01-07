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
    hints->ai_socktype = SOCK_STREAM;
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
            continue;
        }

        retval = connect(sockfd, p->ai_addr, p->ai_addrlen);
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

    printf("client connected\n");

    while(n)
    {
       /*  memset(buff, 0, sizeof(buff)); */
        retval = send(sockfd, "Ping", 4, 0);
        if (-1 == retval)
        {
            return errno;
        }
        
        num_of_bytes = recv(sockfd, &buff[0], g_MAX_DATA_SIZE - 1, 0);
        if (-1 == num_of_bytes)
        {
            return errno;
        }
        buff[num_of_bytes] = '\0';
        
        printf("client: received message - %s\n", buff);

        --n;
        sleep(1);
    }

    close(sockfd);

    return 0;
}
