#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strings */
#include "memlib.h" /*mem function header */


#define WORD_SIZE sizeof(size_t)

/* fill byte-byte until alignment */
static void *MemSetBeforeAligment(void *ptr_run, int c, size_t n,  size_t *offset);

/* fill by word size */
static void *MemSetByWordSize(void *ptr, int c, size_t *n, size_t *offset);


/* fill the remaining bytes */
static void *MemSetRemainder(void *ptr, int c, size_t *n);


int main()
{
	char *str = "Hi everybody, today we'll learn things";
	char *str2 = NULL;
	char *test_str = (void *)calloc(strlen(str) + 1, sizeof(char));
	
	CheckAlloc(test_str);
	strcpy(test_str, str);
	
	printf("the string is: %s\n", test_str);
	
	printf("the string is: %lu\n", (size_t)test_str);
	
	printf("the string is: %lu\n", (((size_t)test_str + 1) % WORD_SIZE));
	
	str2 = MemSet(test_str+2, 'a', 20);
	
	printf("the string is: %s\n", str2);
	
	
	free(test_str);
	
	return (0);
}




void *MemSet(void *str, int c, size_t n)
{
	size_t offset = (size_t)str % WORD_SIZE;
/*	size_t i = 0;*/
	char *ptr_run = str;
/*	char word_arr[WORD_SIZE] = {0};*/
	
/*	if (0 != offset)*/
/*	{*/
/*		offset = WORD_SIZE - offset;*/
/*	}*/
	ptr_run = MemSetBeforeAligment((void *)ptr_run, c, n, &offset);
	
/*	*/
/*	 first segment, offset */
/*	if (n < offset)*/
/*	{*/
/*		offset = n;*/
/*	}*/
/*	for (i = 0; i < offset; ++i)*/
/*	{*/
/*		*ptr_run = c;*/
/*		++ptr_run;*/
/*	}*/
	

	ptr_run = MemSetByWordSize((void *)ptr_run, c, &n, &offset);
/*	 second segment, word sized chunks */
/*	n -= offset;*/
/*	*/
/*	 check if there is enough for an entire word */
/*	if (n >= WORD_SIZE)*/
/*	{*/
/*		InitializeArr(word_arr, c);*/
/*	}*/
/*	while (n >= WORD_SIZE)*/
/*	{*/
/*		*/
/*		*(size_t *)ptr_run = *(size_t *)word_arr;*/
/*		ptr_run += WORD_SIZE;*/
/*		n -= WORD_SIZE;*/
/*	}	*/
	
	ptr_run = MemSetRemainder((void *)ptr_run, c, &n);
	/* last segment, left overs */
/*	while (0 != n)*/
/*	{*/
/*		*ptr_run = c;*/
/*		--n;*/
/*		++ptr_run;*/
/*	}*/

	return (str);
}


static void *MemSetRemainder(void *ptr, int c, size_t *n)
{
	char *ptr_run = ptr;
	
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
	
	/* second segment, word sized chunks */
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


static void *MemSetBeforeAligment(void *ptr, int c, size_t n, size_t *offset)
{
/*	size_t offset = (size_t)ptr % WORD_SIZE;*/
	size_t i = 0;
	char *ptr_run = ptr;
	
	if (0 != offset)
	{
		*offset = WORD_SIZE - *offset;
	}
	
	/* first segment, offset */
	if (n < *offset)
	{
		*offset = n;
	}
	for (i = 0; i < *offset; ++i)
	{
		*ptr_run = c;
		++ptr_run;
	}
	
	return (ptr_run);
}

void InitializeArr(char *word_arr, int c)
{
	size_t i = 0;
	
	for (i = 0; i < WORD_SIZE; ++i)
	{
		word_arr[i] = c;
	}
}

void CheckAlloc(void *ptr)
{
	if (NULL == ptr)
	{
		perror("There was a problem allocating memory\n");
		exit(0);
	}
}



