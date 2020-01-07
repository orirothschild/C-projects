/***********************************
*                                  *
*   PingPong - Father Son          *
*   written by: Hadar Klein        *
*   reviewed by: Yoni Wainsztok    *
*                                  *
***********************************/

#define _POSIX_C_SOURCE (199309L)

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* sigaction */
#include <assert.h>     /* assert */
#include <sys/types.h>  /* pid    */
#include <unistd.h>     /* fork   */
#include <signal.h>     /* sigaction */

enum PINGPONG {PING, PONG};

pid_t parent_pid;

static void InitSonProcessAndRun();
static void SendPingPong(int arg);
static void InitPing(const struct sigaction *act);
static void InitPong(const struct sigaction *act);
static void InitPingHandler(struct sigaction *act);
static void InitPongHandler(struct sigaction *act);


int main()
{
    struct sigaction PING = {0};
    struct sigaction PONG = {0};
    InitPingHandler(&PING);
    InitPongHandler(&PONG);
    InitPing(&PING);
    InitPong(&PONG);
  
    InitSonProcessAndRun();

    return 0;
}


static void InitPing(const struct sigaction *act)
{
    if (0 != sigaction(SIGUSR1, act, NULL))
    {
        write(1, "Error during signal handler change\n", 36);
        abort();
    }
}


static void InitPong(const struct sigaction *act)
{
    if (0 != sigaction(SIGUSR2, act, NULL))
    {
        write(1, "Error during signal handler change\n", 36);
        abort();
    }
}


static void SendPingPong(int arg)
{
    switch (arg)
    {
        case SIGUSR1 :
        {
            write(1, "Father process sent a     ping\n", 32);
            break;
        }
        case SIGUSR2 :
        {
            write(1, "Son process sent a pong\n", 25);
            break;
        }
    }
}


static void InitPingHandler(struct sigaction *act)
{
    act->sa_handler = SendPingPong;
}


static void InitPongHandler(struct sigaction *act)
{
    act->sa_handler = SendPingPong;
}


static void InitSonProcessAndRun()
{
    pid_t child_pid = 0;
    sigset_t set1;
    sigset_t set2;

    sigemptyset(&set1);
    sigemptyset(&set2);
    
    child_pid = fork();
    parent_pid = getppid();

    while (1)
    {    
        if (0 != child_pid)
        {
            kill(child_pid, SIGUSR2);
            pause();     
        }
        else
        {
            kill(parent_pid, SIGUSR1);
            pause();
        }
    }
}