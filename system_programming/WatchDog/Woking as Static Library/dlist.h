#ifndef ILRD_DLIST_H
#define ILRD_DLIST_H


typedef struct dlist_node *dlist_iter_t;
typedef struct dlist dlist_t;

typedef int (*action_func_t)(void *node_data, void *param);
typedef int (*is_match_func_t)(const void *node_data, const void *match_data, 
             const void *param);


/*
* Create a doubly linked list with two terminators - head and tail.
* Return Value: a pointer to the created list, NULL if allocation failed
* Parameters  : -
* Input       : -
* Time Complexity: O(1)
*/
dlist_t *DListCreate(void);


/*
* Destroys the given doubly linked list
* Return Value: -
* Parameters  : dlist: a doubly linked list
* Input       : -
* Time Complexity: O(n)
*/
void DListDestroy(dlist_t *dlist);



/*
* Returns the first node in the given doubly linked list
* Return Value: an iterator for the doubly linked list
* Parameters  : dlist: a doubly linked list
* Input       : dlist cannot be NULL
* Time Complexity: O(1)
*/
dlist_iter_t DListBegin(const dlist_t *dlist);




/*
* Returns the end of the end of the given doubly linked list
* Return Value: an iterator for the doubly linked list
* Parameters  : dlist: a doubly linked list
* Input       : dlist cannot be NULL
* Time Complexity: O(1)
*/
dlist_iter_t DListEnd(const dlist_t *dlist);


/*
* Returns the next node in the doubly linked list
* Return Value: Returns the next node in the doubly linked list
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR in case of performing this action on the 
                end of the list
* Time Complexity: O(1)
*/
dlist_iter_t DListNext(const dlist_iter_t iter);


/*
* Returns the previous node in the doubly linked list
* Return Value: Returns the previous node in the doubly linked list
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR in case of performing this action on the
                beginning of the list
* Time Complexity: O(1)
*/
dlist_iter_t DListPrev(const dlist_iter_t iter);


/*
* Checks whether the doubly linked list is empty
* Return Value: 1 if the list is empty, 0 otherwise
* Parameters  : dlist: a doubly linked list
* Input       : dlist cannot be NULL
* Time Complexity: O(1)
*/
int DListIsEmpty(const dlist_t *dlist);


/*
* Counts the number of nodes in the list
* Return Value: Number of nodes
* Parameters  : dlist: a doubly linked list
* Input       : dlist cannot be NULL
* Time Complexity: O(n)
*/
size_t DListCount(const dlist_t *dlist);


/*
* Checks whether the two iterators received are the same iterator
* Return Value: 1 if the iterators are the same, 0 otherwise
* Parameters  : iter1: the first iterator
                iter2: the second iterator
* Input       : both iterators cannot be NULL
* Time Complexity: O(1)
*/
int DListIsSameIterator(dlist_iter_t iter1, dlist_iter_t iter2);


/*
* Inserts a node before the given iterator
* Return Value: the node that was inserted before the iterator, if allocation 
                failed, returns the end of the list
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR in case iterator is the previous node from
                the beginning of the list
* Time Complexity: O(1)
*/
dlist_iter_t DListInsertBefore(dlist_iter_t iter, const void *data,
                               dlist_t *dlist);


/*
* Inserts a node after the given iterator
* Return Value: the node that was inserted after the iterator, if allocation 
                failed, returns the end of the list
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
              : iterator cannot be the tail of the list in which the iterator 
                appears
* NOTE        : UNDEFINED BEHAVIOUR in case iterator is the end of the list
* Time Complexity: O(1)
*/
dlist_iter_t DListInsertAfter(dlist_iter_t iter, const void *data, 
                              dlist_t *dlist);


/*
* Erases the given node from doubly linked list
* Return Value: the next node after the given node
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR in case of given iterator being the previous
                node from the beginning or the end node of the list
* Time Complexity: O(1)
*/
dlist_iter_t DListErase(dlist_iter_t iter);


/*
* Retreives the data in the given node
* Return Value: a pointer to the data in the given node
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
*/
void *DListGetData(const dlist_iter_t iter);


/*
* Pushes a new node into the front of the doubly linked list
* Return Value: the pushed node, if allocation failed, returns the end of list
* Parameters  : dlist: a doubly linked list
                data: the data to be added in a new node
* Input       : dlist cannot be NULL
* Time Complexity: O(1)
*/
dlist_iter_t DListPushFront(dlist_t *dlist, const void *data);


/*
* Pushes a new node into the back of the doubly linked list
* Return Value: the pushed node, if allocation failed, returns the end of list
* Parameters  : dlist: a doubly linked list
                data: the data to be added in a new node
* Input       : dlist cannot be NULL
* Time Complexity: O(1)
*/
dlist_iter_t DListPushBack(dlist_t *dlist, const void *data);


/*
* Pops out the node from the beginning of the doubly linked list
* Return Value: - 
* Parameters  : dlist: a doubly linked list
* Input       : dlist cannot be NULL
*/
void DListPopFront(dlist_t *dlist);


/*
* Pops out the node from the end of the doubly linked list
* Return Value: - 
* Parameters  : dlist: a doubly linked list
* Input       : dlist cannot be NULL
* Time Complexity: O(1)
*/
void DListPopBack(dlist_t *dlist);


/*
* takes the nodes from src_start to src_end and places them in the same order 
* before the dest node on the second list
* Return Value: -
* Parameters  : dest: the node before which the nodes are inserted
                src_start: the beginning of the list of nodes to  move
                src_end: the end of the list of nodes to move
* Input       : dest, src_start, src_end cannot be NULL, src_start and src_end 
                cannot be the same iterator
* NOTE: if the src_start and src_end are not on the same list,
        UNDEFINDE BEHAVIOUR
* Time Complexity: O(n)
*/
void DListSpliceBefore(dlist_iter_t dest, dlist_iter_t src_start, 
                       dlist_iter_t src_end);


/*
* Runs the given action function on the data of each node in the list between 
* two given nodes
* Return Value: 0 if successful for each node in the list, 1 otherwise
* Parameters  : start: the beginning of the list of nodes to check
                end: the end of the list of nodes to check
                action_func: the function given to run on the data in the 
                             nodes with the given parameter
                param: the given parameter to run on the data with the 
                       action_func
* Input       : all inputs cannot be NULL
* Time Complexity: O(n)
*/
int DListForEach(dlist_iter_t start,
                 dlist_iter_t end, 
                 action_func_t action_func,
                 void *param);


/*
* Runs the given match function on the data of each node in the list between 
* two given nodes
* Return Value: 1 if a match was found, 0 otherwise
* Parameters  : start: the beginning of the list of nodes to check
                end: the end of the list of nodes to check
                match_func: the function given to run on the data in the
                            nodes with the given parameter
                param: the given parameter to run on the data with the 
                       match_func
* Input       : all inputs cannot be NULL
* Time Complexity: O(n)
*/
int DListFind(dlist_iter_t start,
              dlist_iter_t end, 
              is_match_func_t match_func, 
              const void *param,
              const void *match_data);


#endif
