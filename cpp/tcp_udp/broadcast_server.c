#define _POSIX_C_SOURCE 200809

#include <stdio.h>      /* printf */
#include <unistd.h>     /* close */
#include <errno.h>      /* errno, perror */
#include <string.h>     /* memset */
#include <arpa/inet.h>  /* SOCK_DGRAM, SOL_SOCKET */


const char *gc_PORT = "8080";
const int gi_PORT = 8080;
const int g_BACKLOG = 20;
const char * g_ADDRESS = "10.1.255.255";
#define g_MAX_DATA_SIZE (100)

int RunServer();

int main()
{
    int retval = RunServer();
    if (0 != retval)
    {
        printf("%d\n", errno);
        return errno;
    }
    
    return 0;
}


int RunServer()
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

    memset(&send_to_addr, 0, sizeof(send_to_addr));
    send_to_addr.sin_family  = AF_INET;
    send_to_addr.sin_port = htons(gi_PORT);
    send_to_addr.sin_addr.s_addr = inet_addr(g_ADDRESS);
    printf("server waiting for connection\n");

    while(n)
    {
        retval = sendto(sockfd, "Ping", strlen("PING") + 1, 0,
                        (struct sockaddr *)&send_to_addr, 
                        sizeof(send_to_addr));
        if (-1 == retval)
        {
            return errno;
        }

        num_of_bytes = recvfrom(sockfd, buff, g_MAX_DATA_SIZE -1, 0,
                               (struct sockaddr *)&send_to_addr,
                               &addr_len);
        if (-1 == num_of_bytes)
        {
            return errno;
        }
        buff[num_of_bytes] = '\0';
        printf("server: received message - %s\n", buff);
        
        --n;
    }

    close(sockfd);

    return 0;
}

