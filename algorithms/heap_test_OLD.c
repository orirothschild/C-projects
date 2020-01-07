#include <stdio.h> /* printf */

#include "heap.h"
#include "utils.h"

/* static void PrintArrIMP(double **arr, size_t size); */
static int CmpIntsFuncIMP(const void *a, const void *b, void *param);

int main()
{
	
	double arr1[] = {20, 8, 7, 2, 6, 10};
	double arr2[] = {20, 8, 7, 2, 6, 30};
	double arr3[] = {1, 7, 8, 5, 2, 6};
	double arr4[] = {7, 15, 8, 5, 2, 6};
	
	size_t size = sizeof(arr1) / sizeof(arr1[0]), i = 0;
	size_t index = size - 1;
	double param = 1;
	double *arr[6];

	for(i = 0; i < size; ++i)
	{
		arr[i] = &arr1[i];
	}

	HeapifyUp(arr, CmpIntsFuncIMP, index, size, &param);

	RUN_TEST(20 == *arr[0]);
	RUN_TEST(8 == *arr[1]);
	RUN_TEST(10 == *arr[2]);
	RUN_TEST(2 == *arr[3]);
	RUN_TEST(6 == *arr[4]);
	RUN_TEST(7 == *arr[5]);

	for(i = 0; i < size; ++i)
	{
		arr[i] = &arr2[i];
	}

	HeapifyUp(arr, CmpIntsFuncIMP, index, size, &param);

	RUN_TEST(30 == *arr[0]);
	RUN_TEST(8 == *arr[1]);
	RUN_TEST(20 == *arr[2]);
	RUN_TEST(2 == *arr[3]);
	RUN_TEST(6 == *arr[4]);
	RUN_TEST(7 == *arr[5]);

	for(i = 0; i < size; ++i)
	{
		arr[i] = &arr3[i];
	}

	HeapifyDown(arr, CmpIntsFuncIMP, 0, size, &param);

	RUN_TEST(8 == *arr[0]);
	RUN_TEST(7 == *arr[1]);
	RUN_TEST(6 == *arr[2]);
	RUN_TEST(5 == *arr[3]);
	RUN_TEST(2 == *arr[4]);
	RUN_TEST(1 == *arr[5]);

	for(i = 0; i < size; ++i)
	{
		arr[i] = &arr4[i];
	}

	HeapifyDown(arr, CmpIntsFuncIMP, 0, size, &param);

	RUN_TEST(15 == *arr[0]);
	RUN_TEST(7 == *arr[1]);
	RUN_TEST(8 == *arr[2]);
	RUN_TEST(5 == *arr[3]);
	RUN_TEST(2 == *arr[4]);
	RUN_TEST(6 == *arr[5]);

	/* PrintArrIMP(arr, size); */

	return (SUCCESS);	
}

/*
static void PrintArrIMP(double **arr, size_t size)
{
	size_t i = 0;

	for(i = 0; i < size; ++i)
	{
		printf("%d ", *arr[i]);
	}

	printf("\n");
}
*/

static int CmpIntsFuncIMP(const void *a, const void *b, void *param) 
{
   	if(1 == *(double *)param)
   	{
	   return (**(double**)a - **(double**)b);
   	}
   
   	return (**(double**)b - **(double**)a);
}