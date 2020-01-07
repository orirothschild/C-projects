/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/

#include <stdio.h>
#include <assert.h>

#include "heap.h"



static int GetMaxChildSide(void **array, heap_cmp_func_t cmp_func, 
                    size_t l_child_idx, size_t r_child_idx, size_t arr_size,
                    void *param)
{
    if (r_child_idx < arr_size)
    {
        return (0 < cmp_func(((void *)((size_t *)array + l_child_idx)),
                             ((void *)((size_t *)array + r_child_idx)),
                             param)) ?
                l_child_idx  : r_child_idx;
    }
    else
    {
        return l_child_idx;
    }
}


/* static void SwapChildren(void **array, size_t root_idx, size_t child_idx)
{
    void *temp = NULL;

    assert(NULL != array);
    
    temp = array[root_idx];
    array[root_idx] = array[child_idx];
    array[child_idx] = temp;
} */


static void SwapChildren(void **root, void **swap)
{
    void *temp = *root;
    *root = *swap;
    *swap = temp;
}

void HeapifyUp(void *array, heap_cmp_func_t cmp_func, size_t index, 
               size_t arr_size, void *param)
{
    size_t root_idx = 0;
    size_t parent_idx = 0;
    void *temp1 = NULL;
    void *temp2 = NULL;


    (void)param;
    (void)arr_size;

    while (index > 0ul)
    {
        root_idx = index;
        parent_idx = (index - 1) / 2;

        temp1 = (void *)((size_t *)array + root_idx);
        temp2 = (void *)((size_t *)array + parent_idx);
        if (0 < cmp_func(temp1, temp2, param))
        {
            /* SwapChildren(array, root_idx, parent_idx); */
            SwapChildren(temp1, temp2);
        }

        index = parent_idx;
    }
}


 
void HeapifyDown(void *array, heap_cmp_func_t cmp_func, size_t index, 
                 size_t arr_size, void *param)
{
    size_t root_idx = 0;
    size_t l_child_idx = 0;
    size_t r_child_idx = 0;
    size_t swap_idx = 0;
    void *temp1 = NULL;
    void *temp2 = NULL;

    (void)param;

    assert(NULL != array);
    assert(NULL != cmp_func);
    assert(index <= arr_size);

    while (2 * index + 1 < arr_size)
    {
        root_idx = index;
        l_child_idx = 2 * index + 1;
        r_child_idx = 2 * index + 2;

        swap_idx = GetMaxChildSide(array, cmp_func,
                                   l_child_idx, r_child_idx,
                                   arr_size, param);
        temp1 = (void *)((size_t *)array + root_idx);
        temp2 = (void *)((size_t *)array + swap_idx);
        if (0 < cmp_func(temp1, temp2, param))
        {
            break;
        }
        /* SwapChildren(array, root_idx, swap_idx); */
        SwapChildren(temp1, temp2);
        index = swap_idx;
    }

    return;
}
