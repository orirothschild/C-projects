/***********************************
*                                  *
*   PingPong - Father Exec         *
*   written by: Hadar Klein        *
*   reviewed by: Yoni Wainsztok    *
*                                  *
***********************************/

#define _POSIX_C_SOURCE (199309L)

#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include <sys/types.h>  /* pid    */
#include <unistd.h>     /* fork   */
#include <signal.h>     /* sigaction */
#include <stdlib.h>     /* sigaction */

enum PINGPONG {PING, PONG};

typedef void handler(int, siginfo_t *, void *);

static void SigHandler(int signum, siginfo_t *info, void *vp);
static void InitSignal(int signum, handler *handler, struct sigaction *act);
static void ForkAndExec();


int main(int argc, char **argv)
{
    struct sigaction PING = {0};
    
    (void)argc;

    InitSignal(SIGUSR2, SigHandler, &PING);

    ForkAndExec(argv);

    return 0;
}


static void ForkAndExec(char **argv)
{
    pid_t child_pid = 0;
    char *executable = argv[1];

    child_pid = fork();

    while (1)
    {
        if (0 != child_pid)
        {
            pause();
        }
        else
        {
            ++argv;
            execvp(executable, argv);
            perror("an error occured while running the child process\n");
            abort();
        }
    }
}


static void SigHandler(int signum, siginfo_t *info, void *vp)
{
    (void)signum;
    (void)vp;

    write(1, "A Pong\n", 8);
    kill(info->si_pid, SIGUSR1);
}


static void InitSignal(int signum, handler *handler, struct sigaction *act)
{
    act->sa_sigaction = handler;
    act->sa_flags = SA_SIGINFO;

    if (0 != sigaction(signum, act, NULL))
    {
        write(1, "Error during signal handler change\n", 36);
        abort();
    }
}
