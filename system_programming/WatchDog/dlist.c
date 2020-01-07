/***********************************
*                                  *
*   DS - Doubly Linked List        *
*   written by: Hadar Klein        *
*   reviewed by: Dafna Cohen       *
*                                  *
***********************************/


#include <assert.h>  /* assert */
#include <stdlib.h>  /* malloc */

#include "dlist.h"   /* API    */
#include "utils.h"   /* macros */

typedef struct dlist_node dlist_node_t;

struct dlist_node
{
    void *data;
    dlist_node_t *prev;
    dlist_node_t *next;
};

struct dlist
{
    dlist_node_t *head;
    dlist_node_t *tail;
};

static dlist_node_t *DListCreateNode(void *data, dlist_node_t *next, 
                                     dlist_node_t *prev);
                                     
dlist_t *DListCreate(void)
{
    dlist_t *dlist = (dlist_t *)malloc(sizeof(dlist_t));
    dlist_node_t *head = DListCreateNode((void *)0xDEADBEEF, NULL, NULL);
    dlist_node_t *tail = DListCreateNode((void *)0xDEADBEEF, NULL, NULL);
    
    if (NULL == dlist || NULL == head || NULL == tail)
    {
        free (dlist);
        free (head);
        free (tail);
        
        return (NULL);
    }
    
    head->next = tail;
    tail->prev = head;
    
    dlist->head = head;
    dlist->tail = tail;
    
    return (dlist);
}


static dlist_node_t *DListCreateNode(void *data, dlist_node_t *next, 
                                     dlist_node_t *prev)
{
	dlist_node_t *node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if (NULL == node)
	{
		return (NULL);
	}

	node->data = data;
	node->next = next;
	node->prev = prev;

	return (node);
}


void DListDestroy(dlist_t *dlist)
{
    dlist_iter_t iter = NULL;
    dlist_iter_t temp = NULL;
    
    if (NULL != dlist)
    {
        iter = DListBegin(dlist);

        while (iter != DListEnd(dlist))
        {
            temp = DListNext(iter);
            DListErase(iter);
            iter = temp;
        }
                
        dlist->head->next = NULL;
        dlist->tail->prev = NULL;
        free(dlist->head);
        free(dlist->tail);
        free(dlist);
    }
}


dlist_iter_t DListBegin(const dlist_t *dlist)
{
    assert(NULL != dlist);
    
    return ((dlist_iter_t)dlist->head->next);
}


dlist_iter_t DListEnd(const dlist_t *dlist)
{
    assert(NULL != dlist);
    
    return ((dlist_iter_t)dlist->tail);
}


dlist_iter_t DListNext(const dlist_iter_t iter)
{
    assert(NULL != iter);
    
    return (iter->next);
}


dlist_iter_t DListPrev(const dlist_iter_t iter)
{
    assert(NULL != iter);
    
    return (iter->prev);
}


int DListIsEmpty(const dlist_t *dlist)
{
    assert(NULL != dlist);
    
    return (!DListCount(dlist));
}


size_t DListCount(const dlist_t *dlist)
{
    dlist_iter_t curr = NULL;
    dlist_iter_t end = NULL;
    size_t count = 0;
    
    assert(NULL != dlist);
    
    curr = DListBegin(dlist);
    end = DListEnd(dlist);
    
    while (curr != end)
    {
        ++count;
        curr = DListNext(curr);
    }
    
    return (count);
}


int DListIsSameIterator(dlist_iter_t iter1, dlist_iter_t iter2)
{
    assert(NULL != iter1);
    assert(NULL != iter2);
    
    return (iter1 == iter2);
}


dlist_iter_t DListInsertBefore(dlist_iter_t iter, const void *data,
                               dlist_t *dlist)
{
    assert(NULL != dlist);
    assert(NULL != iter);
    
    iter = DListPrev(iter);
    return (DListInsertAfter(iter, data, dlist));
}


dlist_iter_t DListInsertAfter(dlist_iter_t iter, const void *data, 
                              dlist_t *dlist)
{
    dlist_node_t *new_node = NULL;
    
    assert(NULL != dlist);
    assert(NULL != iter);
    
    new_node = DListCreateNode((void *)data, DListNext(iter), iter);
    if (NULL == new_node)
    {
        return (DListEnd(dlist));
    }
    
    iter->next->prev = new_node;
    iter->next = new_node;
    
    return (new_node);
}


dlist_iter_t DListErase(dlist_iter_t iter)
{
    dlist_iter_t return_iter = NULL;
    
    assert(NULL != iter);
    
    iter->next->prev = DListPrev(iter);
    iter->prev->next = DListNext(iter);
    
    return_iter = DListNext(iter);
    
    iter->next = NULL;
    iter->prev = NULL;
    free(iter);
    
    return (return_iter);
}


void *DListGetData(const dlist_iter_t iter)
{
    assert(NULL != iter);
    
    return (iter->data);
}


dlist_iter_t DListPushFront(dlist_t *dlist, const void *data)
{
    assert(NULL != dlist);
    
    return (DListInsertBefore((dlist_iter_t)DListBegin(dlist), data, dlist));
}


dlist_iter_t DListPushBack(dlist_t *dlist, const void *data)
{
    assert(NULL != dlist);
    
    return (DListInsertBefore((dlist_iter_t)DListEnd(dlist), data, dlist));
}


void DListPopFront(dlist_t *dlist)
{
    assert(NULL != dlist);
    
    DListErase((dlist_iter_t)DListBegin(dlist));
}


void DListPopBack(dlist_t *dlist)
{
    assert(NULL != dlist);
    
    DListErase(DListPrev((dlist_iter_t)DListEnd(dlist)));
}


void DListSpliceBefore(dlist_iter_t dest, dlist_iter_t src_start, 
                       dlist_iter_t src_end)
{
    assert(NULL != dest);
    assert(NULL != src_start);
    assert(NULL != src_end);
    assert(True != DListIsSameIterator(src_start, src_end));
    
    /* move src_end back one node since it is not inclusive */
    src_end = DListPrev(src_end);
    
    src_end->next->prev = DListPrev(src_start);
    src_start->prev->next = DListNext(src_end);
    
    src_end->next = dest;
    src_start->prev = DListPrev(dest);
    
    dest->prev->next = src_start;
    dest->prev = src_end;
}


int DListForEach(dlist_iter_t start,
                 dlist_iter_t end, 
                 action_func_t action_func,
                 void *param)
{
    dlist_iter_t curr = start;
    int result = SUCCESS;
    
    assert(NULL != start);
    assert(NULL != end);
    assert(NULL != param);
    
    while (curr != end && FAILURE != result)
    {
        result = action_func(DListGetData(curr), param);
        curr = DListNext(curr);
    }
    
    return (result);
}


int DListFind(dlist_iter_t start,
              dlist_iter_t end, 
              is_match_func_t match_func, 
              const void *param,
              const void *match_data)
{
    dlist_iter_t curr = start;
    int result = SUCCESS;
    
    assert(NULL != start);
    assert(NULL != end);
    assert(NULL != match_data);
    assert(NULL != param);
    
    while (curr != end && True != result)
    {
        result = match_func((const void *)DListGetData(curr), match_data, param);
        curr = DListNext(curr);
    }
    
    return (result);
}


