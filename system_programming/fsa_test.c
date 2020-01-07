#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include "fsa.h"
#include "fsa_test_funcs.h"
#include "utils.h"

static void PrintMemory(fsa_t *fsa, size_t suggested_size);

int main()
{

    RUN_TEST(TestFSA_Create());
    TestFSA_Alloc();
    TestFSA_Alloc_Free();
    TestFSA_Alloc_Free_Many();


    return (0);
}


int TestFSA_Create()
{
    fsa_t *fsa = NULL;
    size_t element_size = 4; /* 4 */
    size_t num_of_elements = 5;
    void *allocated = NULL;
    size_t suggested_size = FSASuggestedSize(element_size, num_of_elements);
    
    allocated = (void *)malloc(suggested_size);
    
    fsa = FSACreate(element_size, suggested_size, allocated);
    
    if (FSACountFree(fsa) == num_of_elements)
    {
        free (allocated);
        return (PASS);
    }
    
    free (allocated);
    return (FAIL);
}


int TestFSA_Alloc()
{
    fsa_t *fsa = NULL;
    size_t i = 0;
    size_t element_size = 4; /* 4 */
    size_t num_of_elements = 5;
    void *allocated = NULL;
    size_t *ptr = NULL;
    size_t suggested_size = FSASuggestedSize(element_size, num_of_elements);
    void *a = NULL;
    
    printf("*****TestFSA_Alloc*****\n");
    
    allocated = (void *)malloc(suggested_size);
    
    fsa = FSACreate(element_size, suggested_size, allocated);
    
    printf("suggested size: %lu\n", suggested_size);
    printf("\n");
    ptr = (size_t *)fsa;
    for (i = 0; i < (suggested_size / 8); ++i)
    {
        printf("%d\t%lu\n", (void *)ptr, *ptr);
        ++ptr;
    }

    printf("\n");
    printf("\n");
    
    a = FSAAlloc(fsa);
    ptr = (size_t *)fsa;
    for (i = 0; i < (suggested_size / 8); ++i)
    {
        printf("%d\t%lu\n", (void *)ptr, *ptr);
        ++ptr;
    }
    printf("\n");
    printf("a is %d \n", (void *)a);
    
    
    free (allocated);
    return 0;
}


int TestFSA_Alloc_Free()
{
    fsa_t *fsa = NULL;
    size_t i = 0;
    size_t element_size = 4; /* 4 */
    size_t num_of_elements = 5;
    void *allocated = NULL;
    size_t *ptr = NULL;
    size_t suggested_size = FSASuggestedSize(element_size, num_of_elements);
    void *a = NULL;
    
    printf("*****TestFSA_Alloc_Free*****\n");
    
    allocated = (void *)malloc(suggested_size);
    
    fsa = FSACreate(element_size, suggested_size, allocated);
    
    printf("suggested size: %lu\n", suggested_size);
    printf("\n");
    ptr = (size_t *)fsa;
    for (i = 0; i < (suggested_size / 8); ++i)
    {
        printf("%d\t%lu\n", (void *)ptr, *ptr);
        ++ptr;
    }

    printf("\n");
    printf("\n");
    
    a = FSAAlloc(fsa);

    ptr = (size_t *)fsa;
    for (i = 0; i < (suggested_size / 8); ++i)
    {
        printf("%d\t%lu\n", (void *)ptr, *ptr);
        ++ptr;
    }
    printf("\n");
    printf("a is %d \n", (void *)a);
    

    FSAFree(a);

    ptr = (size_t *)fsa;
    for (i = 0; i < (suggested_size / 8); ++i)
    {
        printf("%d\t%lu\n", (void *)ptr, *ptr);
        ++ptr;
    }
    printf("\n");

    free (allocated);
    return 0;
}


int TestFSA_Alloc_Free_Many()
{
    fsa_t *fsa = NULL;

    size_t element_size = 4; /* 4 */
    size_t num_of_elements = 10;
    void *allocated = NULL;
    size_t *ptr = NULL;
    size_t suggested_size = FSASuggestedSize(element_size, num_of_elements);
    void *a, *b, *c, *d, *e = NULL;

    printf("*****TestFSA_Alloc_Free_Many*****\n");
    
    allocated = (void *)malloc(suggested_size);
    
    fsa = FSACreate(element_size, suggested_size, allocated);
    
    printf("suggested size: %lu\n", suggested_size);
    printf("\n");
    PrintMemory(fsa, suggested_size);

    printf("\n");
    printf("\n");
    
    a = FSAAlloc(fsa);
    PrintMemory(fsa, suggested_size);
    printf("a is %d \n", (void *)a);
    printf("\n");
    
    b = FSAAlloc(fsa);
    PrintMemory(fsa, suggested_size);
    printf("b is %d \n", (void *)b);
    printf("\n");

    c = FSAAlloc(fsa);
    PrintMemory(fsa, suggested_size);
    printf("c is %d \n", (void *)c);
    printf("\n"); 

    d = FSAAlloc(fsa);
    PrintMemory(fsa, suggested_size);
    printf("d is %d \n", (void *)d);    
    printf("\n");

    e = FSAAlloc(fsa);
    PrintMemory(fsa, suggested_size);
    printf("e is %d \n", (void *)e);
    printf("\n");
    
    printf("\n");
    printf("*************************************\n");
    printf("\n");
    
    FSAFree(e);
    PrintMemory(fsa, suggested_size);
    printf("e was freed\n");    
    printf("\n");
    
    FSAFree(d);
    PrintMemory(fsa, suggested_size);
    printf("d was freed\n");    
    printf("\n");
    
    FSAFree(c);
    PrintMemory(fsa, suggested_size);
    printf("c was freed\n");    
    printf("\n");
    
    FSAFree(b);
    PrintMemory(fsa, suggested_size);
    printf("b was freed\n");    
    printf("\n");
    
    FSAFree(a);
    PrintMemory(fsa, suggested_size);
    printf("a was freed\n");    
    printf("\n");
    
    free (allocated);
    return 0;
}

static void PrintMemory(fsa_t *fsa, size_t suggested_size)
{
    size_t i = 0;
    size_t *ptr = NULL;
    
    ptr = (size_t *)fsa;
    
    for (i = 0; i < (suggested_size / 8); ++i)
    {
        printf("%d\t%lu\n", (void *)ptr, *ptr);
        ++ptr;
    }
}
