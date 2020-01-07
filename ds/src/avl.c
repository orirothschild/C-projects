/***********************************
*                                  *
*   DS - AVL Tree                  *
*   written by: Hadar Klein        *
*   date: 10.1.19                  *
*   reviewed by: Ellad Barkay      *
*                                  *
***********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "avl.h"    /*  API   */
#include "utils.h"  /* utils  */

enum {BALANCED = 1, UNBALANCED = 2};

enum direction {LEFT, RIGHT};

typedef struct avl_node *avl_node_t;

typedef avl_node_t (*remove_node_func_t)(avl_node_t root);

struct avl_node
{
    avl_node_t kids[2];
    void *data;
    int height;
};

struct avl_tree
{
    avl_node_t root;
    avl_cmp_func_t user_cmp_func;
    void *cmp_func_param;
};

enum
{
    NO_KIDS,
    ONE_KID,
    TWO_KIDS,
    num_of_kids
};

remove_node_func_t remove_func_table[num_of_kids] = {0};


static void AVLUpdateHeightIMP(avl_node_t root)
{
    int left_height = 0;
    int right_height = 0;

    assert(NULL != root);

    left_height = NULL != root->kids[LEFT] ? root->kids[LEFT]->height : -1;
    right_height = NULL != root->kids[RIGHT] ? root->kids[RIGHT]->height : -1;
    root->height = MAX(left_height, right_height) + 1;
}


static enum direction AVLGetChildSide(avl_node_t root)
{
    assert(NULL != root);

    return root->kids[LEFT] == NULL ? RIGHT : LEFT;
}


static int AVLGetNumOfKidsIMP(avl_node_t root)
{
    assert(NULL != root);

    return !!(root->kids[LEFT]) + !!(root->kids[RIGHT]);
}


static avl_node_t AVLGetRootIMP(const avl_t *tree)
{
    assert(NULL != tree);

    return tree->root;
}


static void *AVLGetDataIMP(avl_node_t root)
{
    assert(NULL != root);

    return root->data;
}


static avl_node_t AVLRotateIMP(enum direction side, avl_node_t root)
{
    avl_node_t new_root = NULL;
    avl_node_t old_child = NULL;
    
    assert(NULL != root);
    assert(LEFT == side || RIGHT == side);

    new_root = root->kids[side];
    old_child = new_root->kids[!side];

    new_root->kids[!side] = root;

    root->kids[side] = old_child;

    AVLUpdateHeightIMP(root);

    return new_root;
}


static avl_node_t AVLPerformBalanceIMP(enum direction side1, 
                                       enum direction side2,
                                       avl_node_t root)
{
    avl_node_t new_root = NULL;

    assert(NULL != root);
    assert(LEFT == side1 || RIGHT == side1);
    assert(LEFT == side2 || RIGHT == side2);

    if (side1 != side2)
    {
        new_root = AVLRotateIMP(side2, root->kids[side1]);
        root->kids[side1] = new_root;
    }

    new_root = AVLRotateIMP(side1, root);

    return new_root;
}


static int AVLGetHeightDiffIMP(avl_node_t root)
{
    int left_height = -1;
    int right_height = -1;
    int diff = 0;

    assert(NULL != root);

    left_height = NULL == root->kids[LEFT] ? -1 : root->kids[LEFT]->height;
    right_height = NULL == root->kids[RIGHT] ? -1 : root->kids[RIGHT]->height;

    diff = left_height - right_height;
    
    return diff;
}


static avl_node_t AVLBalanceIMP(avl_node_t root)
{
    avl_node_t new_root = root;

    assert(NULL != root);

    if (BALANCED < AVLGetHeightDiffIMP(root))
    {
        if(BALANCED <= AVLGetHeightDiffIMP(root->kids[LEFT]))
        {
            new_root = AVLPerformBalanceIMP(LEFT, LEFT, root);
        }
        else
        {
            new_root = AVLPerformBalanceIMP(LEFT, RIGHT, root);
        }
    }
    else if (BALANCED < abs(AVLGetHeightDiffIMP(root)))
    {
        if (BALANCED <= abs(AVLGetHeightDiffIMP(root->kids[RIGHT])))
        {
            new_root = AVLPerformBalanceIMP(RIGHT, RIGHT, root);
        }
        else
        {
            new_root = AVLPerformBalanceIMP(RIGHT, LEFT, root);
        }
        
    }
    
    return new_root;
}


static avl_node_t AVLGetNextChildIMP(avl_node_t root, avl_node_t *return_root)
{
    assert(NULL != root);
    
    if (NULL == root->kids[LEFT])
    {
        *return_root = root;
        return root->kids[RIGHT];
    }

    root->kids[LEFT] = AVLGetNextChildIMP(root->kids[LEFT], return_root);

    root = AVLBalanceIMP(root);
    AVLUpdateHeightIMP(root);

    return root;
}


static avl_node_t AVLRemoveNoKidIMP(avl_node_t root)
{
    free(root);

    return NULL;
}


static avl_node_t AVLRemoveOneKidIMP(avl_node_t root)
{
    avl_node_t child = NULL;
    enum direction side = LEFT;

    assert(NULL != root);

    side = AVLGetChildSide(root);
    child = root->kids[side];
    root->kids[side] = NULL;

    free(root);

    return child;
}


static avl_node_t AVLRemoveTwoKidsIMP(avl_node_t root)
{
    avl_node_t child = NULL;
    avl_node_t return_root = NULL;
 
    assert(NULL != root);

    child = root->kids[RIGHT];

    root->kids[RIGHT] = AVLGetNextChildIMP(child, &return_root);

    return_root->kids[LEFT] = root->kids[LEFT];
    return_root->kids[RIGHT] = root->kids[RIGHT];
    root->kids[LEFT] = NULL;
    root->kids[RIGHT] = NULL;

    return_root = AVLBalanceIMP(return_root);
    AVLUpdateHeightIMP(return_root);

    free(root);

    return return_root;
}


static void InitRemoveTable()
{
    remove_func_table[NO_KIDS]  = AVLRemoveNoKidIMP;
    remove_func_table[ONE_KID]  = AVLRemoveOneKidIMP;
    remove_func_table[TWO_KIDS] = AVLRemoveTwoKidsIMP;
}


static avl_node_t AVLRemoveIMP(avl_node_t root, const void *key,
                       avl_cmp_func_t cmp_func, void *param, void **out_data)
{
    enum direction side = LEFT;
    int result = 0;

    assert(NULL != cmp_func); 

    if (NULL == root)
    {
        return NULL;
    }

    result = cmp_func(key, AVLGetDataIMP(root), param);

    if (IDENTICAL == result)
    {
        *out_data = AVLGetDataIMP(root);

        root = remove_func_table[AVLGetNumOfKidsIMP(root)](root);

        return root;
    }

    side = result >= RIGHT ? RIGHT : LEFT;

    root->kids[side] =  AVLRemoveIMP(root->kids[side], key, cmp_func, param,
                                     out_data);

    root = AVLBalanceIMP(root);
    AVLUpdateHeightIMP(root);

    return root;
}


static avl_node_t AVLCreateNodeIMP(const void *data, int height, 
                                   avl_node_t left_tree, avl_node_t right_tree)
{
    avl_node_t node = NULL;

    node = (avl_node_t)malloc(sizeof(struct avl_node));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = (void *)data;
    node->height = height;
    node->kids[LEFT] = left_tree;
    node->kids[RIGHT] = right_tree;

    return node;
}


static void AVLDestroyRecIMP(avl_node_t tree)
{
    if (NULL == tree)
    {
        return;
    }
    if (NULL != tree->kids[LEFT])
    {
        AVLDestroyRecIMP(tree->kids[LEFT]);
    }
    if (NULL != tree->kids[RIGHT])
    {
        AVLDestroyRecIMP(tree->kids[RIGHT]);
    }

    free(tree);
    return;
}


static size_t AVLSizeRecIMP(avl_node_t tree)
{
    if (NULL == tree)
    {
        return 0;
    }

    return (1 + AVLSizeRecIMP(tree->kids[RIGHT])) + 
           (AVLSizeRecIMP(tree->kids[LEFT]));
}


static avl_node_t AVLInsertIMP(avl_node_t root, const void *data,
                               avl_cmp_func_t cmp_func, void *param,
                               int *error)
{
    enum direction side = LEFT;
    int result = 0;
    avl_node_t new_root = NULL;

    assert(NULL != cmp_func);

    if (NULL == root)
    {
        new_root = AVLCreateNodeIMP(data, 0, NULL, NULL);
        if (NULL == new_root)
        {
            *error = FAILURE;
        }
        return new_root;
    }

    result = cmp_func(data, root->data, param);

    assert(IDENTICAL != result);

    side = result >= RIGHT ? RIGHT : LEFT; 

    root->kids[side] = AVLInsertIMP(root->kids[side], data, cmp_func, param, 
                                    error);

    root = AVLBalanceIMP(root);
    AVLUpdateHeightIMP(root);

    return root;
}


static avl_node_t AVLFindIMP(avl_node_t root, const void *key,
                             avl_cmp_func_t cmp_func, void *param)
{
    enum direction side = LEFT;
    int result = 0;

    assert(NULL != cmp_func);

    if (NULL == root)
    {
        return NULL;
    }

    result = cmp_func(key, root->data, param);
    if (IDENTICAL == result)
    {
        return root;
    }

    side = result >= RIGHT ? RIGHT : LEFT;

    return AVLFindIMP(root->kids[side], key, cmp_func, param);
}


static int AVLForEachIMP(avl_node_t root, avl_action_func_t action_func, 
                         void *param)
{
    int failure_flag = 0;
    
    assert(NULL != action_func);

    if (NULL == root)
    {
        return SUCCESS;
    }

    failure_flag = AVLForEachIMP(root->kids[LEFT], action_func, param);

    if (FAILURE == failure_flag || FAILURE == action_func(root->data, param))
    {
        return FAILURE;
    }

    return  (FAILURE == failure_flag || AVLForEachIMP(root->kids[LEFT], 
                                        action_func, param));
}


static int AVLMultiFindIMP(avl_node_t root, avl_cmp_func_t multi_cmp_func, 
                           void *data, void *multi_cmp_param, dlist_t *dlist,
                           int *out_error)
{
    dlist_iter_t iter = NULL;
    int result = 0;
    int temp1 = 0;
    int temp2 = 0;
    int found_flag = 0;

    assert(NULL != multi_cmp_func);
    assert(NULL != dlist);

    if (NULL == root || *out_error == ERROR)
    {
        return NOT_FOUND;
    }

    result = multi_cmp_func(data, AVLGetDataIMP(root), multi_cmp_param);
    if (IDENTICAL == result)
    {
        iter = DListBegin(dlist);
        
        if (True == 
            DListIsSameIterator(DListEnd(dlist),
                                DListInsertBefore(iter,
                                AVLGetDataIMP(root), dlist)))
        {
            *out_error = ERROR;
        }
        found_flag = FOUND;
    }

    temp1 = AVLMultiFindIMP(root->kids[LEFT], multi_cmp_func, data,
                            multi_cmp_param, dlist, out_error);
    temp2 = AVLMultiFindIMP(root->kids[RIGHT], multi_cmp_func, data,
                            multi_cmp_param, dlist, out_error);

    return found_flag + temp1 + temp2;
}


static int AVLMultiRemoveWithDlist(avl_t *tree, dlist_t *dlist, 
                                   int num_of_elements)
{
    dlist_iter_t iter = NULL;
    int i = 0;

    assert(NULL != tree);
    assert(NULL != dlist);

    iter = DListBegin(dlist);

    for (i = 0; i < num_of_elements; ++i)
    {
        AVLRemove(tree, DListGetData(iter));
        iter = DListNext(iter);
    }

    return SUCCESS;
}


avl_t *AVLCreate(avl_cmp_func_t compare_func, void *cmp_func_param)
{
    avl_t *tree = NULL;

    assert(NULL != compare_func);

    tree = (avl_t *)malloc(sizeof(avl_t));
    if (NULL == tree)
    {
        return NULL;
    }

    tree->root = NULL;
    tree->user_cmp_func = compare_func;
    tree->cmp_func_param = cmp_func_param;

    return tree;
}


void AVLDestroy(avl_t *tree)
{
    avl_node_t root = NULL;

    assert(NULL != tree);

    root = AVLGetRootIMP(tree);

    AVLDestroyRecIMP(root);
    free(tree);
}


void *AVLRemove(avl_t *tree, const void *key)
{
    void *out_data = NULL;

    assert(NULL != tree);

    InitRemoveTable();
    
    AVLRemoveIMP(tree->root, key, tree->user_cmp_func, tree->cmp_func_param,
                 &out_data);

    return out_data;
}


int AVLHeight(const avl_t *tree)
{
    assert(NULL != tree);

    return tree->root->height;
}


size_t AVLSize(const avl_t *tree)
{
    avl_node_t root = NULL;
    
    assert(NULL != tree);

    root = AVLGetRootIMP(tree);

    return AVLSizeRecIMP(root);
}


int AVLIsEmpty(const avl_t *tree)
{
    assert(NULL != tree);
    
    if (NULL == tree->root)
    {
        return True;
    }

    return False;
}


int AVLInsert(avl_t *tree, const void *data)
{
    int error = SUCCESS;

    assert(NULL != tree);

    tree->root = AVLInsertIMP(tree->root, data, tree->user_cmp_func, 
                              tree->cmp_func_param, &error);

    if (error == FAILURE)
    {
        return FAILURE;
    }

    return SUCCESS;
}


void *AVLFind(const avl_t *tree, const void *key)
{
    avl_node_t node = NULL;

    assert(NULL != tree);
    assert(NULL != key);

    node = AVLFindIMP(tree->root, key, tree->user_cmp_func,
                      tree->cmp_func_param);
    if (NULL == node)
    {
        return NULL;
    }

    return node->data;
}


int AVLForEach(avl_t *tree, avl_action_func_t action_func, void *param)
{
    assert(NULL != tree);
    assert(NULL != action_func);
    
    return !!AVLForEachIMP(tree->root, action_func, param);
}


int AVLMultiFind(const avl_t *tree, avl_cmp_func_t multi_cmp_func, void *data,
                 void *multi_cmp_param, dlist_t *dlist)
{
    int found_flag = NOT_FOUND;
    int out_error = False;
    assert(NULL != tree);
    assert(NULL != multi_cmp_func);
    assert(NULL != dlist);

    found_flag = AVLMultiFindIMP(tree->root, multi_cmp_func, data,
                                 multi_cmp_param, dlist, &out_error);
    
    if (ERROR == out_error)
    {
        return out_error;
    }

    return found_flag >= FOUND ? SUCCESS : FAILURE;
}


int AVLMultiRemove(avl_t *tree, avl_cmp_func_t multi_cmp_func, void *data,
                   void *multi_cmp_param, dlist_t *dlist)
{
    int found_flag = NOT_FOUND;
    int out_error = False;
    
    assert(NULL != tree);
    assert(NULL != multi_cmp_func);
    assert(NULL != dlist);

    found_flag = AVLMultiFindIMP(tree->root, multi_cmp_func, data,
                                 multi_cmp_param, dlist, &out_error);

    if (ERROR == out_error)
    {
        return out_error;
    }

    return found_flag >= NOT_FOUND ? 
           AVLMultiRemoveWithDlist(tree, dlist, found_flag) : FAILURE;
}
