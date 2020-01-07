#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strings */
#include <assert.h> /* assert */
#include "memlib.h" /*mem function header */

#define WORD_SIZE sizeof(size_t)

/* fill memory block byte-byte until alignment */
static void *MemSetBeforeAligment(void *ptr_run, int c, size_t *n,  size_t *offset);

/* fill memory block by Word size */
static void *MemSetByWordSize(void *ptr, int c, size_t *n, size_t *offset);

/* fill memory block with the remaining bytes */
static void *MemSetRemainder(void *ptr, int c, size_t *n);


void *MemSet(void *str, int c, size_t n)
{
	size_t offset = (size_t)str % WORD_SIZE;
	char *ptr_run = str;

	assert(NULL != str);
	assert(c >= 0);

	ptr_run = MemSetBeforeAligment((void *)ptr_run, c, &n, &offset);
	ptr_run = MemSetByWordSize((void *)ptr_run, c, &n, &offset);
	ptr_run = MemSetRemainder((void *)ptr_run, c, &n);

	return (str);
}


static void *MemSetRemainder(void *ptr, int c, size_t *n)
{
	char *ptr_run = ptr;
	
	assert(NULL != ptr);
	assert(NULL != n);
	assert(c >= 0);
	
	while (0 != *n)
	{
		*ptr_run = c;
		--*n;
		++ptr_run;
	}

	return (ptr_run);
}


static void *MemSetByWordSize(void *ptr, int c, size_t *n, size_t *offset)
{
	char *ptr_run = ptr;
	char word_arr[WORD_SIZE] = {0};
	
	assert(NULL != ptr);
	assert(NULL != n);
	assert(NULL != offset);
	assert(c >= 0);

	*n -= *offset;
	
	/* check if there is enough for an entire word */
	if (*n >= WORD_SIZE)
	{
		InitializeArr(word_arr, c);
	}
	while (*n >= WORD_SIZE)
	{
		*(size_t *)ptr_run = *(size_t *)word_arr;
		ptr_run += WORD_SIZE;
		*n -= WORD_SIZE;
	}	

	return (ptr_run);
}


static void *MemSetBeforeAligment(void *ptr, int c, size_t *n, size_t *offset)
{
	size_t i = 0;
	char *ptr_run = ptr;
	
	assert(NULL != ptr);
	assert(NULL != n);
	assert(NULL != offset);
	assert(c >= 0);
	
	if (0 != offset)
	{
		*offset = WORD_SIZE - *offset;
	}
	
	if (*n < *offset)
	{
		*offset = *n;
	}
	for (i = 0; i < *offset; ++i)
	{
		*ptr_run = c;
		++ptr_run;
	}
	
	return (ptr_run);
}
