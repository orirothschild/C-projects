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
#include <string.h>         /* memset */
#include <stdlib.h>         /* sigaction, malloc */
#include <sys/types.h>      /* pid    */
#include <unistd.h>         /* fork   */
#include <signal.h>         /* sigaction */

#include <pthread.h>        /* pthread_create */

#include "schd.h"           /* API */
#include "watchdog_so.h"    /* API */
#include "watchdog_mmi.h"   /* API */
#include "utils.h"          /* utils */


struct thread_arg
{
    char **argv;
    int argc;
    pid_t pid;
    int grace;
    sigset_t set;
};


extern int g_GRACE;
extern int g_COUNT_GRACE;
extern int g_DNR_FLAG;
extern uuid_t g_GRACECHECKUUID;
extern scheduler_t *g_SCHD;
extern char **environ;
static char *ENV_VAR = "WATCHDOG";
/* static char *WDFILE = "./wd.out"; */
static char *WDFILE = "/home/student/hadar-klein/system_programming/WatchDog/wd.out";

static void SetGrace(int grace);
static void SigHandlerSchdStop(int signum, siginfo_t *info, void *vp);
static char **InitInternalArgv(int argc, char **argv, int grace);
static void *ThreadWD(void *arg);
static int CheckThread(int rc, pid_t pid);
static void InitThreadArg(struct thread_arg *arg, char **argv,
                   int argc, pid_t child_pid, int grace, sigset_t *set);


int MMI(int argc, char **argv, int grace, pthread_t *thread)
{
    int rc = 0;
    char **internal_argv = NULL;
    char *executable = WDFILE;
    pid_t child_pid = 0;
    struct thread_arg *arg = NULL;
    struct sigaction sa1 = {0};
    struct sigaction sa2 = {0};
    sigset_t set = {0};

    assert(NULL != argv);
    assert(NULL != thread);
    assert(0 <= grace);

    memset(&sa1, 0, sizeof(sa1));
    memset(&sa2, 0, sizeof(sa2));

    arg = (struct thread_arg *)malloc(sizeof(struct thread_arg));
    
    InitSignalHandler(SIGUSR1, sa1, SigHandler_ResetGrace);
    InitSignalHandler(SIGUSR2, sa2, SigHandlerSchdStop);
    
    internal_argv = InitInternalArgv(argc, argv, grace);
    
    if (NULL == getenv(ENV_VAR))
    {
        setenv("WATCHDOG", "1", 1);
        child_pid = InitWatchDogProcess(internal_argv, executable);
    }
    else
    {
        child_pid = getppid();
    }
    
    InitThreadArg(arg, internal_argv, argc, child_pid, grace, &set);


    /* ThreadWD(arg); */
    rc = pthread_create(thread, NULL, ThreadWD, arg);
    return CheckThread(rc, child_pid);
}


static void InitThreadArg(struct thread_arg *arg, char **argv,
                          int argc, pid_t child_pid, int grace, sigset_t *set)
{
    arg->argv = argv;
    arg->argc = argc;
    arg->pid = child_pid;
    arg->grace = grace;
    sigemptyset(set);
    sigaddset(set, SIGUSR1);
	pthread_sigmask(SIG_BLOCK, set, NULL);
    arg->set = *set;
}


void DNR(pthread_t thread)
{
    g_DNR_FLAG = ON;
    printf("*************************inside DNR****************************\n");
    /* printf("*************************inside DNR****************************\n"); */
    
    pthread_join(thread, NULL);
    PRINT_IN_DEBUG("after pthread join in DNR\n");
}


static int CheckThread(int rc, pid_t pid)
{
    if (0 != rc)
    {
        fprintf(stderr, "There was an error during thread creation\n");
        kill(SIGABRT, pid);
        return FAILURE;
    }

    return SUCCESS;
}

static void SetGrace(int grace)
{
    g_GRACE = grace;
    g_COUNT_GRACE = g_GRACE;
}

static void *ThreadWD(void *arg)
{
    struct thread_arg *temp = NULL;
    char *executable = WDFILE;
    int sig = 0;

    assert(NULL != arg);

    temp = (struct thread_arg *)arg;
    
    SetGrace(temp->grace);

    sigwait(&temp->set, &sig);
    pthread_sigmask(SIG_UNBLOCK, &temp->set, NULL);

    RunWatchDogIMP(temp->argv, temp->pid, executable);

    free(temp->argv[temp->argc]);
    free(temp->argv);
    free(arg);

    return NULL;
}


static char **InitInternalArgv(int argc, char **argv, int grace)
{
    int i = 0;
    char **new_argv = NULL;
    
    assert(NULL != argv);

    new_argv = (char **)malloc((argc + 2) * sizeof(char *));
    if (NULL == new_argv)
    {
        abort();
    }
    
    for (i = 0; i < argc; ++i)
    {
        new_argv[i] = argv[i];
    }
    new_argv[i] = (char *)malloc(sizeof(size_t));

    sprintf(new_argv[i], "%d", grace);
    
    new_argv[++i] = NULL;

    return new_argv;
}


static void SigHandlerSchdStop(int signum, siginfo_t *info, void *vp)
{
    (void)signum;
    (void)info;
    (void)vp;

    PRINT_IN_DEBUG("inside schd destroy handler in thread\n");
    SchdStop(g_SCHD);
}
