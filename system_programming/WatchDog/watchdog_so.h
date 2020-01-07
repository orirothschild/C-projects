#ifndef ILRD_WATCHDOG_SO_H
#define ILRD_WATCHDOG_SO_H

/* #define _POSIX_C_SOURCE (200112L) */

#include <signal.h>
#include <stdlib.h>

enum flag
{
    ON = 0,
    OFF
};

typedef void (*handler_t)(int, siginfo_t *, void *);

int InitWatchDogProcess(char **argv, char *executable);
void InitSignalHandler(int signum, struct sigaction sa, handler_t handler);
void SigHandler_ResetGrace(int signum, siginfo_t *info, void *vp);
void CheckSigAction(int retval);
time_t SendSignalFunc(void *param);
time_t GraceCheckFunc(void *param);
void RunWatchDogIMP(char **argv, pid_t pid, char *executable);

#endif