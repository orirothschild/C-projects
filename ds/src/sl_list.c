/***********************************
*                                  *
*   DS - Single Linked List        *
*   written by: Hadar Klein        *
*   reviewed by: Ellad Barkay      *
*                                  *
***********************************/

#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "sl_list.h"


enum {NOT_FOUND, FOUND};
enum {False, True};
enum {PASS, FAIL};

sll_node_t *SLListCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *node = (sll_node_t *)malloc(sizeof(sll_node_t));
	if (NULL == node)
	{
		return (NULL);
	}

	node->data = data;
	node->next = next;

	return (node);
}


void SLListDestroyList(sll_node_t *node)
{
	sll_node_t *next = NULL;
	
	while (NULL != node)
	{
		next = node->next;
		node->data = NULL;
		free(node);
		node = next;
	}
}


sll_node_t *SLListInsertAfter(sll_node_t *where, sll_node_t *new_node)
{
	assert(NULL != where);
	assert(NULL != new_node);
	
	new_node->next = where->next;
	where->next = new_node;
	
	return (where->next);
}


sll_node_t *SLListInsert(sll_node_t *where, sll_node_t *new_node)
{
	void *temp_data = NULL;

	assert(NULL != where);
	assert(NULL != new_node);
	assert(NULL == new_node->next);

	temp_data = where->data;
	where->data = new_node->data;
	new_node->next = where->next;
	where->next = new_node;
	new_node->data = temp_data;

	return (where);
}


sll_node_t *SLListRemoveAfter(sll_node_t *where)
{
	sll_node_t *removed_node = NULL;
	
	assert(NULL != where);
	assert(NULL != where->next);
	
	removed_node = where->next;
	where->next = removed_node->next;	
	
	return (removed_node);
}


sll_node_t *SLListRemove(sll_node_t *where)
{
	sll_node_t *removed_node = NULL;
	void *temp_data = NULL;
	
	assert(NULL != where);
	assert(NULL != where->next);
	
	/* hold the removed node in new pointer */
	removed_node = where->next;
	removed_node->next = NULL;
	
	/* hold the data from removed_node temporarily */
	temp_data = removed_node->data;
	
	/* copy the data from the node we want to remove to the node we 
	actually remove */
	removed_node->data = where->data;
	
	/* the data in the node that is left gets the data from the node after 
	where */
	where->data = temp_data;
	
	/* remove the following node */
	SLListRemoveAfter(where);
	
	return (removed_node);
}


sll_node_t *SLListFind(const sll_node_t *head, is_match_func_t match_func, 
					   const void *param)
{
	const sll_node_t *curr_node = head;
	const sll_node_t *prev_node = head;
	int result = NOT_FOUND;
	
	do
	{
		result = match_func(curr_node->data, param);
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	while (NULL != curr_node && result == NOT_FOUND);
	
	if (NULL == curr_node)
	{
		return (NULL);
	}
	
	return (sll_node_t *)prev_node;
}


int SLListForEach(sll_node_t *head, action_func_t action_func, void *param)
{
	const sll_node_t *curr_node = head;
	int result = PASS;

	assert(NULL != head);
	assert(NULL != param);
	
	do
	{
		result = action_func(curr_node->data, param);
		curr_node = curr_node->next;
	}
	while (NULL != curr_node && result == PASS);
	
	
	return (result);
}


size_t SLListCount(const sll_node_t *head)
{
	sll_node_t *runner = (sll_node_t *)head;
	int counter = 0;
	
	assert(NULL != head);
	
	do
	{
		++counter;
		runner = runner->next;
	}
	while (NULL != runner);
	
	return (counter);
}


sll_node_t *SLListFlip(sll_node_t *curr_node)
{
	sll_node_t *next = curr_node;
	sll_node_t *prev = NULL;
	
	assert(NULL != curr_node);
	
    while (NULL != next)
	{
		next = next->next;
		curr_node->next = prev;
		prev = curr_node;
		curr_node = next;
	}
		
	return (prev);
}

sll_node_t *SLListFlipRecursive(sll_node_t *head)
{
	sll_node_t *rev_head = NULL;
	if (NULL == head || NULL == head->next)
	{
		return head;
	}

	rev_head = SLListFlipRecursive(head->next);
	head->next->next = head;
	head->next = NULL;

	return rev_head;
}


int SLListHasLoop(const sll_node_t *head)
{
	sll_node_t *walker = NULL;
	sll_node_t *runner = NULL;
	
	assert(NULL != head);
	assert(NULL != head->next);	

	walker = (sll_node_t *)head;
	runner = (sll_node_t *)head->next;

	while(NULL != walker && NULL != runner->next && walker != runner)
	{
		walker = walker->next;
		runner = runner->next->next;
	}
	
	return (runner == walker);
}


sll_node_t *SLListFindIntersection(const sll_node_t *head1, 
                                   const sll_node_t *head2)
{
	const sll_node_t *curr1 = NULL;
	const sll_node_t *curr2 = NULL;
	size_t len1 = SLListCount(head1);
	size_t len2 = SLListCount(head2);
	size_t diff = 0;
	size_t max = 0;
	size_t min = 0;
	size_t i = 0;

	if (len1 > len2)
	{
		max = len1;
		min = len2;
		curr1 = head1;
		curr2 = head2;
	}
	else
	{
		max = len2;
		min = len1;
		curr1 = head2;
		curr2 = head1;
	}
	
	diff = max - min;
	
	for (i = 0; i < diff; ++i)
	{
		curr1 = curr1->next;
	}
	
	if (curr1 == curr2)
	{
	    return NULL;
	}
	
	while (NULL != curr1 && NULL != curr2 && curr1 != curr2)
	{
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
	
	return ((sll_node_t *)curr1);	
}

