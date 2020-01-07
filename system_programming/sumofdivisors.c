/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

/* #include "sumofdivisors.h" */

#include "utils.h"

#define SUCCESSFUL 0
#define g_ARR_SIZE 6

static const size_t number = 100000000000;

static size_t g_INT_ARRAY[g_ARR_SIZE] = {0};

struct thread_arg
{
    size_t idx;
    size_t lower_bound;
    size_t upper_bound;
};

void *ThreadFuncFindSumDivisors(void *arg)
{
    size_t i = 0ul;
    size_t sum = 0ul;

    struct thread_arg temp = *(struct thread_arg*)arg;

    for (i = temp.lower_bound; i <= temp.upper_bound; ++i)
    {
        if (0ul == number % i)
        {
            sum += i;
        }
    }

    g_INT_ARRAY[temp.idx] = sum;

    return NULL;
}


int main()
{
    size_t range = number / g_ARR_SIZE;
    size_t i = 0ul;
    size_t sum = 0ul;
    size_t retval = 0ul;
    struct thread_arg thread_arg_array[g_ARR_SIZE] = {0};
    pthread_t thread_array[g_ARR_SIZE];
    
    for (i = 0ul; i < g_ARR_SIZE; ++i)
    {
        thread_arg_array[i].idx = i;
        thread_arg_array[i].lower_bound = (range * i) + 1;
        thread_arg_array[i].upper_bound = (range * (i + 1));

    }
    thread_arg_array[i-1].upper_bound = number;

    for (i = 0ul; i < g_ARR_SIZE; ++i)
    {
        retval = pthread_create(&(thread_array[i]), NULL,
                                ThreadFuncFindSumDivisors, 
                                &thread_arg_array[i]);
        if (SUCCESSFUL != retval)
        {
            fprintf(stderr, "Thread number %lu return an error %lu\n", i, retval);
        }
    }

    for (i = 0; i < g_ARR_SIZE; ++i)
    {
        retval = pthread_join(thread_array[i], NULL);
        if (SUCCESSFUL != retval)
        {
            fprintf(stderr,"Thread number %lu returned an error %lu\n", i,
                    retval);
            exit(1);
        }
    }

    for (i = 0ul; i < g_ARR_SIZE; ++i)
    {
        sum += g_INT_ARRAY[i];
    }

    printf("the sum is %lu\n", sum);

    return 0;
}