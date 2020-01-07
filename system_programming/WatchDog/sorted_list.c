/***********************************
*                                  *
*   DS - Sorted List               *
*   written by: Hadar Klein        *
*   reviewed by: Ellad Barkay      *
*                                  *
***********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "sorted_list.h" /* sorted list API */

struct srt_list
{
    dlist_t *dlist;
    is_before_func_t cmp_func;
};


srt_list_t *SortedListCreate(is_before_func_t cmp_func)
{
    srt_list_t *slist = (srt_list_t *)malloc(sizeof(srt_list_t));
    dlist_t *dlist = DListCreate();
    
    assert(NULL != cmp_func);
        
    if (NULL == slist || NULL == dlist)
    {
        free(slist);
        return (NULL);
    }
    
    slist->dlist = dlist;
    slist->cmp_func = cmp_func;
    
    return (slist);
}


void SortedListDestroy(srt_list_t *slist)
{
    assert(NULL != slist);
    
    DListDestroy(slist->dlist);
    free(slist);
    slist = NULL;
}


srt_list_iter_t SortedListBegin(const srt_list_t *slist)
{
    assert(NULL != slist);
    
    return(DListBegin(slist->dlist));
}


srt_list_iter_t SortedListEnd(const srt_list_t *slist)
{
    assert(NULL != slist);
    
    return(DListEnd(slist->dlist));
}


srt_list_iter_t SortedListNext(const srt_list_iter_t iter)
{
    assert(NULL != iter);
    
    return (DListNext(iter));
}


srt_list_iter_t SortedListPrev(const srt_list_iter_t iter)
{
    assert(NULL != iter);
    
    return (DListPrev(iter));
}


int SortedListIsEmpty(const srt_list_t *slist)
{
    assert(NULL != slist);
    
    return (DListIsEmpty(slist->dlist));
}


size_t SortedListSize(const srt_list_t *slist)
{
    assert(NULL != slist);
    
    return (DListCount(slist->dlist));
}


int SortedListIsSameIterator(srt_list_iter_t iter1, srt_list_iter_t iter2)
{
    assert(NULL != iter1);
    assert(NULL != iter2);
    
    return (DListIsSameIterator(iter1, iter2));
}


srt_list_iter_t SortedListInsert(srt_list_t *slist,
                                 const void *data,
                                 void *param)
{
    srt_list_iter_t curr = NULL;
    srt_list_iter_t end = NULL;
    
    assert(NULL != slist);
    
    curr = SortedListBegin(slist);
    end = SortedListEnd(slist);
    
    while ((curr != end) && (0 == slist->cmp_func(SortedListGetData(curr), 
                                                  data,
                                                  param)))
    {
        curr = SortedListNext(curr);
    }
    
    return (DListInsertBefore(curr, data, slist->dlist));
}


srt_list_iter_t SortedListErase(srt_list_iter_t iter)
{
    assert(NULL != iter);
    
    return (DListErase(iter));
}


void *SortedListGetData(const srt_list_iter_t iter)
{
    assert(NULL != iter);
    
    return (DListGetData(iter));
}


void SortedListPopFront(srt_list_t *slist)
{
    assert(NULL != slist);
    
    DListPopFront(slist->dlist);
}


void SortedListPopBack(srt_list_t *slist)
{
    assert(NULL != slist);
    
    DListPopBack(slist->dlist);
}


void SortedListMerge(srt_list_t *dest,
                     srt_list_iter_t start, 
                     srt_list_iter_t end,
                     void *param)
{
    srt_list_iter_t curr_dest = NULL;
    srt_list_iter_t curr_src = NULL;

    assert(NULL != dest);
    assert(NULL != start);
    assert(NULL != end);
    
    curr_dest = SortedListBegin(dest);
    curr_src = start;
    
    while (0 == SortedListIsSameIterator(curr_src, end) && 
           0 == SortedListIsSameIterator(curr_dest, SortedListEnd(dest)))
    {
        while (0 == SortedListIsSameIterator(curr_src, end) &&
               1 == dest->cmp_func(SortedListGetData(curr_dest), 
                                   SortedListGetData(curr_src),
                                   param))
        {
            curr_src = SortedListNext(curr_src);
        }
        if (start != curr_src)
        {
            DListSpliceBefore(curr_dest, start, curr_src);
        }    
        
        start = curr_src;
        curr_dest = SortedListNext(curr_dest);
    }
    
    if (start != end)
    {
        DListSpliceBefore(SortedListEnd(dest), start, end);
    }
}


int SortedListForEach(srt_list_iter_t start,
                      srt_list_iter_t end, 
                      srt_list_action_func_t action_func,
                      void *param)
{
    assert(NULL != start);
    assert(NULL != end);
    assert(NULL != action_func);
    
    return (DListForEach(start, end, action_func, param));
}


int SortedListFind(srt_list_iter_t start,
                   srt_list_iter_t end, 
                   srt_list_is_match_func_t match_func, 
                   const void *param,
                   const void *match_data)
{
    assert(NULL != start);
    assert(NULL != end);
    assert(NULL != match_func);
    
    return (DListFind(start, end, match_func, param, match_data));
}
