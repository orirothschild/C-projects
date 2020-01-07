/***********************************
*                                  *
*   DS - Priority Queue            *
*   written by: Hadar Klein        *
*   reviewed by: Oksana Rubanov    *
*                                  *
***********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "pqueue.h"
#include "utils.h"

struct p_queue
{
    srt_list_t *slist;
};


p_queue_t *PQueueCreate(is_before_func_t sort_func)
{
    p_queue_t *pq = (p_queue_t *)malloc(sizeof(p_queue_t));
    srt_list_t *slist = NULL;
    
    assert(NULL != sort_func);
    
    slist = SortedListCreate(sort_func);
    
    if(NULL == pq || NULL == slist)
    {
        free (pq);
        return NULL;
    }
    
    pq->slist = slist;
    
    return pq;
}


void PQueueDestroy(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    SortedListDestroy(p_queue->slist);
    free(p_queue);
}


int PQueueEnqueue(p_queue_t *p_queue, const void *data)
{
    assert(NULL != p_queue);
    assert(NULL != data);
    
    if (SortedListEnd(p_queue->slist) == SortedListInsert(p_queue->slist,
                                                          data,
                                                          NULL))
    {
        return FAILURE;
    }
    
    return SUCCESS;
}


void PQueueDequeue(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    SortedListPopFront(p_queue->slist);
}


size_t PQueueSize(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    return (SortedListSize(p_queue->slist));
}


int PQueueIsEmpty(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    return (SortedListIsEmpty(p_queue->slist));
}


void *PQueuePeek(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    return (SortedListGetData(SortedListBegin(p_queue->slist)));
}


void *PQueueRemove(p_queue_t *p_queue,
                 p_queue_is_match_func_t match_func,
                 const void *user_data)
{
    srt_list_iter_t iter = NULL;
    void *tmp_data = NULL;
    
    assert(NULL != p_queue);
    assert(NULL != match_func);
    assert(NULL != user_data);
    
    iter = SortedListBegin(p_queue->slist);
    
    while (iter != SortedListEnd(p_queue->slist))
    {
        if(True == match_func(SortedListGetData(iter), user_data, NULL))
        {
            tmp_data = SortedListGetData(iter);
            SortedListErase(iter);
            return (tmp_data);
        }
        
        iter = SortedListNext(iter);
    }
    
    return NULL;
}


         
void PQueueClear(p_queue_t *p_queue)
{
    assert(NULL != p_queue);
    
    while (True != SortedListIsEmpty(p_queue->slist))
    {
        PQueueDequeue(p_queue);
    }
}
