/***********************************
*                                  *
*   Watchdog                       *
*   written by: Hadar Klein        *
*   date: 16.2.19                  *
*   reviewed by:                   *
*                                  *
***********************************/

#define _POSIX_C_SOURCE (200112L)

#include <stdio.h>          /* debug */
#include <assert.h>         /* assert */
#include <sys/types.h>      /* pid    */
#include <unistd.h>         /* fork   */
#include <signal.h>         /* sigaction */
#include <stdlib.h>         /* sigaction, malloc */
#include <pthread.h>        /* threads */
#include <string.h>         /* memset */

#include "schd.h"           /* API */
#include "watchdog_so.h"    /* API */
#include "utils.h"          /* utils */


extern int g_GRACE;
extern int g_COUNT_GRACE;
extern int g_DNR_FLAG;
extern uuid_t g_GRACECHECKUUID;
extern scheduler_t *g_SCHD;
extern char **environ;

static void SigHandler_DestroySchd(int signum, siginfo_t *info, void *vp);
static void SetGrace(int grace);
static void WatchDog(int argc, char **argv);


int main(int argc, char **argv)
{
    struct sigaction sa1 = {0};
    struct sigaction sa2 = {0};

    memset(&sa1, 0, sizeof(sa1));
    memset(&sa2, 0, sizeof(sa2));
    
    InitSignalHandler(SIGUSR1, sa1, SigHandler_ResetGrace);
    InitSignalHandler(SIGUSR2, sa2, SigHandler_DestroySchd);

    WatchDog(argc, argv);

    return 0;
}


void SigHandler_DestroySchd(int signum, siginfo_t *info, void *vp)
{
    (void)signum;
    (void)info;
    (void)vp;
    
    printf("inside schd destroy handler in process pid is %d\n", getpid());
    g_DNR_FLAG = ON;
    SchdStop(g_SCHD);
    kill(info->si_pid, SIGUSR2);
}


void WatchDog(int argc, char **argv)
{
    pid_t pid = 0;
    
    assert(NULL != argv);

    pid = getppid();
    
    SetGrace(atoi(argv[argc - 1]));

    RunWatchDogIMP(argv, pid, argv[0]);
}


static void SetGrace(int grace)
{
    g_GRACE = grace;
    g_COUNT_GRACE = g_GRACE;
}
