/***********************************
*                                  *
*   DS - FSA                       *
*   written by: Hadar Klein        *
*   reviewed by: Dafna Cohen       *
*                                  *
***********************************/

#include <stdio.h>
#include <assert.h>

#include "fsa.h"
#include "utils.h"

#define MOVE(a, b) ((char *)a + b)

struct fsa
{
    size_t offset;
    size_t element_size;
    size_t total_size;
};

static void SwapLocals(fsa_t *first, void *second);
const size_t MIN_ELEM_SIZE = WORD_SIZE;
const size_t STRUCT_SIZE = sizeof(fsa_t);
const size_t POINTER_SIZE = WORD_SIZE;
static size_t CalcElemSize(size_t user_element_size);
static size_t CalcNumOfElements(fsa_t *fsa, size_t user_element_size);


fsa_t *FSACreate(size_t element_size, size_t total_size, void *allocated)
{
    fsa_t *fsa = NULL;
    size_t i = 0;
    size_t new_element_size = 0;
    size_t num_of_elements = 0;
    size_t offset = sizeof(fsa_t);
    void *block = NULL;
    
    assert(NULL != allocated);
    
    fsa = (fsa_t *)allocated;
    fsa->element_size = element_size;
    fsa->total_size = total_size;
    fsa->offset = offset;
    
    new_element_size = CalcElemSize(element_size);
    num_of_elements = CalcNumOfElements(fsa, element_size);
    
    
    block = (char *)fsa + offset;
    for (i = 1; i < num_of_elements; ++i)
    {
        *((size_t *)(block)) = (i * new_element_size) + sizeof(fsa_t);
        block = MOVE(block, new_element_size);
    }
    
    *((size_t *)(block)) = 0xDEADBEEF;
    
    return fsa;
}


static size_t CalcNumOfElements(fsa_t *fsa, size_t user_element_size)
{
    size_t num_of_elements = 0;
    size_t element_size = 0;
    
    assert(NULL != fsa);
    
    element_size = CalcElemSize(user_element_size);
    
    num_of_elements = (fsa->total_size - sizeof(fsa_t)) / element_size;
    
    return num_of_elements;
}


static size_t CalcElemSize(size_t user_element_size)
{   
    size_t new_element_size = 0;
    
    if (0 == user_element_size % WORD_SIZE)
    {
        return user_element_size + WORD_SIZE;
    }
    
    new_element_size = user_element_size + (WORD_SIZE - 
                       (user_element_size % WORD_SIZE)) + POINTER_SIZE;
    
    return new_element_size;
}


void FSADestroy(fsa_t *fsa)
{
    (void)fsa;
}


void *FSAAlloc(fsa_t *fsa)
{
    void *block = NULL;
    
    assert(NULL != fsa);
    
    ret_offset = fsa->offset;
    if (0xDEADBEEF == ret_offset)
    {
        return NULL;
    }
    
    block = MOVE(fsa, fsa->offset);
    
    SwapLocals(fsa, block);
    block = MOVE(block, WORD_SIZE);
    
    return (block);
}


static void SwapLocals(fsa_t *first, void *second)
{
    size_t temp = first->offset;
    
    assert(NULL != first);
    assert(NULL != second);
    
    first->offset = *(size_t *)second;
    *(size_t *)second = temp;
}

void FSAFree(void *element)
{
    fsa_t *fsa = NULL;
    void *block = NULL;
    
    assert(NULL != element);
    
    block = MOVE(element, -WORD_SIZE);
    
    fsa = (fsa_t *)MOVE(block, -(*(size_t *)block));

    SwapLocals(fsa, block);
}


size_t FSACountFree(fsa_t *fsa)
{
    int count = 1;
    void *block = NULL;
    
    assert(NULL != fsa);
    
    if (0xDEADBEEF == *(size_t *)fsa)
    {
        return 0;
    }
    
    block = MOVE(fsa, fsa->offset);
    
    while (0xDEADBEEF != *(size_t *)block)
    {
        ++count;
        block = MOVE(fsa, *(size_t*)block);
    }
    
    return count;
}


size_t FSASuggestedSize(size_t element_size, size_t number_of_elements)
{
    return (STRUCT_SIZE + (CalcElemSize(element_size) * number_of_elements));
}



