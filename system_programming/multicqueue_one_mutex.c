/***********************************
*                                  *
*   Circular Queue - Two Mutexes   *
*   written by: Hadar Klein        *
*   reviewed by: Oksana Rubanov    *
*                                  *
***********************************/

#include <stdio.h>      /* fprintf */
#include <assert.h>     /* asserts */
#include <stdlib.h>     /* malloc */
#include <pthread.h>    /* threads */
#include <semaphore.h>  /* semaphores */

#include "utils.h"      /* utils */

#define Q_SIZE (10)
#define g_NUM_OF_THREADS (2)

typedef struct cqueue
{
    size_t num_of_elements_in_q;
    size_t first_element_idx;
    int cqueue[Q_SIZE];
}cqueue_t;

struct thread_arg
{
    size_t idx;
};

static void OneMutex();
static void *ThreadEnqueue(void *arg);
static void *ThreadDequeue(void *arg);
static cqueue_t *CQueueCreate();
static void CQueueDestroy(cqueue_t *cqueue);
static int OneMutexCQueueEnqueue(cqueue_t *cqueue, int data);
static int OneMutexCQueueDequeue(cqueue_t *cqueue);
static int g_INDEX = 0;

cqueue_t *g_QUEUE = NULL;
pthread_mutex_t mutex_queue_idx_access = PTHREAD_MUTEX_INITIALIZER;
sem_t g_SEM_READER;
sem_t g_SEM_WRITER;


int main()
{
    OneMutex();

    sem_destroy(&g_SEM_WRITER);
    sem_destroy(&g_SEM_READER);
    pthread_mutex_destroy(&mutex_queue_idx_access);

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


static void OneMutex()
{
    int i = 0;
    int retval = 0;
    pthread_t write_thread_array[g_NUM_OF_THREADS];
    pthread_t read_thread_array[g_NUM_OF_THREADS];
    sem_init(&g_SEM_READER, 0, 0);
    sem_init(&g_SEM_WRITER, 0, Q_SIZE);

    g_QUEUE = CQueueCreate();

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        retval = pthread_create(&write_thread_array[i], NULL,
                                      ThreadEnqueue, NULL);
        CheckRetVal(retval, i, "enqueue thread creation");
    }

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        retval = pthread_create(&read_thread_array[i], NULL,
                                      ThreadDequeue , NULL);
        CheckRetVal(retval, i, "dequeue thread creation");
    }

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        retval = pthread_join(write_thread_array[i], NULL);
        CheckRetVal(retval, i, "enqueue thread joining");
        retval = pthread_join(read_thread_array[i], NULL);
        CheckRetVal(retval, i, "dequeue thread  joining");
    }

    CQueueDestroy(g_QUEUE);
}


static cqueue_t *CQueueCreate()
{
    int i = 0;
    cqueue_t *cqueue = NULL;

    cqueue = (cqueue_t *)malloc(sizeof(cqueue_t));
    if (NULL == cqueue)
    {
        return NULL;
    }

    cqueue->num_of_elements_in_q = 0;
    cqueue->first_element_idx = 0;
    for (i = 0; i < Q_SIZE; ++i)
    {
        cqueue->cqueue[i] = 0;
    }

    return cqueue;
}


static void CQueueDestroy(cqueue_t *cqueue)
{
    free(cqueue);
}


static void *ThreadEnqueue(void *arg)
{
    UNUSED(arg);

    while (1)
    {
        OneMutexCQueueEnqueue(g_QUEUE, g_INDEX);
        ++g_INDEX;
        if (Q_SIZE == g_INDEX)
        {
            g_INDEX = 0;
        }
    }

    return NULL;
}


static void *ThreadDequeue(void *arg)
{
    UNUSED(arg);

    while (1)
    {
        OneMutexCQueueDequeue(g_QUEUE);
    }
    
    return NULL;
}


static int OneMutexCQueueEnqueue(cqueue_t *cqueue, int data)
{
    size_t idx = 0;
    
    assert(NULL != cqueue);

    sem_wait(&g_SEM_WRITER);
    pthread_mutex_lock(&mutex_queue_idx_access);
    
    if (Q_SIZE <= cqueue->num_of_elements_in_q)
    {
        return FAILURE;
    }
    idx = (cqueue->first_element_idx + cqueue->num_of_elements_in_q) % Q_SIZE;
    ++cqueue->num_of_elements_in_q;
    cqueue->cqueue[idx] = data;
    printf("enqueued %d data into index %lu\n",data, idx);
    pthread_mutex_unlock(&mutex_queue_idx_access);
    
    sem_post(&g_SEM_READER);

    return 0;
}


static int OneMutexCQueueDequeue(cqueue_t *cqueue)
{
    int retval = 0;
    int tmp_idx = 0;   

    assert(NULL != cqueue);

    sem_wait(&g_SEM_READER);
    pthread_mutex_lock(&mutex_queue_idx_access);

    retval = cqueue->cqueue[cqueue->first_element_idx];
    
    tmp_idx = cqueue->first_element_idx;
    printf("dequeued %d data into index %d\n",retval, tmp_idx);
    ++tmp_idx;
    cqueue->first_element_idx = tmp_idx % Q_SIZE;
    --cqueue->num_of_elements_in_q;
    
    pthread_mutex_unlock(&mutex_queue_idx_access);
    sem_post(&g_SEM_WRITER);
    
    return retval; 
}
