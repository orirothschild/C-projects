/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/

#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include <pthread.h>    /* pthread_create */
#include <stdlib.h>     /* abort */
#include <limits.h>     /* __sync_lock_test_and_set */

#include "utils.h"      /* utils */

#define g_ARR_SIZE (1000)

static void ProConNoBuiltins();
static void ProConBuiltins();
static void ProConOneAfterTheOther();

static void *ProducerFuncNoBuiltins(void *arg);
static void *ConsumerFuncNoBuiltins(void *arg);

static void *ProducerFuncBuiltins(void *arg);
static void *ConsumerFuncBuiltins(void *arg);

static void *ProducerFuncTwoFlags(void *arg);
static void *ConsumerFuncTwoFlags(void *arg);

static const int FLAG_OPEN = 0;
static const int FLAG_CLOSE = 1;
static const int SPINLOCK_OPENED = 0;
static const int SPINLOCK_LOCKED = 1;
static int g_INT_ARRAY[g_ARR_SIZE] = {0};
static int g_SPINLOCK_FLAG = SPINLOCK_OPENED;
static int g_WRITE_FLAG = FLAG_OPEN;
static int g_READ_FLAG = FLAG_OPEN;

static const int g_TEST_NUMBER = 300;


int main()
{
    /* ProConBuiltins(); */
    /* ProConNoBuiltins(); */
    /* ProConOneAfterTheOther(); */
    return 0;
}


void ProConOneAfterTheOther()
{
    pthread_t producer;
    pthread_t consumer;

    if (SUCCESS != pthread_create(&producer, NULL, ProducerFuncTwoFlags,
                                  NULL))
    {
        printf("There was a problem with the producer thread\n");
        abort();
    }
    if (SUCCESS != pthread_create(&consumer, NULL, ConsumerFuncTwoFlags,
                                  NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }

    if (SUCCESS != pthread_join(producer, NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }
    if (SUCCESS != pthread_join(consumer, NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }
}


void ProConNoBuiltins()
{
    pthread_t producer;
    pthread_t consumer;

    if (SUCCESS != pthread_create(&producer, NULL, ProducerFuncNoBuiltins,
                                  NULL))
    {
        printf("There was a problem with the producer thread\n");
        abort();
    }
    if (SUCCESS != pthread_create(&consumer, NULL, ConsumerFuncNoBuiltins,
                                  NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }

    if (SUCCESS != pthread_join(producer, NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }
    if (SUCCESS != pthread_join(consumer, NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }
}


void ProConBuiltins()
{
    pthread_t producer;
    pthread_t consumer;

    if (SUCCESS != pthread_create(&producer, NULL, ProducerFuncBuiltins,
                                  NULL))
    {
        printf("There was a problem with the producer thread\n");
        abort();
    }
    if (SUCCESS != pthread_create(&consumer, NULL, ConsumerFuncBuiltins,
                                  NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }

    if (SUCCESS != pthread_join(producer, NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }
    if (SUCCESS != pthread_join(consumer, NULL))
    {
        printf("There was a problem with the consumer thread\n");
        abort();
    }
}


static void *ProducerFuncNoBuiltins(void *arg)
{
    int i = 0;
    int j = 0;

    assert(NULL != arg);

    UNUSED(arg);
    
    for (i = 0; i < g_TEST_NUMBER; ++i)
    {
        while (SPINLOCK_LOCKED == g_SPINLOCK_FLAG)
        {}
        g_SPINLOCK_FLAG = SPINLOCK_LOCKED;
        printf("producer, number is %i\n", i);
        for (j = 0; j < g_ARR_SIZE; ++j)
        {
            printf("adding %d\n", i);
            g_INT_ARRAY[j] = i;
        }
        g_SPINLOCK_FLAG = SPINLOCK_OPENED;
    }

    printf("producer out\n");

    return NULL;
}


static void *ConsumerFuncNoBuiltins(void *arg)
{
    int i = 0;
    int j = 0;

    assert(NULL != arg);

    UNUSED(arg);

    for (i = 0; i < g_TEST_NUMBER; ++i)
    {
        while (SPINLOCK_LOCKED == g_SPINLOCK_FLAG)
        {}
        g_SPINLOCK_FLAG = SPINLOCK_LOCKED;
        printf("consumer, number is %i\n", g_INT_ARRAY[i]);
        for (j = 1; j < g_ARR_SIZE; ++j)
        {
            printf("reading %d\n", i);
            if (g_INT_ARRAY[j] != g_INT_ARRAY[j - 1])
            {
                printf("The array is not correct.\
                At index %d the numebr is %d, at index %d the number %d\n",
                j, g_INT_ARRAY[j], j - 1,
                g_INT_ARRAY[j - 1]);
            }
        }
        g_SPINLOCK_FLAG = SPINLOCK_OPENED;
    }

    return NULL;
}


static void *ProducerFuncBuiltins(void *arg)
{
    int i = 0;
    int j = 0;

    assert(NULL != arg);

    UNUSED(arg);

    for (i = 0; i < g_TEST_NUMBER; ++i)
    {
        while(__sync_lock_test_and_set(&g_SPINLOCK_FLAG, SPINLOCK_LOCKED));
        printf("producer, number is %i\n", i);
        for (j = 0; j < g_ARR_SIZE; ++j)
        {
            printf("adding %d   %d\n", i,j);
            g_INT_ARRAY[j] = i;
        }
        __sync_lock_release(&g_SPINLOCK_FLAG);
    }

    printf("producer out\n");

    return NULL;
}


static void *ConsumerFuncBuiltins(void *arg)
{
    int i = 0;
    int j = 0;

    assert(NULL != arg);

    UNUSED(arg);

    for (i = 0; i < g_TEST_NUMBER; ++i)
    {
        while(__sync_lock_test_and_set(&g_SPINLOCK_FLAG, SPINLOCK_LOCKED));
        printf("consumer, number is %i\n", g_INT_ARRAY[i]);
        for (j = 1; j < g_ARR_SIZE; ++j)
        {
            printf("reading %d  %d\n", i,j);
            if (g_INT_ARRAY[j] != g_INT_ARRAY[j - 1])
            {
                printf("The array is not correct.\
                At index %d the numebr is %d, at index %d the number %d\n",
                j, g_INT_ARRAY[j], j - 1,
                g_INT_ARRAY[j - 1]);
            }
        }
        __sync_lock_release(&g_SPINLOCK_FLAG);
    }

    return NULL;
}


static void *ProducerFuncTwoFlags(void *arg)
{
    int i = 0;
    int j = 0;

    assert(NULL != arg);

    UNUSED(arg);

    for (i = 0; i < g_TEST_NUMBER; ++i)
    {
        while(FLAG_CLOSE == g_READ_FLAG);
        g_WRITE_FLAG = FLAG_CLOSE;


        printf("producer, number is %i\n", i);
        for (j = 0; j < g_ARR_SIZE; ++j)
        {
            printf("adding %d   %d\n", i,j);
            g_INT_ARRAY[j] = i;
        }
        g_WRITE_FLAG = FLAG_OPEN;
        g_READ_FLAG = FLAG_CLOSE;
    }

    printf("producer out\n");

    return NULL;
}


static void *ConsumerFuncTwoFlags(void *arg)
{
    int i = 0;
    int j = 0;

    assert(NULL != arg);

    UNUSED(arg);

    for (i = 0; i < g_TEST_NUMBER; ++i)
    {
        while(FLAG_CLOSE == g_WRITE_FLAG);
        g_READ_FLAG = FLAG_CLOSE;

        printf("consumer, number is %i\n", g_INT_ARRAY[i]);
        for (j = 1; j < g_ARR_SIZE; ++j)
        {
            printf("reading %d  %d\n", i,j);
            if (g_INT_ARRAY[j] != g_INT_ARRAY[j - 1])
            {
                printf("The array is not correct.\
                At index %d the numebr is %d, at index %d the number %d\n",
                j, g_INT_ARRAY[j], j - 1,
                g_INT_ARRAY[j - 1]);
            }
        }
        g_READ_FLAG = FLAG_OPEN;
        g_WRITE_FLAG = FLAG_CLOSE;
    }

    return NULL;
}
