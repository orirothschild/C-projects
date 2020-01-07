#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */
#include <ctype.h> /* toupper */
#include <string.h> /* strlen */
#include <assert.h> /* assert */

#define LETTERS 26
#define DISTANCE 65

static void CheckArray(int *result_arr, char *array, int arr_size, 
					   int arr_to_check);

void ThreeArrays(char *arr1, size_t arr1_size,
				 char *arr2, size_t arr2_size,
				 char *arr3, size_t arr3_size);

int main()
{
	char *arr1 = "abcdefghijjlmnopqrstuvwxyz";
	char *arr2 = "abcghl";
	char *arr3 = "ab";
	int arr1_len = strlen(arr1);
	int arr2_len = strlen(arr2);
	int arr3_len = strlen(arr3);
	
	
	ThreeArrays(arr1, arr1_len, arr2, arr2_len, arr3, arr3_len);

	return (0);
}


void ThreeArrays(char *arr1, size_t arr1_size,
				 char *arr2, size_t arr2_size,
				 char *arr3, size_t arr3_size)
{
	int result_arr[LETTERS] = {0};
	unsigned int i = 0;
	int arr0_letter = 0;
	int arr1_letter = 1;
	int arr2_letter = 2;
	
	assert(NULL != arr1);
	assert(NULL != arr2);
	assert(NULL != arr3);
		
	CheckArray(result_arr, arr1, arr1_size, arr0_letter);
	CheckArray(result_arr, arr2, arr2_size, arr1_letter);
	CheckArray(result_arr, arr3, arr3_size, arr2_letter);

	for (i = 0; i < LETTERS + 1; ++i)
	{
		if (arr2_letter == result_arr[i])
		{
			printf("%c ", i + DISTANCE);
		}
	}
	
	printf("\n");
}


static void CheckArray(int *result_arr, char *array, int arr_size,
					   int arr_to_check)
{
	int i = 0;
	int place  = 0;
	
	assert(NULL != result_arr);
	assert(NULL != array);
	assert(0 <= arr_size);
	
	for (i = 0; i < arr_size; ++i)
	{
		place = (toupper(*(array + i)) - DISTANCE);
		if (arr_to_check == result_arr[place])
		{
			result_arr[place] = (char)(arr_to_check + 1);
		}
	}
}
