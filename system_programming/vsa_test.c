#include <stdio.h>  /*for printf*/
#include <stdlib.h> /*for malloc*/

#include "vsa.h"
#include "utils.h"
/*#define RUN_TEST(test) test ? printf("OK: " #test "\n") : \
                              printf("FAILED:  " #test "\n");
                              */
/*static void PrintMemory(vsa_t *vsa, size_t suggested_size);*/
int DebugFlow();
int ReleaseFlow();


int main()
{
#ifndef NDEBUG
	DebugFlow();
#else
	ReleaseFlow();
#endif
    return (0);
}


int DebugFlow()
{
	void *allocated = malloc (300);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	/*long whaaa = 0;*/
	
	vsa_t *memory_space = VSAInit(300, allocated);
	printf ("allocated address begin at %p\n", allocated);

	RUN_TEST (264 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	block1 = VSAAlloc(memory_space, 160);
	RUN_TEST (NULL != block1);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (88 == VSALargestChunkAvail(memory_space));
	block2 = VSAAlloc(memory_space, 16);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (56 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	
	VSAFree(block2);
/*	whaaa = VSALargestChunkAvail(memory_space);*/
/*	printf ("%ld\n", whaaa);*/
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (88 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (NULL == VSAAlloc(memory_space, 100));
	block2 = VSAAlloc(memory_space, 20);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (48 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	
	block3 = VSAAlloc(memory_space, 20);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (8 == VSALargestChunkAvail(memory_space));
	block4 = VSAAlloc(memory_space, 16);
	RUN_TEST (NULL == block4);
	RUN_TEST (8 == VSALargestChunkAvail(memory_space));
	
	VSAFree(block1);
	VSAFree(block2);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (200 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	block1 = VSAAlloc(memory_space, 184);
/*	PrintMemory(memory_space, 296);*/
	VSAFree(block3);
	RUN_TEST (48 == VSALargestChunkAvail(memory_space));
	block2 = VSAAlloc(memory_space, 32);
	RUN_TEST (0 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	
	VSAFree(block1);
	VSAFree(block2);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (264 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/

	block1 = VSAAlloc(memory_space, 264);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (0 == VSALargestChunkAvail(memory_space));
		
	free (allocated);
	return 0;
}


int ReleaseFlow()
{
	void *allocated = malloc (300);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	/*long whaaa = 0;*/
	
	vsa_t *memory_space = VSAInit(300, allocated);
	printf ("allocated address begin at %p\n", allocated);

	RUN_TEST (280 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	block1 = VSAAlloc(memory_space, 160);
	RUN_TEST (NULL != block1);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (112 == VSALargestChunkAvail(memory_space));
	block2 = VSAAlloc(memory_space, 16);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (88 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	
	VSAFree(block2);
/*	whaaa = VSALargestChunkAvail(memory_space);*/
/*	printf ("%ld\n", whaaa);*/
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (112 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
/*	RUN_TEST (NULL == VSAAlloc(memory_space, 100));*/
	block2 = VSAAlloc(memory_space, 100);
/*	PrintMemory(memory_space, 296);*/
	/*whaaa = VSALargestChunkAvail(memory_space);
	printf ("%ld\n", whaaa);*/
	RUN_TEST (0 == VSALargestChunkAvail(memory_space));
	/*PrintMemory(memory_space, 296);
	whaaa = VSALargestChunkAvail(memory_space);
	printf ("%ld\n", whaaa);*/
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (NULL == VSAAlloc(memory_space, 20));
	block3 = VSAAlloc(memory_space, 16);
	RUN_TEST (NULL == block3);
/*	PrintMemory(memory_space, 296);*/
	VSAFree(block1);
	VSAFree(block2);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (280 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/
	block1 = VSAAlloc(memory_space, 184);
/*	PrintMemory(memory_space, 296);*/

	RUN_TEST (88 == VSALargestChunkAvail(memory_space));
	/*PrintMemory(memory_space, 296);*/
	block2 = VSAAlloc(memory_space, 32);
	RUN_TEST (48 == VSALargestChunkAvail(memory_space));
	/*PrintMemory(memory_space, 296);*/
	
	VSAFree(block1);
	VSAFree(block2);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (280 == VSALargestChunkAvail(memory_space));
/*	PrintMemory(memory_space, 296);*/

	block1 = VSAAlloc(memory_space, 280);
/*	PrintMemory(memory_space, 296);*/
	RUN_TEST (0 == VSALargestChunkAvail(memory_space));
		
	free (allocated);
	return 0;
}


/*static void PrintMemory(vsa_t *vsa, size_t suggested_size)
{
   size_t i = 0;
   long *ptr = NULL;    
   ptr = (long *)vsa;    
   for (i = 0; i < suggested_size / 8; ++i)
   {
       printf("%p\t%ld\n", (void *)ptr, *ptr);
       ++ptr;
   }
   printf ("FIN\n");
}*/

