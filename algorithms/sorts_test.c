#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <stdlib.h> /* rand */

#include "sorts.h"  /* API */


typedef void (*sort_func_t)(int *arr, int arr_size);
typedef void (*rc_sort_func_t)(int *arr, int arr_size, int range, int minimum);

static void CopyArray(int *sorted_arr, int *rand_arr, int arr_size);
/* static void PrintArray(int *array, int arr_size); */
static void IsSortedArray(int *sorted_arr, int arr_size, char *str);
static void BuildRandomArray(int *arr, int size);
static void CheckArray(int *sorted_arr, int *rand_arr, int arr_size, 
                      sort_func_t sort_func, char *str);
static void CheckArrayQSort(int *sorted_arr, int *rand_arr, int arr_size, 
                           char *str);
static void CheckArrayCountRadix(int *sorted_arr, int *rand_arr, int arr_size,
                                 int range, int minimum, 
                                 rc_sort_func_t sort_func, char *str);

#define ARR_SIZE 10
#define RANGE 200
#define MAX_RAND 199
#define MIN_RAND 0
#define START 1
#define END 0
#define DIGITS 10

int main()
{
    int arr_size = ARR_SIZE;
    int rand_arr[ARR_SIZE] = {0};
    int sorted_arr[ARR_SIZE] = {0};

    char *bubble = "Bubble-Sort               : ";
    char *smarterbubble = "Smarter-Bubble-Sort       : ";
    char *evensmarterbubble = "Even-Smarter-Bubble-Sort  : ";
    char *selection = "Selection-Sort            : ";
    char *insertion = "Insertion-Sort            : ";
    char *qsort = "Q-Sort                    : ";
    char *counting = "Counting-Sort             : ";
    char *radix = "Radix-Sort                : ";
    char *mergesort = "Merge-Sort                : ";
    char *quicksort = "Quick-Sort                : ";
    char *heapsort = "Heap-Sort                 : ";


    BuildRandomArray(rand_arr, arr_size);

    CheckArray(sorted_arr, rand_arr, arr_size, BubbleSort, bubble);
    CheckArray(sorted_arr, rand_arr, arr_size, SmarterBubbleSort, 
               smarterbubble);
    CheckArray(sorted_arr, rand_arr, arr_size, EvenSmarterBubbleSort, 
              evensmarterbubble);
    CheckArray(sorted_arr, rand_arr, arr_size, SelectionSort, selection);
    CheckArray(sorted_arr, rand_arr, arr_size, InsertionSort, insertion);
    CheckArrayQSort(sorted_arr, rand_arr, arr_size, qsort);
    CheckArrayCountRadix(sorted_arr, rand_arr, arr_size, RANGE, MIN_RAND, 
                         CountSort, counting);
    CheckArrayCountRadix(sorted_arr, rand_arr, arr_size, DIGITS, MIN_RAND,
                         RadixSort, radix);
    
    CheckArray(sorted_arr, rand_arr, arr_size, MergeSort, mergesort);
    
    CheckArray(sorted_arr, rand_arr, arr_size, QuickSort, quicksort);
    CheckArray(sorted_arr, rand_arr, arr_size, HeapSort, heapsort);
    
    return 0;
}


static void BuildRandomArray(int *arr, int size)
{
    int i = 0;
    srand(time(NULL));

    for (i = 0; i < size; ++i)
    {
        arr[i] = (rand() % RANGE) + MIN_RAND;
    }
}

static int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

static void CheckArray(int *sorted_arr, int *rand_arr, int arr_size, 
                       sort_func_t sort_func, char *str)
{
    clock_t begin = 0;
    clock_t end = 0;

    CopyArray(sorted_arr, rand_arr, arr_size);
    begin = clock();
    sort_func(sorted_arr, arr_size);
    end = clock();
    printf("%s%f\n", str,  (double)(end - begin) / CLOCKS_PER_SEC);

    IsSortedArray(sorted_arr, arr_size, str);
}

static void CheckArrayCountRadix(int *sorted_arr, int *rand_arr, int arr_size,
                                 int range, int minimum,
                                 rc_sort_func_t sort_func, char *str)
{
    clock_t begin = 0;
    clock_t end = 0;

    CopyArray(sorted_arr, rand_arr, arr_size);
    begin = clock();
    sort_func(sorted_arr, arr_size, range, minimum);
    end = clock();
    printf("%s%f\n", str,  (double)(end - begin) / CLOCKS_PER_SEC);

    IsSortedArray(sorted_arr, arr_size, str);
}

static void CheckArrayQSort(int *sorted_arr, int *rand_arr, int arr_size, 
                           char *str)
{
    clock_t begin = 0;
    clock_t end = 0;

    CopyArray(sorted_arr, rand_arr, arr_size);
    begin = clock();
    qsort(sorted_arr, arr_size, sizeof(int), compare);
    end = clock();
    printf("%s%f\n", str,  (double)(end - begin) / CLOCKS_PER_SEC);

    IsSortedArray(sorted_arr, arr_size, str);
}

static void IsSortedArray(int *sorted_arr, int arr_size, char *str)
{
    int i = 0;

    for (i = 1; i < arr_size; ++i)
    {
        if (sorted_arr[i - 1] > sorted_arr[i])
        {
            printf("%sis not sorted\n", str);
            return;
        }
    }

    printf("%sis sorted\n", str);
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
} */

static void CopyArray(int *sorted_arr, int *rand_arr, int arr_size)
{
    int i = 0;
    for (i = 0; i < arr_size; ++i)
    {
        sorted_arr[i] = rand_arr[i];
    }
}
