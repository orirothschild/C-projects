#include <time.h>   /* time */
#include <stdlib.h> /* rand, malloc */
#include <assert.h> /* assert */
#include <stdio.h>
#include "sorts.h"   /* API */
/* #include "dv.h" */
#include "stupid_heap.h"

typedef int (*arr_idx_loc_t)(int *arr, int i, int digit);

static void SwapInts(int *i, int *j);
static void CopyArray(int *sorted_arr, int *rand_arr, int arr_size);
static int CalcLoc(int *arr, int i, int digit);
static int ArrayGetMax(int *arr, int arr_size);
static int RadixCalcLoc(int *arr, int i, int digit);
static void OffsetArray(int *arr, int arr_size, int minimum, int flag);
static void CountingSort(int *input_arr, int arr_size, int range, int minimum, 
                         int digit,
                         arr_idx_loc_t loc_func);
static int HeapSortCmpFunc( const void *user_data, const void *array_data, void *param);



#define START 1
#define END 0


void BubbleSort(int *arr, int arr_size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < arr_size; ++i)
    {
        for (j = 0; j < arr_size; ++j)
        {
            if (arr[i] < arr[j])
            {
                SwapInts(&arr[i], &arr[j]);
            }
        }
    }
}


void SmarterBubbleSort(int *arr, int arr_size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < arr_size - 1; ++i)
    {
        for (j = 0; j < arr_size - i - 1; ++j)
        {
            if (arr[j] > arr[j+ 1])
            {
                SwapInts(&arr[j], &arr[j + 1]);
            }
        }
    }
}


void EvenSmarterBubbleSort(int *arr, int arr_size)
{
    int i = 0;
    int j = 0;
    int swapped = 0;

    for (i = 0; i < arr_size - 1; ++i)
    {
        swapped = 0;
        for (j = 0; j < arr_size - i - 1; ++j)
        {
            if (arr[j] > arr[j+ 1])
            {
                SwapInts(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (0 == swapped)
        {
            break;
        }
    }
}


void SelectionSort(int *arr, int arr_size)
{
    int i = 0;
    int j = 0;
    int min_idx = 0;

    for (i = 0; i < arr_size - 1; ++i)
    {
        min_idx = i;
        for (j = i + 1; j < arr_size; ++j)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        SwapInts(&arr[min_idx], &arr[i]);
    }
}


void InsertionSort(int *arr, int arr_size)
{
    int i = 0;
    int j = 0;
    int key = 0;

    for (i = 1; i < arr_size; ++i)
    {
        key = arr[i];
        j = i - 1;

        while (0 <= j && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}


void CountSort(int *input_arr, int arr_size, int range, int minimum)
{
    int digit = 1;

    CountingSort(input_arr, arr_size, range, minimum, digit, CalcLoc);
}


void RadixSort(int *input_arr, int arr_size, int range, int minimum)
{
    int digit = 0;
    int max = ArrayGetMax(input_arr, arr_size);

    for (digit = 1; max / digit > 0; digit *= 10)
    {
        CountingSort(input_arr, arr_size, range, minimum, digit, RadixCalcLoc);
    }
}


static void HeapifyHelper(int *arr, int arr_size, size_t element_size)
{
    int last_child = arr_size - 1;
    int last_parent = (last_child - 1) / 2;
    int start = last_parent;

    while (start >= 0)
    {
        HeapifyDown(arr, HeapSortCmpFunc, start, arr_size, NULL, element_size);
        --start; 
    }
}


/* static void PrintArray(int *array, int arr_size)
{
    int i = 0;

    for (i = 0; i < arr_size; ++i)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
    printf("\n");
}
 */

void HeapSort(int *input_arr, int arr_size)
{
    int end = 0;
    int temp_int = 0;
    size_t element_size = sizeof(int);

    HeapifyHelper(input_arr, arr_size, element_size);
    end = arr_size - 1;

    
    while (end > 0)
    {
        /* SwapInts(&input_arr[0], &input_arr[end]); */
        temp_int = input_arr[end];
        input_arr[end] = input_arr[0];
        input_arr[0] = temp_int;
        HeapifyDown(input_arr, HeapSortCmpFunc, 0, end, NULL, element_size);
        --end;
    }
}


static void PerformMerge(int *input_arr, int start, int middle, int end, 
                         int *work_arr)
{
    int i = start;
    int j = middle;
    int k = 0;

    for (k = start; k < end; ++k)
    {
        if (i < middle && (j >= end || input_arr[i] <= input_arr[j]))
        {
            work_arr[k] = input_arr[i];
            ++i;
        }
        else
        {
            work_arr[k] = input_arr[j];
            ++j;
        }
    }
}


static void MergeSortIMP(int *work_arr, int start, int end, int *input_arr)
{
    int middle = 0;

    if ((end - start) < 2)
    {
        return;
    }
    
    middle = (end + start) / 2;

    MergeSortIMP(input_arr, start, middle, work_arr);
    MergeSortIMP(input_arr, middle, end, work_arr);

    PerformMerge(work_arr, start, middle, end, input_arr);
}


static void MergeSortCopyArray(int *input_arr, int start, int end, 
                               int *work_arr)
{
    int i = 0;
    
    for (i = start; i < end; ++i)
    {
        work_arr[i] = input_arr[i];
    }
}


void MergeSort(int *input_arr, int arr_size)
{
    int *work_arr = NULL;

    work_arr = (int *)calloc(arr_size, sizeof(int));

    MergeSortCopyArray(input_arr, 0, arr_size, work_arr);

    MergeSortIMP(work_arr, 0, arr_size, input_arr);

    free(work_arr);
}


static void QuickSortSwap(int *input_arr, int i, int j)
{
    int temp = input_arr[i];
    input_arr[i] = input_arr[j];
    input_arr[j] = temp;
}


static int QuickSortPartition(int *input_arr, int l_idx, int p_idx)
{
    int i = l_idx;
    int j = l_idx;

    for (i = l_idx; i <= p_idx; ++i)
    {
        if (input_arr[i] < input_arr[p_idx])
        {
            QuickSortSwap(input_arr, i, j);
            ++j;
        }
    }
        
    QuickSortSwap(input_arr, j, p_idx);

    return j;
}


static void QuickSortRec(int* input_arr, int l_idx, int r_idx)
{
    int p_idx = 0;

    if (r_idx - l_idx > 0)
    {
        p_idx = QuickSortPartition(input_arr, l_idx, r_idx);
    
        QuickSortRec(input_arr, l_idx, p_idx - 1);
        QuickSortRec(input_arr, p_idx + 1, r_idx);
    }
}


void QuickSort(int *input_arr, int arr_size)
{
    QuickSortRec(input_arr, 0, arr_size - 1);
}


static void CountingSort(int *input_arr, int arr_size, int range, int minimum,
                         int digit, arr_idx_loc_t loc_func)
{
    int *count_arr = NULL;
    int *output_arr = NULL;
    int i = 0;

    assert(NULL != input_arr);

    count_arr = (int *)calloc((range + 1), sizeof(int));
    assert(NULL != count_arr);
    output_arr = (int *)calloc(arr_size, sizeof(int));
    assert(NULL != output_arr);

    OffsetArray(input_arr, arr_size, minimum, START);

    /* get the frequency of each number in input */
    for (i = 0; i < arr_size; ++i)
    {
        ++count_arr[loc_func(input_arr, i, digit)];
    }

    /* turn histogram to location indicators */
    for (i = 1; i <= range; ++i)
    {
        count_arr[i] += count_arr[i - 1];
    }

    /* traverse from the end of the arrays and place in each 
       cell the sorted number, until the end of each numbers area*/
    for (i = arr_size - 1; i >= 0; --i)
    {
        output_arr[count_arr[loc_func(input_arr, i, digit)] - 1] = input_arr[i];
        --count_arr[loc_func(input_arr, i, digit)];
    }

    CopyArray(input_arr, output_arr, arr_size);
    OffsetArray(input_arr, arr_size, minimum, END);
    free(count_arr);
    free(output_arr);

}


static void OffsetArray(int *arr, int arr_size, int minimum, int flag)
{
    int i = 0;
    
    if (START == flag)
    {
        for (i = 0; i < arr_size; ++i)
        {
            arr[i] -= minimum;
        }
    }
    else
    {
        for (i = 0; i < arr_size; ++i)
        {
            arr[i] += minimum;
        }
    }    
}


static int ArrayGetMax(int *arr, int arr_size)
{
    int max = arr[0];
    int i = 0;

    for (i = 0; i < arr_size; ++i)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }

    return max;
}


static int CalcLoc(int *arr, int i, int digit)
{
    (void)digit;
    return arr[i];
}


static int RadixCalcLoc(int *arr, int i, int digit)
{
    return (arr[i] / digit) % 10;
}


static void SwapInts(int *i, int *j)
{
    int temp = 0;
    
    temp = *i;
    *i = *j;
    *j = temp;
}


static void CopyArray(int *sorted_arr, int *rand_arr, int arr_size)
{
    int i = 0;
    for (i = 0; i < arr_size; ++i)
    {
        sorted_arr[i] = rand_arr[i];
    }
}




static int HeapSortCmpFunc(const void *user_data, 
                           const void *array_data,
                           void *param)
{
    (void)param;

    if (*(int *)user_data > *(int *)array_data)
    {
        return 1;
    }
    else if (*(int *)user_data < *(int *)array_data)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
