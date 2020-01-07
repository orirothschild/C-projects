#include <stdio.h> /* printf */

#include "avl.h"
#include "avl_test_funcs.h"
#include "utils.h"

int CompareNodes(const void *user_data, const void *node_data, void *param);
int CompareData(const void *user_data, const void *node_data, void *param);
int MultiCompareData(const void *user_data, const void *node_data, void *param);
int ActionFuncSuccess(void *user_data, void *param);
int ActionFuncFailure(void *user_data, void *param);
void InsertData(avl_t *tree);
void InitDataTable();



typedef struct person data_t;

struct person
{
    int uuid;
    int YOB;
    int YOD;
    char *first_name;
    char *last_name;
};

data_t data_table[10] = {0};

int main()
{
    RUN_TEST(TEST_AVL_CREATE());
    RUN_TEST(TEST_AVL_IsEmpty_True());
    RUN_TEST(TEST_AVL_IsEmpty_False());
    RUN_TEST(TEST_AVL_Insert_One());
    RUN_TEST(TEST_AVL_Size_Zero());
    RUN_TEST(TEST_AVL_Size_One());
    RUN_TEST(TEST_AVL_Size_Three());
    RUN_TEST(TEST_AVL_Find());
    RUN_TEST(TEST_AVL_ForEach_Success());
    RUN_TEST(TEST_AVL_ForEach_Failure());
    RUN_TEST(TEST_AVL_ForEach_Failure());
    RUN_TEST(TEST_AVL_MultiFind());
    RUN_TEST(TEST_AVL_MultiFind_False());
    RUN_TEST(TEST_AVL_Remove_No_Children());
    RUN_TEST(TEST_AVL_Remove_One_Child());
    RUN_TEST(TEST_AVL_Remove_Two_Children());
    RUN_TEST(TEST_AVL_MultiRemove());



    return (0);
}



int TEST_AVL_CREATE()
{
    avl_t *tree = NULL;
    int param = 0;

    tree = AVLCreate(CompareNodes, &param);

    if (NULL != tree)
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_IsEmpty_True()
{
    avl_t *tree = NULL;
    int param = 0;

    tree = AVLCreate(CompareNodes, &param);

    if (True == AVLIsEmpty(tree))
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_IsEmpty_False()
{
    avl_t *tree = NULL;
    int param = 0;
    int user_data;


    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &user_data);

    if (False == AVLIsEmpty(tree))
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_Insert_One()
{
    avl_t *tree = NULL;
    int param = 0;
    int user_data;


    tree = AVLCreate(CompareNodes, &param);
    ;

    if (SUCCESS == AVLInsert(tree, &user_data))
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_Size_Zero()
{
    avl_t *tree = NULL;
    int param = 0;

    tree = AVLCreate(CompareNodes, &param);
    

    if (0 == AVLSize(tree))
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_Size_One()
{
    avl_t *tree = NULL;
    int param = 0;
    int user_data = 1;

    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &user_data);
    
    if (1 == AVLSize(tree))
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_Size_Three()
{
    avl_t *tree = NULL;
    int param = 0;
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &data1);
    AVLInsert(tree, &data2);
    AVLInsert(tree, &data3);

    if (3 == AVLSize(tree))
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_Find()
{
    avl_t *tree = NULL;
    int param = 0;
    int data1 = 2;
    int data2 = 1;
    int data3 = 3;
    int found_data = 0;

    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &data1);
    AVLInsert(tree, &data2);
    AVLInsert(tree, &data3);

    
    found_data = *(int *)AVLFind(tree, &data2);

    if (1 == found_data)
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_ForEach_Success()
{
    avl_t *tree = NULL;
    int param = 0;
    int data1 = 2;
    int data2 = 1;
    int data3 = 3;
    int result = 0;

    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &data1);
    AVLInsert(tree, &data2);
    AVLInsert(tree, &data3);

    
    result = AVLForEach(tree, ActionFuncSuccess, &param);

    if (0 == result)
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_ForEach_Failure()
{
    avl_t *tree = NULL;
    int param = 0;
    int data1 = 2;
    int data2 = 1;
    int data3 = 3;
    int result = 0;

    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &data1);
    AVLInsert(tree, &data2);
    AVLInsert(tree, &data3);

    
    result = AVLForEach(tree, ActionFuncFailure, &param);

    if (1 == result)
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_MultiFind()
{
    avl_t *tree = NULL;
    int param = 0;
    int data = 1830;
    int result = 0;

    dlist_t *dlist = DListCreate();

    tree = AVLCreate(CompareData, &param);
    InitDataTable();
    InsertData(tree);
    
    result = AVLMultiFind(tree, MultiCompareData, &data, &param, dlist);
    /* printf("result is %d\n", result); */


    if (0 == result)
    {
        AVLDestroy(tree);
        DListDestroy(dlist);
        return PASS;
    }

    AVLDestroy(tree);
    DListDestroy(dlist);
    return FAIL;
}


int TEST_AVL_MultiFind_False()
{
    avl_t *tree = NULL;
    int param = 0;
    int data = 2018;
    int result = 0;

    dlist_t *dlist = DListCreate();

    tree = AVLCreate(CompareData, &param);
    InitDataTable();
    InsertData(tree);
    
    result = AVLMultiFind(tree, MultiCompareData, &data, &param, dlist);
    /* printf("result is %d\n", result); */


    if (1 == result)
    {
        AVLDestroy(tree);
        DListDestroy(dlist);
        return PASS;
    }

    AVLDestroy(tree);
    DListDestroy(dlist);
    return FAIL;
}


int TEST_AVL_MultiRemove()
{
    avl_t *tree = NULL;
    int param = 0;
    int data = 1904;
    int result = 0;

    dlist_t *dlist = DListCreate();

    tree = AVLCreate(CompareData, &param);
    InitDataTable();
    InsertData(tree);
    
    /* PrintTree(tree);
    printf("\n\n\n"); */

    result = AVLMultiRemove(tree, MultiCompareData, &data, &param, dlist);

    /* PrintTree(tree);
    printf("\n\n\n"); */


    if (SUCCESS == result)
    {
        AVLDestroy(tree);
        DListDestroy(dlist);
        return PASS;
    }

    AVLDestroy(tree);
    DListDestroy(dlist);
    return FAIL;
}

int TEST_AVL_Remove_No_Children()
{
    avl_t *tree = NULL;
    int param = 0;
    int data1 = 2;
    int data2 = 1;
    int data3 = 3;
    int result = 0;

    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &data1);
    AVLInsert(tree, &data2);
    AVLInsert(tree, &data3);

    /* PrintTree(tree); */
    
    result = *(int*)AVLRemove(tree, &data2);

    /* PrintTree(tree); */

    if (1 == result)
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_Remove_One_Child()
{
    avl_t *tree = NULL;
    int param = 0;
    int data1 = 2;
    int data2 = 1;
    int data3 = 3;
    int data4 = 0;
    int result = 0;

    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &data1);
    AVLInsert(tree, &data2);
    AVLInsert(tree, &data3);
    AVLInsert(tree, &data4);
    
    /* PrintTree(tree);
    printf("\n\n\n"); */

    result = *(int*)AVLRemove(tree, &data2);

    /* PrintTree(tree);
    printf("\n\n\n"); */

    if (1 == result)
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
    return FAIL;
}


int TEST_AVL_Remove_Two_Children()
{
    avl_t *tree = NULL;
    int param = 0;
    int data1 = 4;
    int data2 = 2;
    int data3 = 5;
    int data4 = 1;
    int data5 = 3;
    int result = 0;

    tree = AVLCreate(CompareNodes, &param);
    AVLInsert(tree, &data1);
    AVLInsert(tree, &data2);
    AVLInsert(tree, &data3);
    AVLInsert(tree, &data4);
    AVLInsert(tree, &data5);


    /* PrintTree(tree);
    printf("\n\n\n");
 */
    result = *(int*)AVLRemove(tree, &data2);

    /* PrintTree(tree);
    printf("\n\n\n"); */
    
    if (2 == result)
    {
        AVLDestroy(tree);
        return PASS;
    }

    AVLDestroy(tree);
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


int CompareData(const void *user_data, const void *node_data, void *param)
{
    data_t *user = (data_t *)user_data;
    data_t *node = (data_t *)node_data;

    (void)param;

    if(user->uuid < node->uuid)
    {
        return -1;
    }
    else if (user->uuid > node->uuid)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int MultiCompareData(const void *user_data, const void *node_data, void *param)
{
    /* data_t *user = (data_t *)user_data; */
    data_t *node = (data_t *)node_data;

    (void)param;

    if(*(int*)user_data < node->YOB)
    {
        return -1;
    }
    else if (*(int*)user_data > node->YOB)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int ActionFuncSuccess(void *user_data, void *param)
{
    (void)param;

    return !(*(int *)user_data + 5);
}


int ActionFuncFailure(void *user_data, void *param)
{
    (void)param;

    return !!(*(int *)user_data + 5);
}


void InsertData(avl_t *tree)
{
    int i = 0;
    for (i = 0; i < 10; ++i)
    {
        AVLInsert(tree, &data_table[i]);
        /* PrintTree(tree);
        printf("\n\n\n"); */
    }
}


void InitDataTable()
{
    data_t keats =       {0, 1770, 1821, "John", "Keats"};
    data_t dickinson =   {1, 1830, 1963, "Emily", "Dickinson"};
    data_t frost =       {2, 1874, 1963, "Robert", "Frost"};
    data_t poe =         {3, 1809, 1849, "Edgar", "Poe"};
    data_t wordsworth =  {4, 1770, 1850, "William", "Wordsworth"};
    data_t whitman =     {5, 1819, 1892, "Walt", "Whitman"};
    data_t neruda =      {6, 1904, 1963, "Pablo", "Neruda"};
    data_t hardy =       {9, 1840, 1928, "Thomas", "Hardy"};
    data_t silverstein = {8, 1830, 1963, "Shel", "Silverstein"};
    data_t wilde =       {7, 1854, 1900, "Oscar", "Wilde"};

    data_table[0] = keats;
    data_table[1] = dickinson;
    data_table[2] = frost;
    data_table[3] = poe;
    data_table[4] = wordsworth;
    data_table[5] = whitman;
    data_table[6] = neruda;
    data_table[7] = hardy;
    data_table[8] = silverstein;
    data_table[9] = wilde;
}


/* static void Print2DUtil(avl_node_t root, int space)
{
   int i = 0;

   if (root == NULL)
       return;

   space += 10;

   Print2DUtil(root->kids[RIGHT], space);

   printf("\n");
   for (i = 10; i < space; i++)
   {
       printf(" ");
   }
   printf("%p\n", (void *)root);
   for (i = 10; i < space; i++)
   {
       printf(" ");
   }
   printf("%d\n", *(int*)root->data);
   Print2DUtil(root->kids[LEFT], space);
}

void PrintTree(avl_t *avl)
{
   Print2DUtil(avl->root , 0);
} */
