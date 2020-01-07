#ifndef ILRD_SL_LIST_H
#define ILRD_SL_LIST_H

typedef int (*is_match_func_t)(const void *data, const void *param);
typedef int (*action_func_t)(const void *data, const void *param);
typedef struct sll_node sll_node_t;

struct sll_node
{
	void *data;
	sll_node_t *next;
};


/*
* Builds the node with a pointer to the data and next node received 
* Return Value: pointer to the node, NULL if allocation failure
* Parameters  : data: pointer to the data the node is to hold
				node: the next node in the list the created node points to
* Input       : - 
* Time Complexity: O(1)
*/
sll_node_t *SLListCreateNode(void *data, sll_node_t *next);


/*
* Destroys the node and all subsequent nodes in the list
* Return Value: -
* Parameters  : node: pointer to the node to be destroyed and all its subsequent
					  nodes
* Input       : -
* Time Complexity: O(n)
*/
void SLListDestroyList(sll_node_t *node);


/*
* Inserts the new_node after the where node
* Return Value: returns a pointer to the new node that was inserted
* Parameters  : where: the node that the insert occurs after it
				new_node: the node to be inserted
* Input       : where and new_node cannot be NULL
* Time Complexity: O(1)
*/
sll_node_t *SLListInsertAfter(sll_node_t *where, sll_node_t *new_node);

/*
* Inserts the new_node before the where node
* Return Value: returns a pointer to the new_node that was inserted. On failure,
				returns a pointer to the original node.
* Parameters  : where: the node that the insert occurs after it it
				new_node: the node to be inserted
* Input       : where and new_node cannot be NULL
* Time Complexity: O(1)
*/
sll_node_t *SLListInsert(sll_node_t *where, sll_node_t *new_node);

/*
* Removes the node after the where node
* Return Value: returns a pointer to the node that was removed
* Parameters  : where: the node 
* Input       : -
* NOTE: free the node that was removed
* Time Complexity: O(1)
*/
sll_node_t *SLListRemoveAfter(sll_node_t *where);

/*
* Removes the where node
* Return Value: returns a pointer to the node that was removed
* Parameters  : where: the node
* Input       : -
* NOTE: free the node that was removed
* Time Complexity: O(1)
*/
sll_node_t *SLListRemove(sll_node_t *where);

/*
* Iterates over the linked list from the given node head, performs the match 
* function on the given parameter until it reaches a node with a matching 
* parameter. 
* Return Value: pointer to a node with a matching parameter
* Parameters  : head: the starting node
				match_func: a matching function
				param: parameter to match using the matching function
* Input       : head not NULL, param not NULL
* NOTE: match_func: int (*is_match_func_t)(const void *data, const void *param)
* NOTE: the last node in the linked list cannot be removed with this function
* Time Complexity: O(n)
*/
sll_node_t *SLListFind(const sll_node_t *head, is_match_func_t match_func, 
					   const void *param);

/*
* Iterates over the linked list from the given node head and performs the action
* of action_func with parameter param
* Return Value: 0 if successful for all nodes in the list, 1 otherwise
* Parameters  : head: the starting node
				action_func: a matching function
				param: parameter to match using the matching function
* Input       : head not NULL, param not NULL
* NOTE: action_func: int (*action_func_t)(const void *data, const void *param)
* Time Complexity: O(n)
*/
int SLListForEach(sll_node_t *head, action_func_t action_func, void *param);

/*
* Counts the number of nodes from the given head node until the end of the list
* Return Value: number of nodes
* Parameters  : head: the given node to start counting from
* Input       : head is not NULL
* Time Complexity: O(n)
* NOTE: There may be intersections of other linked lists. The nodes in the 
* second linked list (other than the intersection) are not counted.
*/
size_t SLListCount(const sll_node_t *head);

/*
* Flips the order of the linked list
* Return Value: a pointer to the new head node
* Parameters  : head: the given head node, from there start flipping the order
* Input       : head is not NULL
* Time Complexity: O(n)
*/
sll_node_t *SLListFlip(sll_node_t *head);
sll_node_t *SLListFlipRecursive(sll_node_t *head);


/*
* Checks whether the given head node is part of a looped linked list
* Return Value: 1 if part of loop, 0 otherwise
* Parameters  : head: the given head node
* Input       : head is not NULL
* Time Complexity: O(n)
*/
int SLListHasLoop(const sll_node_t *head);

/*
* Finds the intersection between two linked lists
* Return Value: returns a pointer to the node at the intersection of two linked 
* lists
* Parameters  : head1: the head node in the first linked list
				head2: the head node in the second linked list 
* Input       : head1 is not NULL, head2 is not null
* Time Complexity: O(n)
*/
sll_node_t *SLListFindIntersection(const sll_node_t *head1, 
								   const sll_node_t *head2);


#endif
