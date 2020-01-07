#define _POSIX_C_SOURCE (200112L)

#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "schd.h"
#include "watchdog_so.h"

enum flag
{
    ON = 0,
    OFF
};

int g_GRACE = 0;
int g_COUNT_GRACE = 0;
int g_DNR_FLAG = OFF;
uuid_t g_GRACECHECKUUID = {0};
scheduler_t *g_SCHD = NULL;

extern char **environ;

int InitWatchDogProcess(char **argv, char *executable)
{
    pid_t child_pid = 0;

    child_pid = fork();
    if (0 != child_pid)
    {
        return child_pid;
    }
    else
    {
        setenv("WATCHDOG", "1", 1);
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

    printf("received SIGUSR1 from pid %d\n", getpid());
    g_COUNT_GRACE = g_GRACE;
}

void InitSignalHandler(int signum, struct sigaction sa, handler_t handler)
{
    int retval = 0;
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
        /* SchdStop(g_SCHD); */
        
        printf("sent SIGUSER2 to %d from %d\n", *(pid_t*)param, getpid());
    }

    return time(NULL) + 3;
}


time_t GraceCheckFunc(void *param)
{
    printf("inside checker\n");
    printf("grace is now: %d pid is %d\n", *(int*)param, getpid());
    if(0 == --*(int *)param)
    {
        SchdStop(g_SCHD);    
        return 0;
    }

    return time(NULL) + 3;
}


void RunWatchDogIMP(char **argv, pid_t pid, char *executable, int grace)
{
    /* g_GRACE = grace;
    g_COUNT_GRACE = g_GRACE; */
    printf("the pid received in the watchIMP is                 %d\n", pid);
    printf("after grace %d\n", grace);
    printf("after g_grace %d\n", g_GRACE);

    g_SCHD = SchdCreate();
    printf("after schd create\n");

    while(OFF == g_DNR_FLAG)
    {
        printf("inside while\n");
        SchdAdd(g_SCHD, SendSignalFunc, &pid, time(NULL));
        g_GRACECHECKUUID = SchdAdd(g_SCHD, GraceCheckFunc,
                                   &g_COUNT_GRACE, time(NULL) + 1);
        printf("right before running the schd first time\n");
        SchdRun(g_SCHD);
        printf("after schd run %d\n", getpid());
        if (OFF == g_DNR_FLAG)
        {
            printf("reviving argv is %s\n", argv[0]);
            printf("reviving executable is %s\n", executable);
            pid = InitWatchDogProcess(argv, executable);
        }
    }
    printf("before schddestroy in pid %d\n", getpid());
    SchdDestroy(g_SCHD);
    printf("after schddestroy in pid %d\n", getpid());
}
