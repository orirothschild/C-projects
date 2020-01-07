/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/
#define _POSIX_C_SOURCE (200112L)

#include <stdio.h>      
#include <assert.h>     /* assert */
#include <sys/types.h>  /* pid    */
#include <unistd.h>     /* fork   */
#include <signal.h>     /* sigaction */
#include <stdlib.h>     /* sigaction, malloc */
#include <pthread.h>    /* threads */
#include <string.h>     /* memset */

#include "schd.h"
#include "watchdog_so.h"

enum flag
{
    ON = 0,
    OFF
};

extern int g_GRACE;
extern int g_COUNT_GRACE;
extern int g_DNR_FLAG;
extern uuid_t g_GRACECHECKUUID;
extern scheduler_t *g_SCHD;
extern char **environ;
typedef void (*handler)(int, siginfo_t *, void *);


/* void InitSignalHandler(int signum, struct sigaction sa, handler handler); */
void SigHandler_DestroySchd(int signum, siginfo_t *info, void *vp);
/* void SigHandler_ResetGrace(int signum, siginfo_t *info, void *vp); */
void SetGrace(int argc, char **argv);
/* time_t SendSignalFunc(void *param);
time_t GraceCheckFunc(void *param);
 */void WatchDog(int argc, char **argv);
/* int InitWatchDogProcess(char **argv); */
void CheckSigAction(int retval);


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
    
    printf("inside schd destroy handler in process\n");
    g_DNR_FLAG = ON;
    SchdStop(g_SCHD);
    kill(info->si_pid, SIGUSR2);
    
}
/* void SigHandler_ResetGrace(int signum, siginfo_t *info, void *vp)
{
    (void)signum;
    (void)info;
    (void)vp;

    printf("received SIGUSR1 from thread\n");
    g_COUNT_GRACE = g_GRACE;
} */

void WatchDog(int argc, char **argv)
{
    pid_t pid = getppid();
    
    g_GRACE = atoi(argv[argc - 1]);
    g_COUNT_GRACE = g_GRACE;
   
    printf("in the process wd\n");
    printf("argv[0] is %s\n", argv[0]);
    printf("argv[argc - 1] is %s\n", argv[argc - 1]);
    printf("grace is %s\n", argv[argc - 1]);
    printf("pid is %d\n", pid);
    printf("process pid is now :             %d\n", getpid());
    RunWatchDogIMP(argv, pid, argv[0], atoi(argv[argc - 1]));
}


