#define _POSIX_C_SOURCE 200809

#include <stdio.h>      /* printf */
#include <unistd.h>     /* close */
#include <string.h>     /* memset */
#include <netdb.h>      /* addrinfo */
#include <errno.h>      /* errno, perror */

const char *gc_PORT = "8080";
const int gi_PORT = 8080;
const int g_BACKLOG = 20;
#define g_MAX_DATA_SIZE (100)

int RunClient();

int main()
{
    int retval = RunClient();
    if (0 != retval)
    {
        printf("%d\n", errno);
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
    int sockfd = 0;
    char buff[g_MAX_DATA_SIZE];
    int broadcast = 1;
    int retval = 0;
    int num_of_bytes = 0;
    int n = 10;
    struct sockaddr_in send_to_addr;
    socklen_t addr_len = sizeof(send_to_addr);


    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sockfd)
    {
        perror("Socket");
    }
    retval = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
                        sizeof(broadcast));
    if (-1 == retval)
    {
        perror("error in setsockopt");
        return errno;    
    }

    send_to_addr.sin_family  = AF_INET;
    send_to_addr.sin_port = htons(gi_PORT);
    send_to_addr.sin_addr.s_addr = INADDR_ANY;

    retval = bind(sockfd, (struct sockaddr *)&send_to_addr,
                  sizeof(send_to_addr));
    if (-1 == retval)
    {
        perror("Bind");
        return errno;
    }

    printf("client sending to connection\n");

    while(n)
    {
        num_of_bytes = recvfrom(sockfd, buff, g_MAX_DATA_SIZE -1, 0,
                                (struct sockaddr *)&send_to_addr,
                                &addr_len);
        if (-1 == num_of_bytes)
        {
            return errno;
        }
        buff[num_of_bytes] = '\0';
        printf("client: received message - %s\n", buff);

        retval = sendto(sockfd, "Pong", strlen("PONG") + 1, 0,
                        (struct sockaddr *)&send_to_addr, 
                        sizeof(send_to_addr));
        if (-1 == retval)
        {
            return errno;
        }

        --n;
    }

    close(sockfd);

    return 0;
}

