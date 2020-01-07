#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strings */
#include "memlib.h" /*mem function header */

#define WORD_SIZE sizeof(size_t)



/* Copies the first n bytes from src to dest, overrides the existing data */
void *MemCpy(void *dest, const void *src, size_t n);




int main()
{

	
	char *str = "Hi everybody, today we'll learn things";
	char *str2 = "Today is going to be a great day";
	char *str3 = NULL;
	
	char *test_str = (void *)calloc(strlen(str) + 1, sizeof(char));
	char *test_str2 = (void *)calloc(strlen(str2) + 1, sizeof(char));
	
	CheckAlloc(test_str);
	strcpy(test_str, str);
	strcpy(test_str2, str2);
	
	printf("the string is: %s\n", test_str);
	printf("the string is: %s\n", test_str2);
	
	printf("the string is: %lu\n", (size_t)test_str);
	
	printf("the string is: %lu\n", (((size_t)test_str + 1) % WORD_SIZE));
	
	str2 = MemCpy(test_str+2, test_str2, 16);
	
	printf("the string is: %s\n", str2);
	
	
	free(test_str);
	free(test_str2);
	
	return (0);
}




void *MemCpy(void *dest, const void *src, size_t n)
{
	char *dest_run = dest;
	const char *src_run = src;
	size_t offset = (size_t)dest % WORD_SIZE;
	size_t i = 0;

	if (0 != offset)
	{
		offset = WORD_SIZE - offset;
	}
	
	
	/* first segment, offset */
	if (n < offset)
	{
		offset = n;
	}
	for (i = 0; i < offset; ++i)
	{
		*dest_run = *src_run;
		++dest_run;
		++src_run;
	}
	
	
	/* second segment, word sized chunks */
	n -= offset;
	
	/* check if there is enough for an entire word */
	while (n >= WORD_SIZE)
	{
		
		*(size_t *)dest_run = *(size_t *)src_run;
		dest_run += WORD_SIZE;
		src_run += WORD_SIZE;
		n -= WORD_SIZE;
	}	
	
	
	/* last segment, left overs */
	while (0 != n)
	{ 
		*(char *)dest_run = *(char *)src_run;
		--n;
		++dest_run;
		++src_run;
	}

	return (dest);
}

void CheckAlloc(void *ptr)
{
	if (NULL == ptr)
	{
		perror("There was a problem allocating memory\n");
		exit(0);
	}
}
