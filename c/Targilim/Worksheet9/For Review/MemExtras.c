#include <stdio.h> /* printf */
#include <stdlib.h> /* exit */
#include <assert.h> /* assert */

#define WORD_SIZE sizeof(size_t)


void CheckAlloc(void *ptr)
{
	if (NULL == ptr)
	{
		perror("There was a problem allocating memory\n");
		exit(0);
	}
}


void InitializeArr(char *word_arr, int c)
{
	size_t i = 0;
	
	assert(NULL != word_arr);
	assert(c >= 0);
	
	for (i = 0; i < WORD_SIZE; ++i)
	{
		word_arr[i] = c;
	}
}
