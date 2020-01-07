/***********************************
*                                  *
*   OS - Simple Shell              *
*   written by: Hadar Klein        *
*   reviewed by: Dafna Cohen       *
*                                  *
***********************************/

#include <stdio.h>      /* print  */
#include <assert.h>     /* assert */
#include <unistd.h>     /* fork   */
#include <sys/types.h>  /* pid    */
#include <sys/wait.h>   /* wait   */
#include <stdlib.h>     /* malloc */
#include <string.h>     /* strtok */

#include "utils.h"

#define ARR_SIZE 100
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define NORMAL "\x1B[0m"
#define IDENTICAL 0

static int CreateChildProcessWithForkChar(char *user_input);
static void RaisePrompt();
static void CreateArgv(char *user_input, char **argv);

int main(int argc, char **argv)
{
    while(1)
    {
        char user_input[ARR_SIZE] = {0};
        int child_status = 0;

        UNUSED(argc);
        UNUSED(argv);

        RaisePrompt();
        fgets(user_input, 100, stdin);

        if (IDENTICAL == strcmp(user_input, "exit\n"))
        {
            break;
        }
        if ('\n' == *user_input)
        {
            continue;
        }

        CreateChildProcessWithForkChar(user_input);
        wait(&child_status);
        if (WIFEXITED(child_status))
        {
            if (0 != WEXITSTATUS(child_status))
            {
                printf("there was an error during execution with exist \
                status:%d\n", child_status);
            }
        }
        else
        {
            printf("the child process exited abnormally\n");
        }
    }

    printf("exiting\n");

    return 0;
}


static void RaisePrompt()
{
    char *username = NULL;
    char hostname[ARR_SIZE] = {0};
    char curr_dir[ARR_SIZE] = {0};

    username = getenv("USER");
    if (0 != gethostname(hostname, sizeof(hostname)))
    {
        perror("There was an error while attempting to retrieve the hostname\n");
    }
    
    if (NULL == getcwd(curr_dir, sizeof(curr_dir)))
    {
        perror("There was an error while attempting to retrieve the cwd\n");
    }


    printf("%s%s@%s%s:%s~%s%s$",GREEN, username, hostname,
                                NORMAL, BLUE, curr_dir, NORMAL);

}
static int CreateChildProcessWithForkChar(char *user_input)
{
    pid_t child_pid = 0;
    char *argv[ARR_SIZE] = {0};

    assert(NULL != user_input);

    /* if (IDENTICAL == strcmp(user_input, ""))
    {
        return 0;
    } */

    CreateArgv(user_input, argv);

    child_pid = fork();

    if (0 != child_pid)
    {
        return child_pid;
    }
    else
    {
        execvp(argv[0], argv);
        perror("an error occured while running the command\n");
        abort();
    }
}

static void CreateArgv(char *user_input, char **argv)
{
    int i = 0;

    assert(NULL != user_input);
    assert(NULL != argv);
    
    argv[i] = strtok(user_input, " \n");

    while (NULL != argv[i])
    {
        ++i;
        argv[i] = strtok(NULL, " \n");
        
    }
}

