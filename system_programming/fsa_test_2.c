#include <stdio.h>
#include <stdlib.h>

#include "fsa.h"

#define RUN_TEST(test) test ? printf("OK: "#test"\n") : printf("FAILED "#test"\n")

int main()
{
	fsa_t *fsa = NULL;
	void *element1 = NULL;
	void *element2 = NULL;

	RUN_TEST(192 == FSASuggestedSize(15, 7));
	
	fsa = (fsa_t *)malloc(190);
	fsa = FSACreate(15, 190, fsa);
	RUN_TEST(NULL != fsa);
	RUN_TEST(6 == FSACountFree(fsa));
	
	element1 = FSAAlloc(fsa);
	printf("%p\n", (char *)element1);
	element2 = FSAAlloc(fsa);
	printf("%lu\n", *(size_t *)((char *)element1 - 8));
	RUN_TEST(4 == FSACountFree(fsa));
	printf("%lu\n", FSACountFree(fsa));
	
	FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAAlloc(fsa);
	
	RUN_TEST(0 == FSACountFree(fsa));
	printf("%lu\n", FSACountFree(fsa));
	
	FSAFree(element1);
	printf("%lu\n", FSACountFree(fsa));
	RUN_TEST(1 == FSACountFree(fsa));
	
	FSAFree(element2);
	printf("%lu\n", FSACountFree(fsa));
	RUN_TEST(2 == FSACountFree(fsa));
	
	free(fsa);

	return 0;
}
