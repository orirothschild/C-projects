#include <stdio.h> /* printf */

#include "pqueue.h"
#include "pqueue_test_funcs.h"
#include "utils.h"

int CheckArrays(int *arr1, int *arr2, int arr_size);
int CompareFuncInts(const void *node_data, const void *match_data, 
                  void *param);

int main()
{
    RUN_TEST(TestPQueue_Create());
    RUN_TEST(TestPQueue_Size_Five());
    RUN_TEST(TestPQueue_Insert_Five());
    RUN_TEST(TestPQueue_IsEmpty_False());
    RUN_TEST(TestPQueue_IsEmpty_True());
    

    
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
    
    int z = 0;
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;

    int array[5] = {5, 10, 15, 20, 25};
    int test_arr[5] = {0};
    int arr_size = 5;
    
    PQueueEnqueue(pq, &i);
    PQueueEnqueue(pq, &j);
    PQueueEnqueue(pq, &m);
    PQueueEnqueue(pq, &l);
    PQueueEnqueue(pq, &k);

    for (z = 0; z < arr_size; ++z)
    {
        test_arr[z] = *(int *)PQueuePeek(pq);
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





/******************************************************************************/
int MatchFuncInts(const void *node_data, const void *match_data, 
                  const void *param)
{
	(void)param;
	
	return (*(int *)node_data == *(int *)match_data);
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
