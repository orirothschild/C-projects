#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strings */
#include <assert.h> /* assert */
#include "memlib.h" /*mem function header */

#define WORD_SIZE sizeof(size_t)

/* fill memory block byte-byte until alignment */
static void *MemMoveBeforeAlignment(void *dest, const void **src, size_t *n, size_t *offset);

/* fill memory block by Word size */
static void *MemMoveByWordSize(void *dest, const void **src, size_t *n, size_t *offset);

/* fill memory block with the remaining bytes */
static void *MemMoveRemainder(void *dest, const void **src, size_t *n);


void *MemMove(void *dest, const void *src, size_t n)
{
	char *dest_run = dest;
	const char *src_run = src;
	size_t offset = (size_t)dest % WORD_SIZE;
	int distance = dest_run - src_run;
	
	if ((distance >= (int)n))
	{	
		return (MemCpy(dest, src, n));
	}

	dest_run = MemMoveBeforeAlignment(dest_run, (const void **)&src_run, &n, &offset);
	dest_run = MemMoveByWordSize(dest_run, (const void **)&src_run, &n, &offset);
	dest_run = MemMoveRemainder(dest_run, (const void **)&src_run, &n);
	
	return ((char *)dest - offset);
}


static void *MemMoveRemainder(void *dest, const void **src, size_t *n)
{
	char *dest_run = dest;
	const char **src_run = (const char **)src;

	
	/* last segment, left overs */
	while (0 != *n)
	{ 
		--dest_run;
		--*src_run;
		*(char *)dest_run = *(char *)*src_run;
		--*n;
	}
	
	return (dest_run);
}


static void *MemMoveByWordSize(void *dest, const void **src, size_t *n, size_t *offset)
{
	char *dest_run = dest;
	const char **src_run = (const char **)src;

	assert(NULL != dest);
	assert(NULL != *src);
	assert(NULL != n);
	assert(NULL != offset);
	
	/* second segment, word sized chunks */
	*n -= *offset;
	
	/* check if there is enough for an entire word */
	while (*n >= WORD_SIZE)
	{
		dest_run -= WORD_SIZE;
		*src_run -= WORD_SIZE;
		*(size_t *)dest_run = *(size_t *)*src_run;
		*n -= WORD_SIZE;
	}	
	
	return (dest_run);
}


static void *MemMoveBeforeAlignment(void *dest, const void **src, size_t *n, size_t *offset)
{
	size_t i = 0;
	char *dest_run = dest;
	const char **src_run = (const char **)src;	
	
	assert(NULL != dest);
	assert(NULL != *src);
	assert(NULL != n);
	assert(NULL != offset);
	
	dest_run += *n;
	*src_run += *n;
	
	if (*n < *offset)
	{
		*offset = *n;
	}
	
	for (i = 0; i < *offset; ++i)
	{
		--dest_run;
		--*src_run;
		*dest_run = **src_run;
	}
	
	return (dest_run);
}
