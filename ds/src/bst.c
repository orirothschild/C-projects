/***********************************
*                                  *
*   DS - Binary Search Tree        *
*   written by: Hadar Klein        *
*   date: 31.12.18                 *
*   reviewed by: Shay Weiss        *
*                                  *
***********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "bst.h"    /*  API   */
#include "utils.h"  /* utilis */


const int END_DATA = 987654321;

struct bst_node 
{
    void *data;
    struct bst_node *parent;
    struct bst_node *children[2];
};

struct bst
{
    struct bst_node *end;
    void *param;
    cmp_func_t user_cmp_func;
};

enum {LEFT, RIGHT};


static bst_iter_t BSTFindFarthestChildIMP(bst_iter_t iter, int direction)
{
    while (NULL != iter->children[direction])
    {
        iter = iter->children[direction];
    }

    return iter;
}


static bst_iter_t BSTFindFittingParentIMP(bst_iter_t iter, int direction)
{
    while (False == BSTIsSameIterator(iter, iter->parent->children[direction]))
    {
        iter = iter->parent;
    }

    return iter->parent;
}


static bst_iter_t BSTCreateNodeIMP(void *data, bst_iter_t parent, 
                                   bst_iter_t left_child, 
                                   bst_iter_t right_child)
{
    bst_iter_t node = NULL;
    
    node = (bst_iter_t)malloc(sizeof(struct bst_node));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = data;
    node->parent = parent;
    node->children[LEFT] = left_child;
    node->children[RIGHT] = right_child;
    
    return node;
}


static bst_iter_t BSTInsertIMP(const void *data, bst_iter_t iter, int direction)
{
    bst_iter_t insert_iter = NULL;

    assert(NULL != data);
    assert(NULL != iter);
    assert(LEFT == direction || RIGHT == direction);

    insert_iter = BSTCreateNodeIMP((void *)data, iter, NULL, NULL);
    if (NULL == insert_iter)
    {
        return NULL;
    }
    iter->children[direction] = insert_iter;

    return insert_iter;
}


static bst_iter_t BSTGetRoot(const bst_t *bst)
{
    assert(NULL != bst);

    return bst->end->children[LEFT];
}


static bst_iter_t BSTFindIMP(const bst_t *bst, const void *data)
{
    bst_iter_t iter = NULL;
    bst_iter_t parent = BSTEnd(bst);
    int result = 0;

    assert(NULL != bst);

    iter = BSTGetRoot(bst);

    while (NULL != iter)
    {
        result = bst->user_cmp_func(data, BSTGetData(iter), bst->param);

        parent = iter;
        if (0 > result)
        {
            iter = iter->children[LEFT];
        }
        else if (0 < result)
        {
            iter = iter->children[RIGHT];
        }
        else
        {
            return iter;
        }
    }

    return parent;
}


static int BSTNumOfChildrenIMP(bst_iter_t iter)
{
    return !!(iter->children[LEFT]) + !!(iter->children[RIGHT]);
}

static int BSTGetChildDirection(bst_iter_t remove_iter)
{
    if (True == BSTIsSameIterator(remove_iter, 
                                  remove_iter->parent->children[LEFT]))
    {
        return LEFT;
    }
    else
    {
        return RIGHT;
    }
}

static bst_iter_t BSTRemoveNoChildrenIMP(bst_iter_t iter)
{
    bst_iter_t parent = NULL;
    bst_iter_t iter_next = NULL;

    assert(NULL != iter);
    
    iter_next = BSTNext(iter);
    parent = iter->parent;

    parent->children[BSTGetChildDirection(iter)] = NULL;
    iter->parent = NULL;
    free(iter);
    
    return iter_next;
}


static bst_iter_t BSTGetOnlyChildIMP(bst_iter_t iter)
{
    if (NULL != iter->children[LEFT])
    {
        return iter->children[LEFT];
    }
    return iter->children[RIGHT];
}


static void DisconnectNodeIMP(bst_iter_t iter)
{
    iter->parent = NULL;
    iter->children[LEFT] = NULL;
    iter->children[RIGHT] = NULL;

    free(iter);
}

static bst_iter_t BSTRemoveOneChildIMP(bst_iter_t iter)
{
    bst_iter_t grandparent = NULL;
    bst_iter_t next_iter = NULL;
    bst_iter_t child = NULL;

    assert(NULL != iter);
    
    next_iter = BSTNext(iter);
    grandparent = iter->parent;
    child = BSTGetOnlyChildIMP(iter);

    grandparent->children[BSTGetChildDirection(iter)] = child;
    child->parent = grandparent;
    
    DisconnectNodeIMP(iter);

    return next_iter;
}




static bst_iter_t BSTRemoveTwoChildrenIMP(bst_iter_t remove_iter)
{
    bst_iter_t replace_iter = NULL;
    
    assert(NULL != remove_iter);
    
    replace_iter = BSTNext(remove_iter);
    
    /* if the leftmost is also the right from remove */
    if (False == BSTIsSameIterator(replace_iter, remove_iter->children[RIGHT]))
    {
        replace_iter->parent->children[LEFT] = replace_iter->children[RIGHT];
        if (NULL != replace_iter->children[RIGHT])
        {
            replace_iter->children[RIGHT]->parent = replace_iter->parent;
        }
        replace_iter->children[RIGHT] = remove_iter->children[RIGHT];
        replace_iter->children[RIGHT]->parent = replace_iter;
    }
    
    replace_iter->parent = remove_iter->parent;
    replace_iter->parent->children[BSTGetChildDirection(remove_iter)] = 
                                                        replace_iter;

    replace_iter->children[LEFT] = remove_iter->children[LEFT];
    replace_iter->children[LEFT]->parent = replace_iter;

    DisconnectNodeIMP(remove_iter);

    return replace_iter;
}


bst_t *BSTCreate(cmp_func_t compare_func, void *param)
{
    bst_t *bst = NULL;
    bst_iter_t end = NULL;

    assert(NULL != compare_func);

    end = BSTCreateNodeIMP((int *)&END_DATA, NULL, NULL, NULL);
    if (NULL == end)
    {
        return NULL;
    }

    bst = (bst_t *)malloc(sizeof(bst_t));
    if (NULL == bst)
    {
        free(end);
        return NULL;
    }

    bst->end = end;
    bst->param = param;
    bst->user_cmp_func = compare_func;

    return bst;
}


void BSTDestroy(bst_t *bst)
{
    bst_iter_t temp = NULL;
    bst_iter_t iter = NULL;

    assert(NULL != bst);

    iter = BSTBegin(bst);
    while (False == BSTIsEmpty(bst))
    {
        if (NULL == iter->children[LEFT] && NULL == iter->children[RIGHT])
        {
            temp = iter;
            iter = iter->parent;
            BSTRemove(temp);
        }

        if (NULL == iter->children[LEFT] && NULL != iter->children[RIGHT])
        {
            iter = iter->children[RIGHT];
        }

        iter = BSTFindFarthestChildIMP(iter, LEFT);
    }
    free(bst->end);
    free(bst);
}


bst_iter_t BSTRemove(bst_iter_t iter)
{
    int num_of_children = 0;
    bst_iter_t r_iter = NULL;

    assert(NULL != iter);

    num_of_children = BSTNumOfChildrenIMP(iter);

    switch (num_of_children)
    {
        case 0 :
            r_iter = BSTRemoveNoChildrenIMP(iter);
            return r_iter;
        case 1 :
            r_iter = BSTRemoveOneChildIMP(iter);
            return r_iter;
        default :
            r_iter = BSTRemoveTwoChildrenIMP(iter);
            return r_iter;
    }
}


bst_iter_t BSTBegin(const bst_t *bst)
{
    assert(NULL != bst);

    return BSTFindFarthestChildIMP(bst->end, LEFT);
}


bst_iter_t BSTEnd(const bst_t *bst)
{
    assert(NULL != bst);

    return bst->end;
}


bst_iter_t BSTNext(bst_iter_t iter)
{
    assert(NULL != iter);

    if (NULL != iter->children[RIGHT])
    {
        iter = iter->children[RIGHT];
        return BSTFindFarthestChildIMP(iter, LEFT);
    }
    
    return BSTFindFittingParentIMP(iter, LEFT);
}


bst_iter_t BSTPrev(bst_iter_t iter)
{
    assert(NULL != iter);

    if (NULL != iter->children[LEFT])
    {
        iter = iter->children[LEFT];
        return BSTFindFarthestChildIMP(iter, RIGHT);
    }

    return BSTFindFittingParentIMP(iter, RIGHT);
}


bst_iter_t BSTInsert(bst_t *bst, const void *user_data)
{
    bst_iter_t iter = NULL;
    bst_iter_t inserted_iter = NULL;
    int result = 0;

    assert(NULL != bst);

    if (True == BSTIsEmpty(bst))
    {
        return BSTInsertIMP(user_data, BSTBegin(bst), LEFT);
    }

    iter = BSTFindIMP((bst_t *)bst, user_data);

    result = bst->user_cmp_func(user_data, BSTGetData(iter), bst->param);
    
    assert(IDENTICAL != result);

    if (LEFT >= result)
    {
        inserted_iter = BSTInsertIMP(user_data, iter, LEFT);
    }
    else
    {
        inserted_iter = BSTInsertIMP(user_data, iter, RIGHT);
    }

    return inserted_iter;
}


bst_iter_t BSTFindNode(const bst_t *bst, const void *user_data)
{
    bst_iter_t iter = NULL;

    assert(NULL != bst);

    iter = BSTFindIMP(bst, user_data);
    if (IDENTICAL == bst->user_cmp_func(user_data, 
                                        BSTGetData(iter), 
                                        bst->param))
    {
        return iter;
    }

    return bst->end;
}


int BSTForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func,
               void *param)
{
    bst_iter_t iter = NULL;
    int result = 0;

    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != action_func);
    
    iter = from;
    while (SUCCESS == result && False == BSTIsSameIterator(iter, to))
    {
        result = action_func(BSTGetData(iter), param);
        iter = BSTNext(iter);
    }

    return result;
}


void *BSTGetData(const bst_iter_t iter)
{
    assert(NULL != iter);

    return iter->data;
}


int BSTIsEmpty(const bst_t *bst)
{
    assert(NULL != bst);

    if(NULL == bst->end->children[LEFT])
    {
        return True;
    }
    return False;
}


size_t BSTSize(const bst_t *bst)
{
    bst_iter_t end = NULL;
    bst_iter_t runner = NULL;
    int count = 0;

    assert(NULL != bst);

    end = BSTEnd(bst);

    for (runner = BSTBegin(bst); False == BSTIsSameIterator(runner, end);
         runner = BSTNext(runner))
    {
        ++count;
    }

    return count;
}


int BSTIsSameIterator(const bst_iter_t iter1, const bst_iter_t iter2)
{
    return iter1 == iter2;
}
