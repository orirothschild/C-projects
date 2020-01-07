#include <stdio.h> /* printf */
#include <stdlib.h>

#include "bst.h"
#include "bst_test_funcs.h"
#include "utils.h"


void PrintArray(bst_t *bst);
int CompareNodes(const void *user_data, const void *node_data, void *param);
int ActionFunc(void *user_data, void *param);



int main()
{
    RUN_TEST(TEST_BST_CREATE());
    RUN_TEST(TEST_BST_IsEmpty_True());
    RUN_TEST(TEST_BST_IsEmpty_False());
    RUN_TEST(TEST_BST_Size_Zero());
    RUN_TEST(TEST_BST_Size_One());
    RUN_TEST(TEST_BST_Next_one());
    RUN_TEST(TEST_BST_Prev_one());
    RUN_TEST(TEST_BST_Insert_Six_FindNode());
    RUN_TEST(TEST_BST_Insert_Six_ActionFunc());
    RUN_TEST(TEST_BST_Remove_NoChildren());
    RUN_TEST(TEST_BST_Remove_OneChild_Next());
    RUN_TEST(TEST_BST_Remove_OneChild_Prev());
    RUN_TEST(TEST_BST_Remove_TwoChildren());
    RUN_TEST(TEST_BST_Remove_TwoChildren_Long());

    return (0);
}


int TEST_BST_CREATE()
{
    bst_t *bst = NULL;
    int param = 0;

    bst = BSTCreate(CompareNodes, &param);

    if (NULL != bst)
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_IsEmpty_True()
{
    bst_t *bst = NULL;
    int param = 0;

    bst = BSTCreate(CompareNodes, &param);

    if (True == BSTIsEmpty(bst))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_IsEmpty_False()
{
    bst_t *bst = NULL;
    int param = 0;
    int user_data;


    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data);

    if (False == BSTIsEmpty(bst))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Size_Zero()
{
    bst_t *bst = NULL;
    int param = 0;

    bst = BSTCreate(CompareNodes, &param);
    

    if (0 == BSTSize(bst))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Size_One()
{
    bst_t *bst = NULL;
    int param = 0;
    int user_data = 1;


    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data);
    


    if (1 == BSTSize(bst))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Next_one()
{
    bst_t *bst = NULL;
    int param = 0;
    int user_data = 1;


    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data);
    


    if (BSTEnd(bst) == BSTNext(BSTBegin(bst)))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Prev_one()
{
    bst_t *bst = NULL;
    bst_iter_t iter1 = NULL;
    int param = 0;
    int user_data1 = 1;
    int user_data2 = 0;


    bst = BSTCreate(CompareNodes, &param);
    iter1 = BSTInsert(bst, &user_data1);
    BSTInsert(bst, &user_data2);

    if (0 == *(int *)BSTGetData(BSTPrev(iter1)))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Insert_Six_FindNode()
{
    bst_t *bst = NULL;
    bst_iter_t iter = NULL;
    int param = 0;
    int user_data1 = 6;
    int user_data2 = 2;
    int user_data3 = 1;
    int user_data4 = 9;
    int user_data5 = 8;
    int user_data6 = 10;

    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data1);
    BSTInsert(bst, &user_data2);
    BSTInsert(bst, &user_data3);
    BSTInsert(bst, &user_data4);
    iter = BSTInsert(bst, &user_data5);
    BSTInsert(bst, &user_data6);

    if (True == BSTIsSameIterator(iter, BSTFindNode(bst, &user_data5)))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Insert_Six_ActionFunc()
{
    bst_t *bst = NULL;
    bst_iter_t iter1 = NULL;
    bst_iter_t iter2 = NULL;
    int param = 0;
    int result = 0;
    int user_data1 = 6;
    int user_data2 = 2;
    int user_data3 = 1;
    int user_data4 = 9;
    int user_data5 = 8;
    int user_data6 = 10;

    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data1);
    iter1 = BSTInsert(bst, &user_data2);
    BSTInsert(bst, &user_data3);
    BSTInsert(bst, &user_data4);
    iter2 = BSTInsert(bst, &user_data5);
    BSTInsert(bst, &user_data6);

    result = BSTForEach(iter1, iter2, ActionFunc, &param);

    if (0 == result)
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Remove_NoChildren()
{
    bst_t *bst = NULL;
    bst_iter_t iter = NULL;
    int param = 0;
    int user_data1 = 6;
    int user_data2 = 2;
    int user_data3 = 1;
    int user_data4 = 9;
    int user_data5 = 8;
    int user_data6 = 10;

    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data1);
    BSTInsert(bst, &user_data2);
    iter = BSTInsert(bst, &user_data3);
    BSTInsert(bst, &user_data4);
    BSTInsert(bst, &user_data5);
    BSTInsert(bst, &user_data6);

    /* printf("%d\n", *(int *)BSTRemove(iter)); */

    if (2 == *(int *)BSTGetData(BSTRemove(iter)))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Remove_OneChild_Next()
{
    bst_t *bst = NULL;
    bst_iter_t iter = NULL;
    int param = 0;
    int user_data1 = 6;
    int user_data2 = 2;
    int user_data3 = 1;
    int user_data4 = 9;
    int user_data5 = 8;
    int user_data6 = 10;

    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data1);
    iter = BSTInsert(bst, &user_data2);
    BSTInsert(bst, &user_data3);
    BSTInsert(bst, &user_data4);
    BSTInsert(bst, &user_data5);
    BSTInsert(bst, &user_data6);

    /* printf("%d\n", *(int *)BSTRemove(iter)); */

    if (6 == *(int *)BSTGetData(BSTRemove(iter)))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Remove_OneChild_Prev()
{
    bst_t *bst = NULL;
    bst_iter_t iter = NULL;
    int param = 0;
    int user_data1 = 6;
    int user_data2 = 2;
    int user_data3 = 1;
    int user_data4 = 9;
    int user_data5 = 8;
    int user_data6 = 10;

    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data1);
    iter = BSTInsert(bst, &user_data2);
    BSTInsert(bst, &user_data3);
    BSTInsert(bst, &user_data4);
    BSTInsert(bst, &user_data5);
    BSTInsert(bst, &user_data6);

    if (1 == *(int *)BSTGetData(BSTPrev(BSTRemove(iter))))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Remove_TwoChildren()
{
    bst_t *bst = NULL;
    bst_iter_t iter = NULL;
    int param = 0;
    int user_data1 = 6;
    int user_data2 = 2;
    int user_data3 = 1;
    int user_data4 = 9;
    int user_data5 = 8;
    int user_data6 = 10;

    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data1);
    BSTInsert(bst, &user_data2);
    BSTInsert(bst, &user_data3);
    iter = BSTInsert(bst, &user_data4);
    BSTInsert(bst, &user_data5);
    BSTInsert(bst, &user_data6);

    if (True == BSTIsSameIterator(BSTRemove(iter), BSTPrev(BSTEnd(bst))))
    {
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


int TEST_BST_Remove_TwoChildren_Long()
{
    bst_t *bst = NULL;
    bst_iter_t iter = NULL;
    int param = 0;
    int user_data1 = 6;
    int user_data2 = 2;
    int user_data3 = 1;
    int user_data4 = 10;
    int user_data5 = 8;
    int user_data6 = 12;
    int user_data7 = 11;

    bst = BSTCreate(CompareNodes, &param);
    BSTInsert(bst, &user_data1);
    BSTInsert(bst, &user_data2);
    BSTInsert(bst, &user_data3);
    iter = BSTInsert(bst, &user_data4);
    BSTInsert(bst, &user_data5);
    BSTInsert(bst, &user_data6);
    BSTInsert(bst, &user_data7);


    if (11 == *(int *)BSTGetData(BSTRemove(iter)))
    {
        /* PrintArray(bst); */
        BSTDestroy(bst);
        return PASS;
    }

    BSTDestroy(bst);
    return FAIL;
}


/**********************************USER*FUNCTIONS******************************/
int CompareNodes(const void *user_data, const void *node_data, void *param)
{
    (void)param;
    if (*(int *)user_data < *(int *)node_data)
    {
        return -1;
    }
    else if (*(int *)user_data > *(int *)node_data)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int ActionFunc(void *user_data, void *param)
{
    (void)param;

    return !(*(int *)user_data + 5);
}


void PrintArray(bst_t *bst)
{
    bst_iter_t iter = NULL;

    for (iter = BSTBegin(bst);
         False == BSTIsSameIterator(iter, BSTEnd(bst)); 
         iter = BSTNext(iter))
    {
        printf("%d ", *(int *)BSTGetData(iter));
    }

    printf("\n\n");
}
