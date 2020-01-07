/***********************************
*                                  *
*   mutexex, semaphores and dlist  *
*   written by: Hadar Klein        *
*   reviewed by: Yoni Wainsztok    *
*                                  *
***********************************/

#include <stdio.h>      /* fprintf */
#include <assert.h>     /* asserts */
#include <pthread.h>    /* threads */
#include <stdlib.h>     /* exit */
#include <semaphore.h>  /* semphores */

#include "dlist.h"      /* API */
#include "utils.h"      /* utils */

#define g_NUM_OF_THREADS (100)

static void *ThreadPushFront(void *arg);
static void *ThreadPopFront(void *arg);
static void *ThreadPushFrontSemaphore(void *arg);
static void *ThreadPopFrontSemaphore(void *arg);

static void CreateThreadsAndRunMutexes();
static void CreateThreadsAndRunSemaphores();

dlist_t *g_DLIST = NULL;
pthread_mutex_t dlist_access_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t dlist_read_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t g_SEM;
struct thread_arg
{
    size_t thread_id;
    size_t idx;
};

int main()
{
    g_DLIST = DListCreate();
    if (NULL == g_DLIST)
    {
        return 1;
    }

    CreateThreadsAndRunMutexes();
    /* CreateThreadsAndRunSemaphores(); */

    DListDestroy(g_DLIST);
    
    return 0;
}


static void CreateThreadsAndRunMutexes()
{
    int i = 0;
    pthread_t write_thread_array[g_NUM_OF_THREADS];
    pthread_t read_thread_array[g_NUM_OF_THREADS];
    struct thread_arg thread_arg_array[g_NUM_OF_THREADS] = {0};

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        thread_arg_array[i].thread_id = i;
    }

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_create(&(write_thread_array[i]), NULL,
                                      ThreadPushFront, 
                                      &thread_arg_array[i]))
        {
            fprintf(stderr, "Thread number %d returned an error\n", i);
        }
    }
    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_create(&(read_thread_array[i]), NULL,
                                      ThreadPopFront, 
                                      &thread_arg_array[i]))
        {
            fprintf(stderr, "Thread number %d returned an error\n", i);
        }
    }
    
    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_join(write_thread_array[i], NULL) ||
            SUCCESS != pthread_join(read_thread_array[i], NULL) )
        {
            fprintf(stderr,"Thread number %d returned an error\n", i);
            exit(1);
        }
    }

    pthread_mutex_destroy(&dlist_access_mutex);
    pthread_mutex_destroy(&dlist_read_mutex);
}


static void *ThreadPushFront(void *arg)
{
    int i = 0;

    assert(NULL != arg);

    struct thread_arg *temp = (struct thread_arg*)arg;

    pthread_mutex_lock(&dlist_access_mutex);
    for (i = 0; i < 2; ++i)
    {
        printf("thread id %lu, inserting %d\n", temp->thread_id, i);

        if (DListIsSameIterator(DListEnd(g_DLIST), DListPushFront(g_DLIST,
                                                   &temp->thread_id)))
        {
            printf("there was a problem during allocation\n");
            return NULL;
        }
    }
    pthread_mutex_unlock(&dlist_access_mutex);
    
    return NULL;
}


static void *ThreadPopFront(void *arg)
{
    int i = 0;

    assert(NULL != arg);

    UNUSED(arg);


    pthread_mutex_lock(&dlist_read_mutex);
    while (True == DListIsEmpty(g_DLIST));
    pthread_mutex_lock(&dlist_access_mutex);

    for (i = 0; i < 2; ++i)
    {
        printf("the data was: %d\n", *(int*)DListGetData(DListBegin(g_DLIST)));
        DListPopFront(g_DLIST);
    }
    pthread_mutex_unlock(&dlist_access_mutex);
    pthread_mutex_unlock(&dlist_read_mutex);

    return NULL;
}

static void CreateThreadsAndRunSemaphores()
{
    int i = 0;
    pthread_t write_thread_array[g_NUM_OF_THREADS];
    pthread_t read_thread_array[g_NUM_OF_THREADS];
    struct thread_arg thread_arg_array[g_NUM_OF_THREADS] = {0};
    sem_init(&g_SEM, 0, 0);

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        thread_arg_array[i].thread_id = i;
    }

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_create(&(write_thread_array[i]), NULL,
                                      ThreadPushFrontSemaphore, 
                                      &thread_arg_array[i]))
        {
            fprintf(stderr, "Thread number %d returned an error\n", i);
        }
    }
    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_create(&(read_thread_array[i]), NULL,
                                      ThreadPopFrontSemaphore, 
                                      &thread_arg_array[i]))
        {
            fprintf(stderr, "Thread number %d returned an error\n", i);
        }
    }
    
    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        if (SUCCESS != pthread_join(write_thread_array[i], NULL) ||
            SUCCESS != pthread_join(read_thread_array[i], NULL) )
        {
            fprintf(stderr,"Thread number %d returned an error\n", i);
            exit(1);
        }
    }

    pthread_mutex_destroy(&dlist_access_mutex);
    sem_destroy(&g_SEM);
}

static void *ThreadPushFrontSemaphore(void *arg)
{
    struct thread_arg *temp = (struct thread_arg*)arg;

    assert(NULL != arg);

    pthread_mutex_lock(&dlist_access_mutex);

    printf("thread id %lu, inserting %d\n", temp->thread_id, temp->idx);

    if (DListIsSameIterator(DListEnd(g_DLIST), DListPushFront(g_DLIST,
                                                &temp->thread_id)))
    {
        printf("there was a problem during allocation\n");
        return NULL;
    }
    sem_post(&g_SEM);

    pthread_mutex_unlock(&dlist_access_mutex);
    
    return NULL;
}


static void *ThreadPopFrontSemaphore(void *arg)
{
    int i = 0;

    assert(NULL != arg);

    UNUSED(arg);

    sem_wait(&g_SEM);
    pthread_mutex_lock(&dlist_access_mutex);

    printf("the data was: %d\n", *(int*)DListGetData(DListBegin(g_DLIST)));
    DListPopFront(g_DLIST);

    pthread_mutex_unlock(&dlist_access_mutex);

    return NULL;
}

