#ifndef ILRD_QUEUE_H
#define ILRD_QUEUE_H

typedef struct queue queue_t;

/*
* Creates a queue and returns a pointer to it
* Return Value: a pointer to the queue if successful, NULL otherwise 
* Parameters  : - 
* Input       : - 
* Time Complexity: O(1)
*/
queue_t *QueueCreate();


/*
* Destroys the given queue
* Return Value: - 
* Parameters  : queue: a queue
* Input       : queue cannot be NULL
* Time Complexity: O(n)
*/
void QueueDestroy(queue_t *queue);


/*
* creates a new node and pushes it into the queue
* Return Value: 0 if successful, 1 otherwise
* Parameters  : queue: the queue
                data: the data to be pushed into the queue
* Input       : queue cannot be NULL
* Time Complexity: O(1)
*/
int QueueEnqueue(queue_t *queue, void *data);


/*
* removes the head of the queue
* Return Value: returns the data in the dequeued node
* Parameters  : queue: the queue
* Input       : queue cannot be NULL, cannot dequeue an empty queue
* Time Complexity: O(1)
*/
void *QueueDequeue(queue_t *queue);


/*
* Returns the number of nodes in the queue
* Return Value: the number of nodes
* Parameters  : queue: the queue
* Input       : queue cannot be NULL
* Time Complexity: O(n)
*/
size_t QueueSize(queue_t *queue);


/*
* Checks whether the queue is empty or not
* Return Value: 1 if the queue is empty, 0 otherwise
* Parameters  : queue: the queue
* Input       : queue cannot be NULL 
* Time Complexity: O(n)
*/
int QueueIsEmpty(queue_t *queue);


/*
* Returns the data from the head of the queue
* Return Value: the data in the head node
* Parameters  : queue: the queue
* Input       : queue cannot be NULL
* Time Complexity: O(1)
*/
void *QueuePeek(queue_t *queue);


/*
* Pushes the src queue into the end of the dest queue.
* The src queue is emptied but is not destroyed
* Return Value: - 
* Parameters  : dest_q: the queue to push into
                src_q : the queue to push
* Input       : both queues cannot be NULL
* Time Complexity: O(n)
*/
void QueueAppend(queue_t *to, queue_t *from);


#endif
