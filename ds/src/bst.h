#ifndef ILRD_BST_H
#define ILRD_BST_H

typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t;

typedef int (*cmp_func_t)(const void *user_data, const void *node_data,
                          void *param);
typedef int (*action_func_t)(void *user_data, void *param);

/*
* Creates a new Binary Search Tree
* Return Value: a pointer to the BST, NULL if there was an allocation problem
* Parameters  : compare_func: a function to use for comparison between iterators
* Input       : compare_func cannot be NULL
* Time Complexity: O(1)
*/
bst_t *BSTCreate(cmp_func_t compare_func, void * param);


/*
* Destroys the given BST
* Return Value: -
* Parameters  : bst: a bst
* Input       : bst cannot be NULL
* Time Complexity: O(n)
*/
void BSTDestroy(bst_t *bst);


/*
* Retuns a pointer to the beginning leaf in the tree
* Return Value: a pointer to the first iterator
* Parameters  : bst: a bst
* Input       : bst cannot be NULL
* Time Complexity: O(log n)
*/
bst_iter_t BSTBegin(const bst_t *bst);


/*
* Returns a pointer to the end of the tree, used for exclusive looping
* Return Value: a pointer to the end of the tree
* Parameters  : bst: a bst
* Input       : bst cannot be NULL
* Undefined Behavior: using BSTGetData() on the returned value
* Time Complexity: O(1)
*/
bst_iter_t BSTEnd(const bst_t *bst);

/*
* Returns a pointer to the next iterator in the tree
* Return Value: a pointer to the next iterator
* Parameters  : iter: an iterator
* Input       : iter cannot be NULL
* Undefined Behavior: using BSTNext() on the returned value of BSTEnd()
* Time Complexity: O(log n)
*/
bst_iter_t BSTNext(bst_iter_t iter);


/*
* Returns a pointer to the previous iterator in the tree
* Return Value: a pointer 
* Parameters  : iter: an iterator 
* Input       : iter cannot be NULL
* Undefined Behavior: using BSTPrev() on the returned value of BSTBegin()
* Time Complexity: O(log n)
*/
bst_iter_t BSTPrev(bst_iter_t iter);


/*
* Returns an iterator to the inserted data in the tree 
* Return Value: returns a pointer to the inserted data, NULL otherwise
* Parameters  : bst: a bst
                data: the data from the user
* Input       : bst cannot be NULL
* Time Complexity: O(log n)
*/
bst_iter_t BSTInsert(bst_t *bst, const void *data);


/*
* Removes the given iterator
* Return Value: returns a pointer to the next iterator
* Parameters  : iter: an iterator
* Input       : iter cannot be NULL
* Time Complexity: O(1)
*/
bst_iter_t BSTRemove(bst_iter_t iter);


/*
* Returns the data in the given iterator
* Return Value: a pointer to the given iterator's data
* Parameters  : iter: an iterator
* Input       : iter cannot be null
* Time Complexity: O(1)
*/
void *BSTGetData(const bst_iter_t iter);


/*
* Searches for a given value in the given tree
* Return Value: a pointer to the found iterator or BSTEnd() otherwise
* Parameters  : bst: a bst
                user_data: the data from the user
* Input       : both parameters cannot be NULL
* Time Complexity: O(log n)
*/
bst_iter_t BSTFindNode(const bst_t *bst, const void *user_data);


/*
* Performs the action in action_func on all the iterators between from and to
* Return Value: 0 if the function was applied to every iterator, 1 otherwise.
* Parameters  : from: the beginning iterator
                to: the last iterator
                action_func: a user provided action function. This function
                cannot alter the data in the iterator
* Input       : from, to and the action_func cannot be NULL
* Time Complexity: O(n)
*/
int BSTForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func,
                    void *param);


/*
* Checks whether the bst is empty or not
* Return Value: 1 if the tree is empty, 0 otherwise
* Parameters  : bst: a bst
* Input       :bst cannot be NULL
* Time Complexity: O(1)
*/
int BSTIsEmpty(const bst_t *bst);


/*
* Counts the number of iterators in the bst
* Return Value: the size of the bst
* Parameters  : bst: a bst
* Input       : bst cannot be NULL
* Time Complexity: O(n)
*/
size_t BSTSize(const bst_t *bst);


/*
* Checks whether two given iterators are the same iterator
* Return Value: 1 if they are the same, 0 otherwise
* Parameters  : iter1: an iterator
                iter2: an iterator
* Input       : both parameters cannot be NULL
* Time Complexity: O(1)
*/
int BSTIsSameIterator(const bst_iter_t iter1, const bst_iter_t iter2);


#endif /* ILRD_BST_H */
