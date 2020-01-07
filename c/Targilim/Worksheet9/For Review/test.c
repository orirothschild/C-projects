#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strings */
#include "memlib.h"


#define WORD_SIZE sizeof(size_t)

int main()
{
	char *str1 = "Hi everybody";
	char *str2 = "this is the ";
	
	char *test_str1 = (void *)calloc(strlen(str1) + 1, sizeof(char));
	char *test_str2 = (void *)calloc(strlen(str2) + 1, sizeof(char));
	
	strcpy(test_str1, str1);
	strcpy(test_str2, str2);



	printf("the string is: %s\n", test_str1);
	
	printf("the address of str1 is: %p\n", test_str1);
	
/*	printf("the string is: %lu\n", (((size_t)test_str1 + 1) % WORD_SIZE));*/
	

	printf("the string is: %s\n", test_str1);
	
	printf("the address of str2 is: %p\n", test_str2);
	
/*	printf("the string is: %lu\n", (((size_t)test_str1 + 1) % WORD_SIZE));*/
	
	str2 = MemMove(test_str1 + 2, test_str1, 4);
	
	printf("the string is: %s\n", str2);
	
	
	free(test_str1);
	free(test_str2);
	
	
	return (0);

}
