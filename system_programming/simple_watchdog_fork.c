/***********************************
*                                  *
*   OS - Simple Watchdog Fork      *
*   written by: Hadar Klein        *
*   reviewed by: Dafna Cohen       *
*                                  *
***********************************/

#include <stdio.h>      /* print  */
#include <assert.h>     /* assert */
#include <unistd.h>     /* fork   */
#include <sys/types.h>  /* pid    */
#include <sys/wait.h>   /* wait   */
#include <stdlib.h>     /* abort  */

#include "utils.h"

int CreateChildProcessWithFork(char **argv);


int main(int argc, char **argv)
{
    while(1)
    {
        int child_status = 0;

        UNUSED(argc);
        
        CreateChildProcessWithFork(argv);
        wait(&child_status);
        
        if (WIFEXITED(child_status))
        {
            printf("the child process exited normally, with exit code %d\n",
                   WEXITSTATUS(child_status));
        }
        else
        {
            printf("the child process exited abnormally\n");
        }

        sleep(1);
    }

    return 0;
}


int CreateChildProcessWithFork(char **argv)
{
    pid_t child_pid = 0;
    char *executable = argv[1];

    assert(NULL != argv);

    child_pid = fork();

    if (0 != child_pid)
    {
        return child_pid;
    }
    else
    {
        ++argv;
        execvp(executable, argv);
        perror("an error occured while running the child process\n");
        abort();
    }
    
}
