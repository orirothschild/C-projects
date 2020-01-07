#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* memmove */
#include <stdlib.h> /* malloc */
#include "dv.h" /* ADT */

struct dynamic_vector
{
	void *base;
	size_t elem_size;
	size_t num_of_elems;
	size_t capacity;
};

enum {SUCCESS, FAILURE};

vector_t *DVectorCreate(size_t num_of_elements, size_t element_size)
{
	vector_t *dv = NULL;
	
	dv = (void *)malloc(sizeof(vector_t));
	if (NULL == dv)
	{
		return (NULL);
	}

	dv->base = (void *)malloc(num_of_elements * element_size);
	if (NULL == dv->base)
	{
		free(dv);
		
		return (NULL);
	}
	
	dv->elem_size = element_size;
	dv->num_of_elems = 0;
	dv->capacity = num_of_elements;
	
	return(dv);
}


void DVectorDestroy(vector_t *dv)
{
	if (NULL != dv)
	{
		free(dv->base);
	}
	
	free(dv);
}


size_t DVectorSize(const vector_t *dv)
{
	assert(NULL != dv);
	
	return(dv->num_of_elems);
}


size_t DVectorCapacity(const vector_t *dv)
{
	assert(NULL != dv);
	
	return(dv->capacity);
}


int DVectorPush(vector_t *dv, const void *element)
{
	void *temp = NULL;
	
	assert(NULL != dv);
	assert(NULL != element);
	
	if (dv->num_of_elems >= (dv->capacity))
	{
		temp = realloc(dv->base, (dv->capacity * dv->elem_size) * 2);
		if (NULL == temp)
		{
			return (FAILURE);
		}
		dv->base = temp;
		dv->capacity *= 2;
	}
	
	memmove(((char *)dv->base + (dv->num_of_elems * dv->elem_size)),
			 element, dv->elem_size);
	
	++(dv->num_of_elems);
	
	return (SUCCESS);
}


int DVectorPop(vector_t *dv)
{
	void *temp = NULL;
	
	assert(NULL != dv);
	assert(0 != dv->num_of_elems);
	
	if (dv->num_of_elems - 1 <= (dv->capacity / 4))
	{
		temp = realloc(dv->base, (dv->capacity * dv->elem_size) / 2);
		if (NULL == temp)
		{
			return (FAILURE);
		}
		dv->base = temp;
		dv->capacity /= 2;
	}
	
	--(dv->num_of_elems);
	
	
	return (SUCCESS);
}


int DVectorReserve(vector_t *dv, size_t res_size)
{
	void *temp = NULL;
	assert(NULL != dv);
	
	if(res_size < dv->num_of_elems)
	{
		res_size = dv->num_of_elems;
	}
	
	temp = realloc(dv->base, (dv->elem_size * res_size));
	if (NULL == temp)
	{
		return (FAILURE);
	}
	dv->base = temp;
	dv->capacity = res_size;
	
	return (SUCCESS);
}


void *DVectorGetItemAddress(vector_t *dv, size_t idx)
{
	assert(NULL != dv);
	assert(idx <= dv->num_of_elems);
	
	return ((char *)dv->base + (idx * dv->elem_size));
}

