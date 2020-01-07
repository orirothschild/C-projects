#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strings */
#include <assert.h> /* assert */
#include "memlib.h" /*mem function header */

#define WORD_SIZE sizeof(size_t)

/* fill memory block byte-byte until alignment */
static void *MemCpyBeforeAlignment(void *dest, const void **src, size_t *n, size_t *offset);

/* fill memory block by Word size */
static void *MemCpyByWordSize(void *dest, const void **src, size_t *n, size_t *offset);

/* fill memory block with the remaining bytes */
static void *MemCpyRemainder(void *dest, const void **src, size_t *n);


void *MemCpy(void *dest, const void *src, size_t n)
{
	char *dest_run = dest;
	const char *src_run = src;
	size_t offset = (size_t)dest % WORD_SIZE;

	dest_run = MemCpyBeforeAlignment(dest_run, (const void **)&src_run, &n, &offset);
	dest_run = MemCpyByWordSize(dest_run, (const void **)&src_run, &n, &offset);
	dest_run = MemCpyRemainder(dest_run, (const void **)&src_run, &n);
	
	offset = (size_t)dest % WORD_SIZE;
	
	return ((char *)dest - offset);
}


static void *MemCpyRemainder(void *dest, const void **src, size_t *n)
{
	char *dest_run = dest;
	const char **src_run = (const char **)src;
	
	assert(NULL != dest);
	assert(NULL != *src);
	assert(NULL != n);


	while (0 != *n)
	{ 
		*dest_run = **src_run;
		--*n;
		++dest_run;
		++*src_run;
	}
	
	return (dest_run);
}


static void *MemCpyByWordSize(void *dest, const void **src, size_t *n, size_t *offset)
{
	char *dest_run = dest;
	const char **src_run = (const char **)src;
	
	assert(NULL != dest);
	assert(NULL != *src);
	assert(NULL != n);
	assert(NULL != offset);

	*n -= *offset;
	
	/* check if there is enough for an entire word */
	while (*n >= WORD_SIZE)
	{
		*(size_t *)dest_run = *(size_t *)*src_run;
		dest_run += WORD_SIZE;
		*src_run += WORD_SIZE;
		*n -= WORD_SIZE;
	}
	
	return (dest_run);
}


static void *MemCpyBeforeAlignment(void *dest, const void **src, size_t *n, size_t *offset)
{
	size_t i = 0;
	char *dest_run = dest;
	const char **src_run = (const char **)src;	
	
	assert(NULL != dest);
	assert(NULL != *src);
	assert(NULL != n);
	assert(NULL != offset);

	if (0 != *offset)
	{
		*offset = WORD_SIZE - *offset;
	}
	
	if (*n < *offset)
	{
		*offset = *n;
	}
	for (i = 0; i < *offset; ++i)
	{
		*dest_run = **src_run;
		++dest_run;
		++*src_run;
	}
	
	return (dest_run);
}
