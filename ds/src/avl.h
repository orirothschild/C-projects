/* RC9 */

#ifndef ILRD_AVL_H
#define ILRD_AVL_H

#include "dlist.h"

typedef int (*avl_cmp_func_t)(const void *user_data, const void *node_data,
                              void *param);
typedef int (*avl_action_func_t)(void *user_data, void *param);



typedef struct avl_tree avl_t;
/* typedef struct avl_node *avl_node_t; */
/* 
struct avl_node
{
    avl_node_t kids[2]
    void *data;
    int height;
}
 */

/*
struct avl_tree
{
    avl_node_t root;
    cmp_func_t user_cmp_func;
    void *cmp_func_param;
}
*/


/*AVLCreate
* Creates a new AVL Tree
* Return Value: pointer to the AVL tree, NULL if there was an allocation problem
* Parameters  : compare_func: a function to use for comparison between data in 
                the nodes of the tree
* Input       : compare_func cannot be NULL
                compare_func parameters: const void *user_data, 
                                         const void *node_data,
                                         void *param
* Time Complexity: O(1)
*/
avl_t *AVLCreate(avl_cmp_func_t compare_func, void *cmp_func_param);


/*AVLDestroy
* Destroys the given AVL
* Return Value: -
* Parameters  : avl: an avl tree
* Input       : avl cannot be NULL
* Time Complexity: O(n)
* order       : post-order
*/
void AVLDestroy(avl_t *avl);


/*AVLInsert
* Inserts new data into the tree
* Return Value: 0 if successful, 1 otherwise
* Parameters  : avl: an avl
                data: the data from the user
* Input       : avl cannot be NULL
* Time Complexity: O(log n)
*/
int AVLInsert(avl_t *avl, const void *data);


/*AVLRemove
* Removes the given tree
* Return Value: returns the data removed from the tree
* Parameters  : avl: an avl tree
                data: data from the user
* Input       : avl cannot be NULL
* Time Complexity: O(log n)
*/
void *AVLRemove(avl_t *avl, const void *key);


/*AVLFind
* Searches for a given value in the given avl tree
* Return Value: returns a pointer to the data searched for, or NULL
* Parameters  : avl: an avl
                user_data: the data from the user
* Input       : both parameters cannot be NULL
* Time Complexity: O(log n)
*/
void *AVLFind(const avl_t *avl, const void *key);


/*AVLForEach
* Performs the action in action_func on the avl tree 
* Return Value: 0 if the function was applied to the entire tree, 1 otherwise.
* Parameters  : tree: an avl tree
                action_func: a user provided action function. This function
                cannot alter the data in the treeator
                action_func parameters: (void *user_data, void *param
* Input       : tree, action_func cannot be NULL
* order       : in-order
* Time Complexity: O(n)
*/
int AVLForEach(avl_t *avl, avl_action_func_t action_func,
               void *action_func_param);


/*AVLIsEmpty
* Checks whether the avl tree is empty or not
* Return Value: 1 if the tree is empty, 0 otherwise
* Parameters  : avl: an avl tree
* Input       : avl cannot be NULL
* Time Complexity: O(1)
*/
int AVLIsEmpty(const avl_t *avl);


/*AVLSize
* Counts the number of data points in the tree
* Return Value: the size of the tree
* Parameters  : avl: an avl tree
* Input       : avl cannot be NULL
* order       : pre-order
* Time Complexity: O(n)
*/
size_t AVLSize(const avl_t *avl);


/*AVLHeight
* Finds the height of the tree
* Return Value: the height of the tree
* Parameters  : avl: an avl tree
* Input       : avl cannot be NULL
* Time Complexity: O(1)
*/
int AVLHeight(const avl_t *avl);


/*AVLMultiFind
* Finds all the data points that return true when using the multi_cmp_func in a
  doubly-linked list
* Return Value: 0 if found data points, 1 otherwise
* Parameters  : avl: an avl tree
                multi_cmp_func: a comparison function given by the user
                dlist: a doubly-linked list, given by the user.
* Input       : avl cannot be NULL
                multi_cmp_func cannot be NULL
                multi_cmp_func parameters: const void *user_data, 
                                            const void *node_data,
                                            void *param
                dlist cannot be NULL

* Time Complexity: O(n)
*/
int AVLMultiFind(const avl_t *avl, avl_cmp_func_t multi_cmp_func, void *data,
                 void *multi_cmp_param, dlist_t *dlist);


/*AVLMultiRemove
* Finds all the data points that return true when using the multi_cmp_func in a 
  doubly-linked list and removes these data points from the avl tree
* Return Value: 0 if any data points were removed, 1 otherwise
* Parameters  : avl: an avl tree
                multi_cmp_func: a comparison function given by the user
                dlist: a doubly-linked list, given by the user.
* Input       : avl cannot be NULL
                multi_cmp_func cannot be NULL
                multi_cmp_func parameters: const void *user_data, 
                                            const void *node_data,
                                            void *param
                dlist cannot be NULL
* Time Complexity: O(n logn)
*/
int AVLMultiRemove(avl_t *avl, avl_cmp_func_t multi_cmp_func, void *data,
                   void *multi_cmp_param, dlist_t *dlist);



void PrintTree(avl_t *avl);

#endif /* ILRD_AVL_H */
