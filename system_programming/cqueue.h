/* RC2 */
#ifndef ILRD_MULTICQUEUE_H
#define ILRD_MULTICQUEUE_H

typedef struct cqueue cqueue_t;

/* typedef struct cqueue
{
    size_t num_of_elements_in_q;
    size_t first_element_idx;
    int cqueue[size];
}cqueue_t; */


/*
* Builds a new circular queue
* Return Value: 
* Parameters  : 
* Input       : 
*/
cqueue_t *CQueueCreate();


/*
* Destroys the circular queue
* Return Value: 
* Parameters  : 
* Input       : 
*/
void CQueueDestroy(cqueue_t *cqueue);


/*
* enqueues the data
* Return Value: returns 0 if enqueued, 1 otherwise
* Parameters  : 
* Input       : 
*/
int CQueueEnqueue(cqueue_t *cqueue, int data);

/*
* dequeues the data at the head of the queue
* Return Value: returns the data
* Parameters  : 
* Input       : 
*/
int CQueueDequeue(cqueue_t *cqueue);



/*
* checks whether the queue is empty
* Return Value: 
* Parameters  : 
* Input       : 
*/
int CQueueIsEmpty(cqueue_t *cqueue);


void PrintQueue(cqueue_t *cqueue);

#endif
