#ifndef ILRD_VSA_H
#define ILRD_VSA_H
/*RC5*/

typedef struct vsa vsa_t;
/*
struct vsa
{
    long chunk_size;
#ifndef NDEBUG
    long magic;
#endif
};
*/


/*
* 
* Return Value: returns a pointer to the struct.
* Parameters  : total_size in BYTEs and pointer to allocated memory
* Input       : The min size of total size must be 5 WORD_SIZE
*			  : allocated must not be NULL
* complexity: O(1)
*/
vsa_t *VSAInit(long total_size, void *allocated);

/*
* 
* Return Value: /
* Parameters  : /
* Input       : /
*/
void VSADestroy(vsa_t *vsa);

/*
* 
* Return Value: allocates a block of memory to the user
* Parameters  : pointer to vsa struct, size_of_element requested
* Input       : vsa cannot be null
* complexity: O(n)
*/
void *VSAAlloc(vsa_t *vsa, long size_of_element);

/*
* 
* Return Value: recives a block of memory from the user to be freed.inserts it 
to the freelist
* Parameters  : pointer to the element
* Input       : element cannot be null
* complexity: O(1)
*/
void VSAFree(void *element);

/*
* 
* Return Value: returns the size of the largest free chunk available.
* Parameters  : pointer to vsa struct 
* Input       :vsa cannot be null
* complexity: O(n)
*/
long VSALargestChunkAvail(vsa_t *vsa);

#endif   /* ILRD_VSA_H */
