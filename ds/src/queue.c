/***********************************
*                                  *
*   DS - Queue                     *
*   written by: Hadar Klein        *
*   reviewed by: Ori Rothschild    *
*                                  *
***********************************/

#include <stdio.h>   /* std library     */
#include <assert.h>  /* assert          */
#include <stdlib.h>  /* malloc          */ 
#include "queue.h"   /* Queue API       */
#include "sl_list.h" /* Linked List API */

enum {False, True};
enum {SUCCESS, FAILURE};

struct queue
{
    sll_node_t *head;
    sll_node_t *tail;
};


queue_t *QueueCreate()
{
    sll_node_t *dummy = SLListCreateNode(NULL, NULL);
    queue_t *queue = (void *)malloc(sizeof(queue_t));
    if(NULL == queue || NULL == dummy)
    {
        free(dummy);
        return NULL;
    }
    
    queue->head = dummy;
    queue->tail = dummy;
 
    return (queue);
}


void QueueDestroy(queue_t *queue)
{
    assert(NULL != queue);
    
    SLListDestroyList(queue->head);
    free(queue);
}


int QueueEnqueue(queue_t *queue, void *data)
{
    sll_node_t *new_node = NULL;
    
    assert(NULL != queue);
    
    new_node = SLListCreateNode(data, NULL);
    if (NULL == new_node)
    {
        return (FAILURE);
    }

    SLListInsert(queue->tail, new_node);
    
    queue->tail = queue->tail->next;
    
    return (SUCCESS);
}


void *QueueDequeue(queue_t *queue)
{
    void *temp_data = NULL;
    sll_node_t *temp_head = NULL;
    assert(NULL != queue);
    assert(queue->head != queue->tail);
  
    temp_data = queue->head->data;
    temp_head = queue->head;
    queue->head = queue->head->next;

    temp_head->next = NULL;
    free(temp_head);
    
    return (temp_data);
}


size_t QueueSize(queue_t *queue)
{
    assert(NULL != queue);
    
    return (SLListCount(queue->head) - 1);
}


int QueueIsEmpty(queue_t *queue)
{
    assert(NULL != queue);
    
    if (queue->head == queue->tail)
    {
        return (True);
    }
    
    return (False);
}


void *QueuePeek(queue_t *queue)
{
    assert(NULL != queue);
    
    return (queue->head->data);
}


void QueueAppend(queue_t *to, queue_t *from)
{
    assert(NULL != to);
    assert(NULL != from);

    to->tail->data = from->head->data;
    to->tail->next = from->head->next;
    to->tail = from->tail;
    
    
    from->tail = from->head;
    from->head->next = NULL;
    from->head->data = NULL;
/*    free(from->head);*/
/*    free(from);*/
}

