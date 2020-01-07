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
#include <signal.h>         /* sigaction */
#include <stdlib.h>         /* sigaction */

#include <pthread.h>        /* pthread_create */

#include "schd.h"           /* API */
#include "watchdog_so.h"    /* API */
#include "utils.h"          /* utils */


int g_GRACE = 0;
int g_COUNT_GRACE = 0;
int g_DNR_FLAG = OFF;
uuid_t g_GRACECHECKUUID = {0};
scheduler_t *g_SCHD = NULL;

extern char **environ;


int InitWatchDogProcess(char **argv, char *executable)
{
    pid_t child_pid = 0;

    assert(NULL != argv);
    assert(NULL != executable);

    child_pid = fork();
    if (0 != child_pid)
    {
        return child_pid;
    }
    else
    {
        execve(executable, argv, environ);
        fprintf(stderr, "There was an error during executing %s\n", executable);
        abort();
    }
}


void CheckSigAction(int retval)
{
    if (0 != retval)
    {
        printf("Error during signal handler change\n");
        abort();
    }
}


void SigHandler_ResetGrace(int signum, siginfo_t *info, void *vp)
{
    (void)signum;
    (void)info;
    (void)vp;

    printf("received SIGUSR1 from pid %d\n", info->si_pid);
    g_COUNT_GRACE = g_GRACE;
}

void InitSignalHandler(int signum, struct sigaction sa, handler_t handler)
{
    int retval = 0;

/*     assert(NULL != &sa); */

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;

    retval = sigaction(signum, &sa, NULL);
    CheckSigAction(retval);
}

time_t SendSignalFunc(void *param)
{
    kill(*(pid_t *)param, SIGUSR1);
    printf("sent SIGUSER1 to %d from %d\n", *(pid_t*)param, getpid());

    if (ON == g_DNR_FLAG)
    {
        kill(*(pid_t *)param, SIGUSR2);
        printf("sent SIGUSER2 to %d from %d\n", *(pid_t*)param, getpid());
    }

    return time(NULL) + 3;
}


time_t GraceCheckFunc(void *param)
{
    assert(NULL != param);

    printf("grace is now: %d pid is %d\n", *(int*)param, getpid());
    if(0 == --*(int *)param)
    {
        SchdStop(g_SCHD);    
        return 0;
    }

    return time(NULL) + 3;
}


void RunWatchDogIMP(char **argv, pid_t pid, char *executable)
{
    assert(NULL != argv);
    assert(NULL != executable);
    
    printf("the pid received in the watchIMP is   %d\n", pid);
    
    g_SCHD = SchdCreate();
    
    while(OFF == g_DNR_FLAG)
    {
        SchdAdd(g_SCHD, SendSignalFunc, &pid, time(NULL));
        g_GRACECHECKUUID = SchdAdd(g_SCHD, GraceCheckFunc,
                                   &g_COUNT_GRACE, time(NULL) + 1);
    
        SchdRun(g_SCHD);
        if (OFF == g_DNR_FLAG)
        {
            kill(pid, SIGABRT);
            printf("reviving argv is %s\n", argv[0]);
            printf("reviving executable is %s\n", executable);
            pid = InitWatchDogProcess(argv, executable);
        }
    }
    
    SchdDestroy(g_SCHD);
}
