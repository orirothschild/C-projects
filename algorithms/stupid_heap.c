/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/

#include <stdio.h>
#include <assert.h>

#include "stupid_heap.h"

/* #define GetArrayElement(array, index) (void **)((char *)array + (index * sizeof(size_t))) */


static void **GetArrayElement(void *array, size_t idx, size_t element_size)
{
    return (void **)((char *)array + (idx * element_size));
}


static int GetMaxChildSide(void **array, heap_cmp_func_t cmp_func, 
                    size_t l_child_idx, size_t r_child_idx, size_t arr_size,
                    void *param, size_t element_size)
{
    if (r_child_idx < arr_size)
    {
        return (0 < cmp_func(GetArrayElement(array, l_child_idx, element_size), 
                             GetArrayElement(array, r_child_idx, element_size)
                             , param) ?
                             l_child_idx : r_child_idx);
    }
    else
    {
        return l_child_idx;
    }
}


static void SwapChildren(void *root, void *swap, size_t element_size)
{
    char temp = 0;
    char *swap_ptr = swap;
    char *root_ptr = root;
    size_t i = 0;

    for (i = 0; i < element_size; ++i)
    {
        temp = *swap_ptr;
        *swap_ptr = *root_ptr;
        *root_ptr = temp;

        ++swap_ptr;
        ++root_ptr;
    }
}


void HeapifyUp(void *array, heap_cmp_func_t cmp_func, size_t index, 
               size_t arr_size, void *param, size_t element_size)
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

        root = GetArrayElement(array,root_idx, element_size);
        parent = GetArrayElement(array, parent_idx, element_size);

        if (0 < cmp_func(root, parent, param))
        {
            SwapChildren(root, parent, element_size);
        }

        index = parent_idx;
    }
}


void HeapifyDown(void *array, heap_cmp_func_t cmp_func, size_t index, 
                 size_t arr_size, void *param, size_t element_size)
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
                                   arr_size, param, element_size);
        temp1 = GetArrayElement(array, root_idx, element_size);
        temp2 = GetArrayElement(array, swap_idx, element_size);
        if (0 < cmp_func(temp1, temp2, param))
        {
            break;
        }
        SwapChildren(temp1, temp2, element_size);
        index = swap_idx;
    }

    return;
}
