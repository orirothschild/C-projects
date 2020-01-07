/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/
#define _POSIX_C_SOURCE (200112L)

#include <stdio.h>
#include <assert.h>     /* asserr */
#include <string.h>     /* memset */
#include <stdlib.h>     /* sigaction, malloc */
#include <sys/types.h>  /* pid    */
#include <unistd.h>     /* fork   */
#include <signal.h>     /* sigaction */

#include <pthread.h>    /* pthread_create */

#include "schd.h" /* API */
#include "watchdog_so.h"

enum flag
{
    ON = 0,
    OFF
};
enum returns
{
    SUCCESS = 0,
    FAILURE
};

struct thread_arg
{
    char **argv;
    int argc;
    pid_t pid;
    int grace;
    sigset_t set;
};


static char *ENV_VAR = "WATCHDOG";
extern int g_GRACE;
extern int g_COUNT_GRACE;
extern int g_DNR_FLAG;
extern uuid_t g_GRACECHECKUUID;
extern scheduler_t *g_SCHD;
extern char **environ;

static char *WDFILE = 
            "/home/student/hadar-klein/system_programming/WatchDog/wd.out";

/* typedef void (*handler)(int, siginfo_t *, void *); */
void SigHandlerSchdStop(int signum, siginfo_t *info, void *vp);
/* void SigHandler_ResetGrace(int signum, siginfo_t *info, void *vp); */
/* time_t SendSignalFunc(void *param); */
/* time_t GraceCheckFunc(void *param); */
static char **InitInternalArgv(int argc, char **argv, int grace);
static void *ThreadWD(void *arg);
static int CheckThread(int rc, pid_t pid);
int MMI(int argc, char **argv, int grace, pthread_t *thread);
void DNR(pthread_t thread);
static void InitThreadArg(struct thread_arg *arg, char **argv,
                   int argc, pid_t child_pid, int grace, sigset_t *set);

int MMI(int argc, char **argv, int grace, pthread_t *thread)
{
    char **env = environ; 
    int rc = 0;
    FILE *fp = NULL;
    char **internal_argv = NULL;
    char *executable = WDFILE;
    pid_t child_pid = 0;
    struct thread_arg *arg = (struct thread_arg *)malloc(sizeof(struct thread_arg));
    /* struct thread_arg arg = {0}; */
    struct sigaction sa1 = {0};
    struct sigaction sa2 = {0};
    sigset_t set;

    memset(&sa1, 0, sizeof(sa1));
    memset(&sa2, 0, sizeof(sa2));

    assert(NULL != argv);
    assert(0 <= grace);
    
    InitSignalHandler(SIGUSR1, sa1, SigHandler_ResetGrace);
    InitSignalHandler(SIGUSR2, sa2, SigHandlerSchdStop);
    
    internal_argv = InitInternalArgv(argc, argv, grace);
    
    /* if (NULL == fopen("./WATCHDOG.txt", "r")) */
    if (NULL == getenv("WATCHDOG"))
    {
        
        child_pid = InitWatchDogProcess(internal_argv, executable);
        
        /* printf("childpid is now %d\n", child_pid); */

        
        /* fp = fopen("./WATCHDOG.txt", "w+");
        fclose(fp); */
    }
    else
    {
        child_pid = getppid();
    }
    
    InitThreadArg(arg, internal_argv, argc, child_pid, grace, &set);
    printf("argv[0] is %s\n", arg->argv[0]);
    printf("argc is %d\n", arg->argc);
    printf("childpid is is %d\n", arg->pid);
    printf("grace is %d\n", arg->grace);
    
    rc = pthread_create(thread, NULL, ThreadWD, arg);
    return CheckThread(rc, child_pid);
    /* sleep(1); */
}


void InitThreadArg(struct thread_arg *arg, char **argv,
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
    SchdRemove(g_SCHD, g_GRACECHECKUUID);

    
    printf("after schdremove in DNR\n");
    remove("./WATCHDOG.txt");
    printf("after remove file in DNR\n");
    
    printf("after pthread join in DNR\n");
    
    pthread_join(thread, NULL);
}


int CheckThread(int rc, pid_t pid)
{
    if (0 != rc)
    {
        fprintf(stderr, "There was an error during thread creation\n");
        kill(SIGABRT, pid);
        return FAILURE;
    }

    return SUCCESS;
}


static void *ThreadWD(void *arg)
{
    struct thread_arg *temp = (struct thread_arg *)arg;
    char *executable = "./wd.out";
    char **env = environ;
    /* pid_t pid = temp->pid; */
    int sig = 0;

    assert(NULL != arg);
    
    g_GRACE = temp->grace;
    g_COUNT_GRACE = g_GRACE;

    printf("thread wd, the grace is %d\n", temp->grace);
    printf("thread wd, the pid is %d\n", temp->pid);
    printf("thread wd, the argc is %d\n", temp->argc);
    printf("thread wd, the argv[0] is %s\n", temp->argv[0]);
    
    sigwait(&temp->set, &sig);
    pthread_sigmask(SIG_UNBLOCK, &temp->set, NULL);

    printf("Thread pid is now :             %d\n", getpid());
    RunWatchDogIMP(temp->argv, temp->pid, executable, temp->grace);

    /* free(temp->argv[temp->argc]); */
    free(temp->argv);

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


void SigHandlerSchdStop(int signum, siginfo_t *info, void *vp)
{
    (void)signum;
    (void)info;
    (void)vp;

    printf("inside schd destroy handler in thread\n");
    SchdStop(g_SCHD);
}
