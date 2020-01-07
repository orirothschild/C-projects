#include <stdio.h> /* printf */

#include "pqheap.h"
#include "pqheap_test_funcs.h"
#include "utils.h"


typedef struct bob
{
    int a;
    int b;
    void *ptr;
    int *int_ptr;
}test_t;

int CheckArrays(int *arr1, int *arr2, int arr_size);
int CompareFuncInts(const void *node_data, const void *match_data, 
                  void *param);
int MatchFuncInts(const void *node_data, const void *match_data, 
                  const void *param);
int HeapCmpFunc(const void *user_data, const void *array_data, void *param);

int main()
{
    RUN_TEST(TestPQueue_Create());
    RUN_TEST(TestPQueue_Size_Five());
    RUN_TEST(TestPQueue_Insert_Five());
    RUN_TEST(TestPQueue_IsEmpty_False());
    RUN_TEST(TestPQueue_IsEmpty_True());
    RUN_TEST(TestPQueue_Remove_End());
    RUN_TEST(TestPQueue_Remove_Middle());
    RUN_TEST(TestPQueue_Insert_structs());


    return (0);
}


int TestPQueue_Create()
{
    p_queue_t *pq = PQueueCreate(CompareFuncInts);
    
    if(NULL != pq)
    {
        PQueueDestroy(pq);
        return (PASS);
    }
    
    PQueueDestroy(pq);
    return (FAIL);
}


int TestPQueue_Size_Five()
{
    p_queue_t *pq = PQueueCreate(HeapCmpFunc);
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    
    PQueueEnqueue(pq, &i);
    PQueueEnqueue(pq, &j);
    PQueueEnqueue(pq, &m);
    PQueueEnqueue(pq, &l);
    PQueueEnqueue(pq, &k);
    
    
    if(5 == PQueueSize(pq))
    {
        PQueueDestroy(pq);
        return (PASS);
    }
    
    PQueueDestroy(pq);
    return (FAIL);
}


int TestPQueue_Insert_Five()
{
    p_queue_t *pq = PQueueCreate(CompareFuncInts);
    
    int temp = 0;
    int z = 0;
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;

    int array[5] = {25, 20, 15, 10, 5};
    int test_arr[5] = {0};
    int arr_size = 5;
    
    PQueueEnqueue(pq, &i);
    PQueueEnqueue(pq, &j);
    PQueueEnqueue(pq, &m);
    PQueueEnqueue(pq, &l);
    PQueueEnqueue(pq, &k);

    temp = **(int **)PQueuePeekTest(pq, 0);
    temp = **(int **)PQueuePeekTest(pq, 1);
    temp = **(int **)PQueuePeekTest(pq, 2);
    temp = **(int **)PQueuePeekTest(pq, 3);
    temp = **(int **)PQueuePeekTest(pq, 4);

    for (z = 0; z < arr_size; ++z)
    {
        temp = **(int **)PQueuePeek(pq);
        test_arr[z] = temp;
        PQueueDequeue(pq);
    }
    
    if(True == CheckArrays(array, test_arr, arr_size))
    {
        PQueueDestroy(pq);
        return (PASS);
    }
    
    PQueueDestroy(pq);
    return (FAIL);
}


int TestPQueue_IsEmpty_False()
{
    p_queue_t *pq = PQueueCreate(CompareFuncInts);
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    
    PQueueEnqueue(pq, &i);
    PQueueEnqueue(pq, &j);
    PQueueEnqueue(pq, &m);
    PQueueEnqueue(pq, &l);
    PQueueEnqueue(pq, &k);

    if(False == PQueueIsEmpty(pq))
    {
        PQueueDestroy(pq);
        return (PASS);
    }
    
    PQueueDestroy(pq);
    return (FAIL);
}


int TestPQueue_IsEmpty_True()
{
     p_queue_t *pq = PQueueCreate(CompareFuncInts);

    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;

    PQueueEnqueue(pq, &i);
    PQueueEnqueue(pq, &j);
    PQueueEnqueue(pq, &m);
    PQueueEnqueue(pq, &l);
    PQueueEnqueue(pq, &k);

    PQueueDequeue(pq);
    PQueueDequeue(pq);
    PQueueDequeue(pq);
    PQueueDequeue(pq);
    PQueueDequeue(pq);
    
    if(True == PQueueIsEmpty(pq))
    {
        PQueueDestroy(pq);
        return (PASS);
    }
    
    PQueueDestroy(pq);
    return (FAIL);
}


int TestPQueue_Remove_End()
{
    p_queue_t *pq = PQueueCreate(CompareFuncInts);
    
    int temp = 0;

    int z = 0;
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;

    int array[5] = {25, 20, 10, 5, 0};
    int test_arr[5] = {0};
    int arr_size = 5;
    
    PQueueEnqueue(pq, &i);
    PQueueEnqueue(pq, &j);
    PQueueEnqueue(pq, &m);
    PQueueEnqueue(pq, &l);
    PQueueEnqueue(pq, &k);

    temp = **(int **)PQueuePeekTest(pq, 0);
    temp = **(int **)PQueuePeekTest(pq, 1);
    temp = **(int **)PQueuePeekTest(pq, 2);
    temp = **(int **)PQueuePeekTest(pq, 3);
    temp = **(int **)PQueuePeekTest(pq, 4);

    temp = **(int **)PQueueRemove(pq, MatchFuncInts, &k);

    for (z = 0; z < arr_size - 1; ++z)
    {
        temp = **(int **)PQueuePeek(pq);
        test_arr[z] = temp;
        PQueueDequeue(pq);
    }
    
    if(True == CheckArrays(array, test_arr, arr_size - 1))
    {
        PQueueDestroy(pq);
        return (PASS);
    }
    
    PQueueDestroy(pq);
    return (FAIL);
}


int TestPQueue_Remove_Middle()
{
    p_queue_t *pq = PQueueCreate(CompareFuncInts);
    
    int temp = 0;

    int z = 0;
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;

    int array[5] = {25, 15, 10, 5, 0};
    int test_arr[5] = {0};
    int arr_size = 5;
    
    PQueueEnqueue(pq, &i);
    PQueueEnqueue(pq, &j);
    PQueueEnqueue(pq, &m);
    PQueueEnqueue(pq, &l);
    PQueueEnqueue(pq, &k);

    temp = **(int **)PQueuePeekTest(pq, 0);
    temp = **(int **)PQueuePeekTest(pq, 1);
    temp = **(int **)PQueuePeekTest(pq, 2);
    temp = **(int **)PQueuePeekTest(pq, 3);
    temp = **(int **)PQueuePeekTest(pq, 4);

    temp = **(int **)PQueueRemove(pq, MatchFuncInts, &l);

    for (z = 0; z < arr_size - 1; ++z)
    {
        temp = **(int **)PQueuePeek(pq);
        test_arr[z] = temp;
        PQueueDequeue(pq);
    }
    
    if(True == CheckArrays(array, test_arr, arr_size - 1))
    {
        PQueueDestroy(pq);
        return (PASS);
    }
    
    PQueueDestroy(pq);
    return (FAIL);
}


int TestPQueue_Insert_structs()
{
    p_queue_t *pq = PQueueCreate(HeapCmpFunc);
    
    int blerg = 5;
    test_t i = {0};
    test_t j = {0};
    test_t k = {0};
    test_t l = {0};
    test_t m = {0};
    
    i.a = 1;
    i.b = 10;
    i.ptr = &i;
    i.int_ptr = &blerg;

    j.a = 2;
    j.b = 3;
    j.ptr = &j;
    j.int_ptr = NULL;
    
    k.a = 4;
    k.b = 5;
    k.ptr = &k;
    k.int_ptr = NULL;

    l.a = 6;
    l.b = 7;
    l.ptr = &l;
    l.int_ptr = NULL;

    m.a = 8;
    m.b = 9;
    m.ptr = &m;
    m.int_ptr = NULL;
    
    PQueueEnqueue(pq, &i);
    PQueueEnqueue(pq, &j);
    PQueueEnqueue(pq, &m);
    PQueueEnqueue(pq, &l);
    PQueueEnqueue(pq, &k);
    
    
    if(5 == PQueueSize(pq))
    {
        PQueueDestroy(pq);
        return (PASS);
    }
    
    PQueueDestroy(pq);
    return (FAIL);
}





/******************************************************************************/
int MatchFuncInts(const void *node_data, const void *match_data, 
                  const void *param)
{
	(void)param;
	
	return (*(int *)node_data == **(int **)match_data);
}


int ActionFuncIntAddition(void *data, void *param)
{
	if (50 == *(int *)data + *(int *)param)
	{
		return (1);
	}
	return (0);
}


int CompareFuncInts(const void *node_data, const void *match_data, 
                  void *param)
{
	(void)param;
	
	return (*(int *)node_data > *(int *)match_data);
}



int CheckArrays(int *arr1, int *arr2, int arr_size)
{
	int i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return (False);
		}
	}
	
	return (True);
}

int HeapCmpFunc(const void *user_data, const void *array_data, void *param)
{
    (void)param;

    if (**(int **)user_data > **(int **)array_data)
    {
        return 1;
    }
    else if (**(int **)user_data < **(int **)array_data)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}