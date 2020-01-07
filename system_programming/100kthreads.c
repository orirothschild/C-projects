/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/

#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/* #include "100kthreads.h" */


#include "utils.h"

#define SUCCESSFUL 0
#define g_ARR_SIZE 100000

static int g_INT_ARRAY[g_ARR_SIZE] = {0};
static void WithAttachAttr();
static void WithDetachFunc();

struct thread_arg
{
    int idx;
};

void *ThreadWriteToArray(void *arg)
{
    struct thread_arg temp = *(struct thread_arg*)arg;

    g_INT_ARRAY[temp.idx] = 1;

    return NULL;
}


int main()
{
    WithAttachAttr();
    /* WithDetachFunc(); */
    return 0;
}


static void WithAttachAttr()
{
    int i = 0;
    int sum = 0;
    int retval = 0;
    struct thread_arg thread_arg_array[g_ARR_SIZE] = {0};
    pthread_t thread_array[g_ARR_SIZE];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    for (i = 0; i < g_ARR_SIZE; ++i)
    {
        thread_arg_array[i].idx = i;
        retval = pthread_create(&(thread_array[i]), &attr, ThreadWriteToArray,
                                &thread_arg_array[i]);
        
        if (SUCCESSFUL != retval)
        {
            fprintf(stderr, "Thread number %d return an error %d\n", i, retval);
        }
        
    }

    pthread_attr_destroy(&attr);

    sleep(0.5);

    for (i = 0; i < g_ARR_SIZE; ++i)
    {
        sum += g_INT_ARRAY[i];
    }

    printf("the sum is %d\n", sum);
}


static void WithDetachFunc()
{
    int i = 0;
    int sum = 0;
    int retval = 0;
    struct thread_arg thread_arg_array[g_ARR_SIZE] = {0};
    pthread_t thread_array[g_ARR_SIZE];
    
    for (i = 0; i < g_ARR_SIZE; ++i)
    {
        thread_arg_array[i].idx = i;
        retval = pthread_create(&(thread_array[i]), NULL, ThreadWriteToArray,
                                &thread_arg_array[i]);
        pthread_detach(thread_array[i]);
        if (SUCCESSFUL != retval)
        {
            fprintf(stderr, "Thread number %d return an error %d\n", i, retval);
        }   
    }

    sleep(0.5);

    for (i = 0; i < g_ARR_SIZE; ++i)
    {
        sum += g_INT_ARRAY[i];
    }

    printf("the sum is %d\n", sum);
}
