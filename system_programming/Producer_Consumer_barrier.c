/***********************************
*                                  *
*   Circular Queue - Two Mutexes   *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/

#include <stdio.h>      /* fprintf */
#include <assert.h>     /* asserts */
#include <pthread.h>    /* threads */
#include <semaphore.h>  /* semaphores */

#include "utils.h"      /* utils */

#define g_NUM_OF_CONSUMERS (5)


struct thread_arg
{
    size_t idx;
};

static volatile int g_COUNTER = 0;

pthread_mutex_t mutex_access = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore;
pthread_cond_t thread_flag_cv;

static void CreateThreads();
static void *Producer(void *arg);
static void *Consumer(void *arg);


int main()
{
    CreateThreads();

    sem_destroy(&semaphore);
    pthread_mutex_destroy(&mutex_access);
    pthread_cond_destroy(&thread_flag_cv);

    return 0;
}


static void CheckRetVal(int retval, int idx, char *str)
{
    if (SUCCESS != retval)
    {
        fprintf(stderr, "there was a problem in thread number %d during %s\n",
                idx, str);
    }
}


static void CreateThreads()
{
    int i = 0;
    int retval = 0;
    pthread_t producer;
    pthread_t consumer_thread_array[g_NUM_OF_CONSUMERS];
    struct thread_arg thread_arg_array[g_NUM_OF_CONSUMERS] = {0};
    sem_init(&semaphore, 0, 0);
    pthread_cond_init(&thread_flag_cv, NULL);
    
    for (i =0; i < g_NUM_OF_CONSUMERS; ++i)
    {
        thread_arg_array[i].idx = i;
    }

    retval = pthread_create(&producer, NULL, Producer, &thread_arg_array[i]);
    CheckRetVal(retval, 0, "enqueue thread creation");

    for (i = 0; i < g_NUM_OF_CONSUMERS; ++i)
    {
        retval = pthread_create(&consumer_thread_array[i], NULL,
                                Consumer, &thread_arg_array[i]);
        CheckRetVal(retval, i, "dequeue thread creation");
    }

    retval = pthread_join(producer, NULL);
    CheckRetVal(retval, i, "enqueue thread joining");
    for (i = 0; i < g_NUM_OF_CONSUMERS; ++i)
    {
        retval = pthread_join(consumer_thread_array[i], NULL);
        CheckRetVal(retval, i, "dequeue thread  joining");
    }
}


static void *Producer(void *arg)
{
    UNUSED(arg);

    while (1)
    {
        sem_wait(&semaphore);

        printf("Producer Thread:     %lu\n", pthread_self());

        pthread_mutex_lock(&mutex_access);
        
        g_COUNTER = 0;
        
        pthread_cond_broadcast(&thread_flag_cv);
        pthread_mutex_unlock(&mutex_access);
    }

    return NULL;
}


static void *Consumer(void *arg)
{
    UNUSED(arg);

    while (1)
    {
        pthread_mutex_lock(&mutex_access);

        ++g_COUNTER;
        if (g_NUM_OF_CONSUMERS == g_COUNTER)
        {
            sem_post(&semaphore);
        }
        
        pthread_cond_wait(&thread_flag_cv, &mutex_access);
        pthread_mutex_unlock(&mutex_access);

        printf("Consumer Thread: %lu\n", pthread_self());
    }

    return NULL;
}





