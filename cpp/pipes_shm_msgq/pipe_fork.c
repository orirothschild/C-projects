#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>



void CheckReturnVal(int i, const char *msg)
{
    if (-1 == i)
    {
        fprintf(stderr, "there was a problem during %s\n", msg);
        perror("");
        abort();
    }
}

int main()
{
    int retval = 0;
    int ping_fds[2];
    int pong_fds[2];
    
    int ping_read_fd  = 0;
    int ping_write_fd = 0;
    int pong_read_fd  = 0;
    int pong_write_fd = 0;
    pid_t pid;

    retval = pipe(ping_fds);
    CheckReturnVal(retval, "ping pipe creation");
    retval = pipe(pong_fds);
    CheckReturnVal(retval, "pong pipe creation");

    ping_write_fd = ping_fds[1];
    pong_write_fd = pong_fds[1];

    pong_read_fd  = ping_fds[0];
    ping_read_fd  = pong_fds[0];
    

    pid = fork();
    CheckReturnVal(pid, "fork");
    if (0 != pid)
    {
        /* this is the parent. it should send ping and read pong*/
        char buffer[1024];
        int retval = 0;
        
        retval = close(pong_read_fd);
        CheckReturnVal(retval, "pong_read_fd");
        retval = close(pong_write_fd);
        CheckReturnVal(retval, "pong_write_fd");
        
        while(1)
        {
            /* printf("in parent process\n"); */

            retval = write(ping_write_fd, "ping ",5);
            CheckReturnVal(retval, "writing - parent");

            retval = read(ping_read_fd, buffer, 5);
            CheckReturnVal(retval, "reading - parent");
            
            printf("%s\n", buffer);
            /* sleep(1); */
        }

        retval = close(ping_write_fd);
        CheckReturnVal(retval, "ping_write_fd");
        retval = close(ping_read_fd);
        CheckReturnVal(retval, "ping_read_fd");
    }
    else
    {
        /* this is the child. it should read ping and send pong*/
        char buffer[1024];
        int retval = 0;
        
        retval = close(ping_read_fd);
        CheckReturnVal(retval, "ping_read_fd");
        retval = close(ping_write_fd);
        CheckReturnVal(retval, "ping_write_fd");

        while(1)
        {
            /* printf("in child process\n"); */
            
            retval = read(pong_read_fd, buffer, 6);
            CheckReturnVal(retval, "reading - child");
            printf("%s\n",buffer);

            retval = write(pong_write_fd, "pong", 5);
            CheckReturnVal(retval, "writing - child");
            /* sleep(1); */
        }

        retval = close(pong_read_fd);
        CheckReturnVal(retval, "pong_read_fd");
        retval = close(pong_write_fd);
        CheckReturnVal(retval, "pong_write_fd");
    }
    



}