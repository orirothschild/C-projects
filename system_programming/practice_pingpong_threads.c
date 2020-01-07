#include <stdio.h>
#include <pthread.h>


#include "utils.h"

const static int CLOSE_FLAG = 0;
const static int OPEN_FLAG = 1;
static int PING_FLAG = OPEN_FLAG;
static int PONG_FLAG = CLOSE_FLAG;


pthread_mutex_t PingPongMutex = PTHREAD_MUTEX_INITIALIZER;

void *PingFunc(void *arg);
void *PongFunc(void *arg);

int main()
{
    pthread_t ping_thread;
    pthread_t pong_thread;

    pthread_create(&ping_thread, NULL, PingFunc, NULL);
    pthread_create(&pong_thread, NULL, PongFunc, NULL);

    pthread_join(ping_thread, NULL);
    pthread_join(pong_thread, NULL);
   
    return 0;
}

void *PingFunc(void *arg)
{
    (void)arg;

    while (1)
    {
        while (CLOSE_FLAG == PING_FLAG)
        {}
        PONG_FLAG = CLOSE_FLAG;

        printf("PING    ");

        PONG_FLAG = OPEN_FLAG;
        PING_FLAG = CLOSE_FLAG;
    }
}


void *PongFunc(void *arg)
{
    (void)arg;

    while (1)
    {
        while(CLOSE_FLAG == PONG_FLAG)
        {}
        PING_FLAG = CLOSE_FLAG;

        printf("PONG\n");

        PING_FLAG = OPEN_FLAG;
        PONG_FLAG = CLOSE_FLAG;

    
    }
}
