#include <stdio.h> /* printf */
#include <stdlib.h>

#include "heap.h"
#include "heap_test_funcs.h"
#include "utils.h"


int HeapCmpFunc(const void *user_data, const void *array_data, void *param);
int CheckArrays(void **array, void **test_array, int arr_size);

int TEST_HeapifyUp();
int TEST_HeapifyDown();



int main()
{
    RUN_TEST(TEST_HeapifyUp());
    /*RUN_TEST(TEST_HeapifyDown());*/

    return (0);
}


int TEST_HeapifyUp()
{
    /* int a = 100;
    int b = 70;
    int c = 60;
    int d = 30;
    int e = 35;
    int f = 45;
    int g = 55;
    int h = 20;
    int i = 10;
    int j = 110;
 */
    int z = 0;
    void *temp = NULL;

    void *array = NULL;
    void *test_array = NULL;
    void *start = NULL;
    /* void *end = NULL; */
    /* void *runner = NULL; */

    int basket[10] = {100, 70, 60, 30, 35, 45, 55, 20, 10, 110};

    array = malloc(8 * 10);

    start = array;
    /* runner = array; */

    for (z = 0; z < 10; ++z)
    {
        array = &basket[z];
        temp = (char *)array + z;
        printf("%d,", *(int*)temp);
        array = (char *)array + 8;
    }
    printf("\n");

    array = start;

    HeapifyUp(array, HeapCmpFunc, 9, 10, NULL);
    
    array = start;
    for (z = 0; z < 10; ++z)
    {
        printf("%d,", *(int *)((char *)array + z));
        array = (char *)array + 8;
    }
    printf("\n");


/* 
    array[0] = &i;
    array[1] = &j;
    array[2] = &a;
    array[3] = &f;
    array[4] = &g;
    array[5] = &b;
    array[6] = &c;
    array[7] = &d;
    array[8] = &e;
    array[9] = &h;
    
    test_array[0] = &j;
    test_array[1] = &g;
    test_array[2] = &a;
    test_array[3] = &f;
    test_array[4] = &h;
    test_array[5] = &b;
    test_array[6] = &c;
    test_array[7] = &d;
    test_array[8] = &e;
    test_array[9] = &i;
 */

    /* HeapifyDown(array, HeapCmpFunc, 0, 10, NULL); */

    if (SUCCESS == CheckArrays(array, test_array, 10))
    {
        return PASS;
    }

    return FAIL;
}


/* int TEST_HeapifyDown()
{
    int a = 100;
    int b = 70;
    int c = 60;
    int d = 30;
    int e = 35;
    int f = 45;
    int g = 55;
    int h = 20;
    int i = 10;
    int j = 110;

    
    void array[10] = {0};
    void test_array[10] = {0};
    
    array[0] = &a;
    array[1] = &b;
    array[2] = &c;
    array[3] = &d;
    array[4] = &e;
    array[5] = &f;
    array[6] = &g;
    array[7] = &h;
    array[8] = &i;
    array[9] = &j;
    
    test_array[0] = &j;
    test_array[1] = &a;
    test_array[2] = &c;
    test_array[3] = &d;
    test_array[4] = &b;
    test_array[5] = &f;
    test_array[6] = &g;
    test_array[7] = &h;
    test_array[8] = &i;
    test_array[9] = &e;


    HeapifyUp(array, HeapCmpFunc, 9, 10, NULL);

    if (SUCCESS == CheckArrays(array, test_array, 10))
    {
        return PASS;
    }

    return FAIL;
}
 */


int CheckArrays(void **array, void **test_array, int arr_size)
{
    int i = 0;
    for (i = 0; i < arr_size; ++i)
    {
        printf("array is %d\n", *(int*)array[i]);
        printf("test_array is %d\n\n", *(int*)test_array[i]);
        if (*(int *)array[i] != *(int *)test_array[i])
        {
            
            return FAILURE;
        }
    }

    return SUCCESS;
}    


int HeapCmpFunc(const void *user_data, const void *array_data, void *param)
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