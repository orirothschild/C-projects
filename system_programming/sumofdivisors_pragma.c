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

static const size_t number = 100000000000;


int main()
{
    size_t i = 0ul;
    size_t sum = 0ul;

    #pragma omp parallel for
    for (i = 1ul; i <= number; ++i)
    {
        if (0 == number % i)
        {
            sum += i;
        }
    }

    printf("the sum is %lu\n", sum);

    return 0;
}