/***********************************
*                                  *
*   DS - VSA                       *
*   written by: Hadar Klein        *
*   date: 20.12.18                 *
*   reviewed by: Efrat Kimchi      *
*                                  *
***********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* abs, size_t */

#include "vsa.h"    /* API */
#include "utils.h"  /* utilities */

struct vsa
{
    long chunk_size;
#ifndef NDEBUG
    long magic;
#endif
};

const long MAGIC = 0x123456;
const size_t STRUCT_SIZE = sizeof(vsa_t);
static long VSACalcElemSizeIMP(long user_element_size);
static long VSACalcTotalSpaceIMP(long total_size);
static void *VSAInsertWithoutStructIMP(vsa_t *vsa, long needed_size);
static void *VSAInsertWithStructIMP(vsa_t *vsa, long needed_size);
static long VSADefragIMP(vsa_t *vsa);
static long VSAAlignBeginningTrimIMP(void *allocated);


vsa_t *VSAInit(long total_size, void *allocated)
{
    vsa_t *vsa = NULL;
    long new_total_space = 0;
    long beginning_trim = 0;

    assert(NULL != allocated);

    /* align beginning */
    beginning_trim = VSAAlignBeginningTrimIMP(allocated);
    allocated = MOVE(allocated, beginning_trim);

    /* calculate usuable total space */
    new_total_space = VSACalcTotalSpaceIMP(total_size - beginning_trim);
    
    /* end */
    vsa = MOVE(allocated, (new_total_space - STRUCT_SIZE));
    vsa->chunk_size = 0;
#ifndef NDEBUG
    vsa->magic = MAGIC;
#endif
    
    /* start */
    vsa = allocated;
    vsa->chunk_size = -1 * (new_total_space - 2 * (STRUCT_SIZE));
#ifndef NDEBUG
    vsa->magic = MAGIC;
#endif
    
    return vsa;
}


void VSADestroy(vsa_t *vsa)
{
    (void)vsa;
}


void *VSAAlloc(vsa_t *vsa, long size_of_element)
{
    assert(NULL != vsa);
    
    size_of_element = VSACalcElemSizeIMP(size_of_element);
    
    while(vsa->chunk_size != 0)
    {
        if (vsa->chunk_size < 0)
        {
            if (labs(vsa->chunk_size) >= size_of_element)
            {
                if (labs(vsa->chunk_size) > 
                    (long)(size_of_element + STRUCT_SIZE))
				{
               		return VSAInsertWithStructIMP(vsa, size_of_element + 
                                                  STRUCT_SIZE);
				}
            	return VSAInsertWithoutStructIMP(vsa, labs(vsa->chunk_size));  
            }
            else
            {
                if (labs(VSADefragIMP(vsa)) >= size_of_element)
                {
                    continue;
                }
            }
        }
        vsa = MOVE(vsa, (labs(vsa->chunk_size) + STRUCT_SIZE));
    }
    
    return NULL;
}


void VSAFree(void *element)
{
    vsa_t *block = NULL;
    
    assert(NULL != element);
    
    block = (vsa_t *)((char *)element - STRUCT_SIZE);
    
    assert(block->magic == MAGIC);
    assert(block->chunk_size >= 0);
    
#ifndef NDEBUG
    block->magic = 0;
#endif
    block->chunk_size *= -1;
}


long VSALargestChunkAvail(vsa_t *vsa)
{
    long pot_sum = 0;
    long sum = 0;
    
    assert(NULL != vsa);

    vsa_t *runner = vsa;
    
    while (runner->chunk_size != 0)
    {
        if (runner->chunk_size < 0)
        {
            pot_sum = VSADefragIMP(runner);
            if (pot_sum < sum)
            {
                sum = pot_sum;
                pot_sum = 0;
            }
        }
        runner = MOVE(runner, (labs(runner->chunk_size) + STRUCT_SIZE));
    }
    
    return labs(sum);
}


static long VSADefragIMP(vsa_t *vsa)
{
    vsa_t *runner = NULL;
    long free_space = 0;
    long i = 0;
    
    assert(NULL != vsa);
    
    runner = MOVE(vsa, (vsa->chunk_size - STRUCT_SIZE));
    
    while (runner->chunk_size < 0)
    {
        free_space = free_space + runner->chunk_size;
#ifndef NDEBUG
    runner->magic = 0;
#endif
        runner = MOVE(runner, (labs(runner->chunk_size) + STRUCT_SIZE));
        ++i;
    }
    vsa->chunk_size = vsa->chunk_size + free_space - (i * STRUCT_SIZE);
    
    return vsa->chunk_size;
}


static long VSACalcTotalSpaceIMP(long total_size)
{
    if (0 == total_size % WORD_SIZE)
    {
        return total_size;
    }
    
    return (total_size - (total_size % WORD_SIZE));
}


static long VSACalcElemSizeIMP(long user_element_size)
{   
    size_t new_element_size = 0;
    
    if (0 == user_element_size % WORD_SIZE)
    {
        return user_element_size;
    }
    
    new_element_size = user_element_size + (WORD_SIZE - 
                       (user_element_size % WORD_SIZE));
    
    return new_element_size;
}


static void *VSAInsertWithoutStructIMP(vsa_t *vsa, long needed_size)
{
    assert(NULL != vsa);
    
    vsa->chunk_size = needed_size; 
#ifndef NDEBUG
    vsa->magic = MAGIC;
#endif   
    
    return MOVE(vsa, STRUCT_SIZE);
}


static void *VSAInsertWithStructIMP(vsa_t *vsa, long needed_size)
{
    vsa_t *vsa_runner = NULL;
    long temp_chunk = 0;
    
    assert(NULL != vsa);
    
    temp_chunk = vsa->chunk_size;
    
    vsa_runner = MOVE(vsa, needed_size);
    vsa_runner->chunk_size = (temp_chunk + needed_size);
    
    vsa->chunk_size = needed_size - STRUCT_SIZE;
#ifndef NDEBUG
    vsa->magic = MAGIC;
    vsa_runner->magic = MAGIC;
#endif

    return MOVE(vsa, STRUCT_SIZE);
}


static long VSAAlignBeginningTrimIMP(void *allocated)
{
	return (size_t)allocated % WORD_SIZE;
}
