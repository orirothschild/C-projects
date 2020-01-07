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

#include "cqueue.h"
#include "utils.h"

#define Q_SIZE (10)


struct cqueue
{
    size_t num_of_elements_in_q;
    size_t first_element_idx;
    int cqueue[Q_SIZE];
};


cqueue_t *CQueueCreate()
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


void CQueueDestroy(cqueue_t *cqueue)
{
    free(cqueue);
}


int CQueueEnqueue(cqueue_t *cqueue, int data)
{
    size_t idx = 0;
    
    assert(NULL != cqueue);

    if (Q_SIZE <= cqueue->num_of_elements_in_q)
    {
        return FAILURE;
    }
    idx = (cqueue->first_element_idx + cqueue->num_of_elements_in_q) % Q_SIZE;

    cqueue->cqueue[idx] = data;

    ++cqueue->num_of_elements_in_q;

    return 0;
}


int CQueueDequeue(cqueue_t *cqueue)
{
    int retval = 0;
    int tmp_idx = 0;    
    assert(NULL != cqueue);

    retval = cqueue->cqueue[cqueue->first_element_idx];

    tmp_idx = cqueue->first_element_idx;
    ++tmp_idx;

    cqueue->first_element_idx = tmp_idx % Q_SIZE;

    --cqueue->num_of_elements_in_q;

    return retval; 
}


int CQueueIsEmpty(cqueue_t *cqueue)
{
    UNUSED(cqueue);

    return 0;
}


void PrintQueue(cqueue_t *queue)
{
    int i = 0;
    
    for (i = 0; i < 10; ++i)
    {
        printf("%d, ", queue->cqueue[i]);
    }
    printf("\n");
}