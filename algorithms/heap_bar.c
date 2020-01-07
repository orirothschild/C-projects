/*     DS          - by Bar Shoshany    */
/*    sent for code review on           */
/*          Reviewd by                  */


#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for malloc */
#include <assert.h> /* for assert */

#include "heap.h"

#define LEFT_CHILD (HeapGetChildIndexIMP(index, LEFT))
#define RIGHT_CHILD (HeapGetChildIndexIMP(index, RIGHT))
#define INDEX_DATA(x) ((char*) array + (x) * WORD_SIZE)

const size_t WORD_SIZE = 4;

enum directions {
                    LEFT = 1,
                    RIGHT = 2
                };


static size_t HeapFindParentIndexIMP(size_t index);
static size_t HeapGetChildIndexIMP(size_t index, enum directions direct);
static size_t HeapSwapValuesIMP (size_t index, size_t swap_index, int *array);
static size_t HeapFindMaxValueIMP(size_t number_of_elements, 
                                  size_t left_child, 
                                  size_t right_child, 
                                  int *array, 
                                  heap_cmp_func_t cmpfunc);

static size_t HeapMaxOfTwoValuesByIndexIMP(size_t left_child, 
                                           size_t right_child, 
                                           int *array, 
                                           heap_cmp_func_t cmpfunc);


void HeapifyUp(int *array, 
               heap_cmp_func_t cmp_func, 
               size_t index, 
               size_t arr_size, 
               void *cmp_param)
{
    size_t parent_index = HeapFindParentIndexIMP(index);
    (void) arr_size;

    while (0 < index &&
           0 <  cmp_func (INDEX_DATA(index), INDEX_DATA(parent_index), cmp_param))
    {
        index = HeapSwapValuesIMP(index, parent_index, array);
        parent_index = HeapFindParentIndexIMP(index);
    }
}

void HeapifyDown(int *array, 
                 heap_cmp_func_t cmp_func, 
                 size_t index, 
                 size_t arr_size, 
                 void *cmp_param)
{
    size_t swap_index = 0;

    while (HeapGetChildIndexIMP(index, LEFT) < arr_size)
    {
        swap_index = HeapFindMaxValueIMP(arr_size,
                                        LEFT_CHILD,
                                        RIGHT_CHILD,
                                        array,
                                        cmp_func);
        if (1 == cmp_func (INDEX_DATA(index), INDEX_DATA(swap_index), cmp_param))
        {
            break;
        }

        index = HeapSwapValuesIMP(index, swap_index, array);
    }
}

static size_t HeapFindParentIndexIMP(size_t index)
{
    return ((index -1) / 2);
}

static size_t HeapGetChildIndexIMP(size_t index, enum directions direct)
{
    return (2 * index + direct);
}

static size_t HeapSwapValuesIMP (size_t index, size_t swap_index, int *array)
{
    size_t temp = array[index];
    array[index] = array[swap_index];
    array[swap_index] = temp;

    return swap_index;
}

static size_t HeapFindMaxValueIMP(size_t number_of_elements, 
                                  size_t left_child, 
                                  size_t right_child, 
                                  int *array, 
                                  heap_cmp_func_t cmpfunc)
{
    if (right_child >= number_of_elements)
    {
        return left_child;
    }

    return (HeapMaxOfTwoValuesByIndexIMP(left_child, 
                                         right_child, 
                                         array, 
                                         cmpfunc));
}

static size_t HeapMaxOfTwoValuesByIndexIMP(size_t left_child, 
                                           size_t right_child, 
                                           int *array, 
                                           heap_cmp_func_t cmpfunc)
{
    if (0 < cmpfunc(INDEX_DATA(left_child), INDEX_DATA(right_child), NULL))
    {
        return (left_child);
    }

    return (right_child);
}