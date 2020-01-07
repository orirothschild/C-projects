#include <stdio.h>      /* printf */
#include <sys/stat.h>   /*  */
#include <sys/types.h>  /* pid_t */
#include <fcntl.h>      /* O_WRONLY */
#include <unistd.h>     /* pipe */
#include <stdlib.h>     /*  */
#include <string.h>     /*  */
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
    char buffer[1024];
    int retval = 0;
    int ping_write_fd = 0;
    int ping_read_fd  = 0;

    char *fifo1 = "/tmp/fifo1";
    char *fifo2 = "/tmp/fifo2";

    retval = mkfifo(fifo1, 0666);
    CheckReturnVal(retval, "fifo1");
    
    retval = mkfifo(fifo2, 0666);
    CheckReturnVal(retval, "fifo2");
    
    ping_write_fd = open(fifo1, O_WRONLY);
    CheckReturnVal(retval, "open fifo1");
    ping_read_fd  = open(fifo2, O_RDONLY);
    if (0 > ping_read_fd)
    {
        retval = close(ping_write_fd);
        CheckReturnVal(retval, "close fifo2");
    }
    
    while(1)
    {
        retval = write(ping_write_fd, "ping ",5);
        CheckReturnVal(retval, "writing - parent");

        retval = read(ping_read_fd, buffer, 5);
        CheckReturnVal(retval, "reading - parent");

        printf("%s\n", buffer);
    }

    retval = close(ping_write_fd);
    CheckReturnVal(retval, "close ping_write_fd");
    retval = close(ping_read_fd);
    CheckReturnVal(retval, "close ping_read_fd");

    return 0;
}