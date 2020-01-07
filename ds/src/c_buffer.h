#ifndef ILRD_C_BUFFER_H
#define ILRD_C_BUFFER_H

#include <unistd.h> /* ssize_t */
typedef struct circular_buffer c_buffer_t;

/*
* Builds the circular buffer of size buffer_size
* Return Value: pointer to the circular buffer, NULL if allocation failed
* Parameters  : buffer_size : the maximum number of bytes held by the buffer
* Proper Input: size >0
* Time Complexity: O(1)
*/
c_buffer_t *CBufferCreate(size_t buffer_size);

/*
* Destroys the circular buffer
* Return Value: -
* Parameters  : cb: the circular buffer
* Time Complexity: O(1)
*/
void CBufferDestroy(c_buffer_t *cb);

/*
* Attempt to write the count bytes from input_buff to the buffer. 
* Return Value: returns the number of bytes written to the buffer from
* input_buff
* Parameters  : cb: the circular buffer that is written to
				element: the data to be added to the buffer
* Proper Input: buffer is not NULL, input_buff is not NULL
* error: returns -1 - capacity 100% and you attempt to write
		 (errno = ENOBUFS/EOVERFLOW)
* Time Complexity: O(n)
*/
ssize_t CBufferWrite(c_buffer_t *cb, const void *input_buff, size_t count);

/*
* Attempts to read count bytes from the buffer into the output stream out_buff
* Return Value: the number of bytes read from the buffer to stream
* Parameters  : cb: the circular buffer that is read from
				out_buff: pointer to output of the user
* Proper Input: cb is not NULL, Out_buff is not NULL
* error: returns -1- no data and you attempt to read (errno =  ENODATA)
* Time Complexity: O(n)
*/
ssize_t CBufferRead(c_buffer_t *cb, void *output_buff, size_t count);

/*
* Returns the total space allocated for the buffer
* Return Value: Returns the total bytes allocated for the buffer
* Parameters  : cb: the circular buffer
* Proper Input: 
* Time Complexity: O(n) 
*/
size_t CBufferCapacity(const c_buffer_t *cb);


/*
* Returns the number of free bytes currently available for input
* Return Value: number of available bytes
* Parameters  : cb: the circular buffer
* Proper Input: buffer is not NULL
* Time Complexity: O(1)
*/
size_t CBufferFreeSpace(const c_buffer_t *cb);


/*
* Checks whether the buffer is empty or not
* Return Value: 1 if empty, 0 otherwise
* Parameters  : cb: the circular buffer
* Proper Input: buffer is not NULL
* Time Complexity: O(1)
*/
int CBufferIsEmpty(const c_buffer_t *cb);


#endif   /* ILRD_DYNAMIC_VECTOR_H */
