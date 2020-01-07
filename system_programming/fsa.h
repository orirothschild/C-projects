#ifndef ILRD_FSA_H
#define ILRD_FSA_H

typedef struct fsa fsa_t;

/*
* Create an allocator from the total allocated memory given. 
* Each individual memory block is at least 8 bytes wide.
* Return Value: a pointer to the allocator
* Parameters  :element_size: the requested size of each individual memory block
               total_size: the size of the entire memory given
               allocated: the entire memory section given
* Input       : allocated cannot be NULL
* Time Complexity: O(1)
*/
fsa_t *FSACreate(size_t element_size, size_t total_size, void *allocated);

/*
* (Nothing for now)
* Return Value: -
* Parameters  : -
* Input       : - 
*/
void FSADestroy(fsa_t *fsa);

/*
* Allocates a single fixed size memory block.
* Return Value: a pointer to the single memory block
* Parameters  : fsa: the allocator
* Input       : fsa cannot be NULL
* Time Complexity: O(1);
* NOTE: cannot fail
*/
void *FSAAlloc(fsa_t *fsa);

/*
* Frees the given memory block (element)
* Return Value: - 
* Parameters  : element: a memory block
* Input       : element cannot be NULL, user may only send pointers 
*               received from FSAAlloc().
* Time Complexity: O(1)
* NOTE: cannot fail
*/
void FSAFree(void *element);

/*
* Counts the number of individual fixed-size blocks left free in the allocator
* Return Value: the number of free memory blocks
* Parameters  : fsa: the allocator
* Input       : fsa cannot be NULL
* Time Complexity: O(n)
*/
size_t FSACountFree(fsa_t *fsa);

/*
* Calculates the suggested size to allocate memory given the number of 
* elements and their size
* Return Value: a size suggested to allocate for the total memory area
* Parameters  : element_size: the size of each memory block
                number_of_elements: the number of elements requested
* Input       : -
Time Complexity: O(1);
*/
size_t FSASuggestedSize(size_t element_size, size_t number_of_elements);


#endif   /* ILRD_FSA_H */
