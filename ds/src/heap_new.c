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

#define GET_ARRAY_ELEMENT(array, index) (void **)((char *)array + (index * sizeof(size_t)))


static int GetMaxChildSide(void **array, heap_cmp_func_t cmp_func, 
                    size_t l_child_idx, size_t r_child_idx, size_t arr_size,
                    void *param)
{
    if (r_child_idx < arr_size)
    {
        return (0 < cmp_func(*GET_ARRAY_ELEMENT(array, l_child_idx), 
                             *GET_ARRAY_ELEMENT(array, r_child_idx), param) ?
                             l_child_idx : r_child_idx);
    }
    else
    {
        return l_child_idx;
    }
}


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
    void **root = NULL;
    void **parent = NULL;


    (void)param;
    (void)arr_size;

    while (index > 0ul)
    {
        root_idx = index;
        parent_idx = (index - 1) / 2;

        root = GET_ARRAY_ELEMENT(array,root_idx);
        parent = GET_ARRAY_ELEMENT(array, parent_idx);

        if (0 < cmp_func(*root, *parent, param))
        {
            SwapChildren(root, parent);
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
    void **temp1 = NULL;
    void **temp2 = NULL;

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
        temp1 = GET_ARRAY_ELEMENT(array, root_idx);
        temp2 = GET_ARRAY_ELEMENT(array, swap_idx);
        if (0 < cmp_func(*temp1, *temp2, param))
        {
            break;
        }
        SwapChildren(temp1, temp2);
        index = swap_idx;
    }

    return;
}
