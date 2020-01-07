/***********************************
*                                  *
*   PingPong - Unrelated Second    *
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

typedef void (*handler)(int, siginfo_t *, void *);

static void SigHandler(int signum, siginfo_t *info, void *vp);
static void InitSignal(int signum, handler handler, struct sigaction *act);


int main(int argc, char **argv)
{
    pid_t cousin_pid = 0;
    struct sigaction PONG = {0};

    (void)argc;

    InitSignal(SIGUSR1, SigHandler, &PONG);

    cousin_pid = atoi(argv[1]);

    kill(cousin_pid, SIGUSR2);

    while (1)
    {        
        pause();
    }

    return 0;
}


static void SigHandler(int signum, siginfo_t *info, void *vp)
{
    (void)signum;
    (void)vp;
 
    write(1, "A     Ping\n", 12);
    kill(info->si_pid, SIGUSR2);    
}


static void InitSignal(int signum, handler handler, struct sigaction *act)
{
    act->sa_sigaction = handler;
    act->sa_flags = SA_SIGINFO;

    if (0 != sigaction(signum, act, NULL))
    {
        write(1, "Error during signal handler change\n", 36);
        abort();
    }
}
