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
#include <string.h>

#include "pqheap.h"
#include "heap.h"
#include "dv.h"
#include "utils.h"

const size_t NUM_OF_ELEMENTS = 30;

void PrintHeap(p_queue_t *pq_heap);

struct p_queue
{
    vector_t *dv;
    pqueue_cmp_func_t sort_func;
};


p_queue_t *PQueueCreate(pqueue_cmp_func_t sort_func)
{
    p_queue_t *pq = NULL;
    vector_t *dv = NULL;
    size_t num_of_elements = NUM_OF_ELEMENTS;
    size_t element_size = WORD_SIZE;

    assert(NULL != sort_func);
    
    pq = (p_queue_t *)malloc(sizeof(p_queue_t));
    if(NULL == pq)
    {
        return NULL;
    }

    dv = DVectorCreate(num_of_elements, element_size);
    if(NULL == dv)
    {
        free (pq);
        return NULL;
    }
    
    pq->dv = dv;
    pq->sort_func = sort_func;
    
    return pq;
}


void PQueueDestroy(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    DVectorDestroy(p_queue->dv);
    free(p_queue);
}


int PQueueEnqueue(p_queue_t *p_queue, const void *data)
{
    assert(NULL != p_queue);
    assert(NULL != data);
    
    if (FAILURE == DVectorPush(p_queue->dv, &data))
    {
        return FAILURE;
    }
    
    HeapifyUp(DVectorGetItemAddress(p_queue->dv, 0), p_queue->sort_func, 
              DVectorSize(p_queue->dv) - 1, DVectorSize(p_queue->dv), NULL);

    return SUCCESS;
}


static void SwapVectorData(void **head, void **end)
{
    void *temp = *head;
    *head = *end;
    *end = temp;
}


void PQueueDequeue(p_queue_t *p_queue)
{
    void *head = 0;
    void *end = 0;

    assert(NULL != p_queue);
    
    head = DVectorGetItemAddress(p_queue->dv, 0);
    end = DVectorGetItemAddress(p_queue->dv, DVectorSize(p_queue->dv) - 1);

    SwapVectorData(head, end);

    DVectorPop(p_queue->dv);

    HeapifyDown(DVectorGetItemAddress(p_queue->dv, 0), p_queue->sort_func, 
                0, DVectorSize(p_queue->dv), NULL);
}


size_t PQueueSize(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    return DVectorSize(p_queue->dv);
}


int PQueueIsEmpty(p_queue_t *p_queue)
{
    assert(NULL != p_queue);

    return !DVectorSize(p_queue->dv);
}


void *PQueuePeek(p_queue_t *p_queue)
{
    void **temp = NULL;
    
    assert(NULL != p_queue);
    
    temp = DVectorGetItemAddress(p_queue->dv, 0);
    return *temp;
}


void *PQueuePeekTest(p_queue_t *p_queue, size_t index)
{
    void **temp = NULL;
    
    assert(NULL != p_queue);
    
    temp = DVectorGetItemAddress(p_queue->dv, index);
    return *temp;
}


void *PQueueRemove(p_queue_t *p_queue,
                   pqueue_match_func_t match_func,
                   const void *user_data)
{
    void **tmp_data = NULL;
    void **end = NULL;
    int i = 0;
    int num_of_elements = 0;

    assert(NULL != p_queue);
    assert(NULL != match_func);
    assert(NULL != user_data);

    num_of_elements = DVectorSize(p_queue->dv);

    for (i = 0; i < num_of_elements; ++i)
    {
        if(True == match_func(*(void**)DVectorGetItemAddress(p_queue->dv, i),
                              user_data, NULL))
        {
            tmp_data = DVectorGetItemAddress(p_queue->dv, i);
            end = DVectorGetItemAddress(p_queue->dv, 
                                        DVectorSize(p_queue->dv) - 1);
            
            SwapVectorData(tmp_data, end);

            DVectorPop(p_queue->dv);
            
            HeapifyUp(DVectorGetItemAddress(p_queue->dv, 0),
                      p_queue->sort_func, 
                      i,
                      DVectorSize(p_queue->dv),
                      NULL);

            HeapifyDown(DVectorGetItemAddress(p_queue->dv, 0),
                        p_queue->sort_func, 
                        i,
                        DVectorSize(p_queue->dv),
                        NULL);

            return *end;       
        }
    }
    
    return NULL;
}

         
void PQueueClear(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    while (False == PQueueIsEmpty(p_queue))
    {
        PQueueDequeue(p_queue);
    }
}


void PrintHeap(p_queue_t *pq_heap)
{
    size_t i = 0;
    size_t *runner = DVectorGetItemAddress(pq_heap->dv, 0);

    while(i < PQueueSize(pq_heap))
    {
        printf("%d\t", **(int **)runner); 

        ++i;
        ++runner;
    }
    printf("\n");
}
