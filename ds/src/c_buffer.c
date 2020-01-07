/******************************
*							  *
*	DS - Circular Buffer 	  *
*   written by: Hadar Klein	  *
* reviewed by: Ori Rothschild *
*							  *
******************************/

#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <errno.h>  /* errno */
#include <unistd.h> /* ssize_t */

#include "c_buffer.h" /* ADT */

#define BASE (char *)cb->base

struct circular_buffer
{
	size_t capacity;
	size_t free_space;
	size_t write_index;
	size_t read_index;
	char base[1];
};

enum {False, True};

const int FLEXIBLE_OFFSET = 1;
const size_t BYTE = 1;


c_buffer_t *CBufferCreate(size_t buffer_size)
{
	c_buffer_t *cb = NULL;
	void *temp = NULL;
	
	temp = (void *)malloc(sizeof(c_buffer_t) + buffer_size - FLEXIBLE_OFFSET);
	if (NULL == temp)
	{
		return (NULL);
	}

	cb = temp;
	cb->write_index = 0;
	cb->read_index = 0;
	cb->capacity = buffer_size;
	cb->free_space = buffer_size;
	
	return(cb);
}


void CBufferDestroy(c_buffer_t *cb)
{
	cb->capacity = 0;
	cb->free_space = 0;
	cb->write_index = 0;
	cb->read_index = 0;
	
	free(cb);
}


size_t CBufferFreeSpace(const c_buffer_t *cb)
{
	assert(NULL != cb);
	
	return(cb->free_space);
}


size_t CBufferCapacity(const c_buffer_t *cb)
{
	assert(NULL != cb);
	
	return(cb->capacity);
}


int CBufferIsEmpty(const c_buffer_t *cb)
{
	assert(NULL != cb);
	
	if(cb->capacity == cb->free_space)
	{
		return (True);
	}
	
	return (False);
}


ssize_t CBufferWrite(c_buffer_t *cb, const void *input_buff, size_t count)
{
	size_t writes = 0;
	size_t outro = 0;
	size_t intro = 0;
	
	assert(NULL != cb);
	assert(NULL != input_buff);
	
	if (0 == cb->free_space)
	{
		errno = ENOBUFS;
		return (-1);
	}
	
	writes = cb->free_space < count ? cb->free_space : count;
	
	if (writes > (cb->capacity - cb->write_index))
	{
		outro = cb->capacity - cb->write_index;
		intro = writes - outro;
		
		memcpy(BASE + cb->write_index, input_buff, outro);
		input_buff = (char *)input_buff + outro;
		cb->write_index = 0;
		memcpy(BASE + cb->write_index, input_buff, intro);
		cb->write_index += intro;
	}
	else
	{
		memcpy(BASE + cb->write_index, input_buff, writes);
		cb->write_index += writes;
	}
	
	cb->free_space -= writes;
	
	return ((ssize_t)writes);
}


ssize_t CBufferRead(c_buffer_t *cb, void *output_buff, size_t count)
{
	size_t reads = 0;
	size_t outro = 0;
	size_t intro = 0;
	size_t read_space = cb->capacity - cb->free_space;
		
	assert(NULL != cb);
	assert(NULL != output_buff);
	
	if (cb->capacity == cb->free_space)
	{
		errno = ENODATA;
		return (-1);
	}
	
	reads = read_space < count ? read_space : count;

	if (reads > (cb->capacity - cb->read_index))
	{
		outro = cb->capacity - cb->read_index;
		intro = reads - outro;
		
		memcpy(output_buff, BASE + cb->read_index, outro);
		output_buff = (char *)output_buff + outro;
		cb->read_index = 0;
		memcpy(output_buff, BASE + cb->read_index, intro);
		cb->read_index += intro;
	}
	else
	{
		memcpy(output_buff, BASE + cb->read_index, reads);
		cb->read_index += reads;
	}
	
	cb->free_space += reads;
	
	return ((ssize_t)reads);
}


