#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>



void CheckReturnVal(int i, const char *msg)
{
    if (-1 == i)
    {
        fprintf(stderr, "there was a problem during %s\n", msg);
        abort();
    }
}

int main()
{
    char buffer[1024];
    int retval = 0;
    int pong_read_fd  = 0;
    int pong_write_fd = 0;

    char *fifo1 = "/tmp/fifo1";
    char *fifo2 = "/tmp/fifo2";

    pong_read_fd  = open(fifo1, O_RDONLY);
    CheckReturnVal(retval, "open fifo1");
    pong_write_fd = open(fifo2, O_WRONLY);
    if (0 > pong_read_fd)
    {
        retval = close(pong_write_fd);
        CheckReturnVal(retval, "close fifo2");
    }

    while(1)
    {
        retval = read(pong_read_fd, buffer, 6);
        CheckReturnVal(retval, "reading - child");
        
        printf("%s\n",buffer);

        retval = write(pong_write_fd, "pong", 5);
        CheckReturnVal(retval, "writing - child");
    }

    retval = close(pong_write_fd);
    CheckReturnVal(retval, "close pong_write_fd");
    retval = close(pong_read_fd);
    CheckReturnVal(retval, "close pong_read_fd");
    
    return 0;
}