#include <stdio.h>              /* printf */

#include "dlist.h"              /* API */
#include "dlist_test_funcs.h"    /* test functions */
#include "utils.h"              /* utilities */

int CheckArrays(int *arr1, int *arr2, int arr_size);
int ActionFuncIntAddition(void *data, void *param);
int MatchFuncInts(const void *node_data, const void *match_data, 
                  const void *param);

int main()
{
    RUN_TEST(TestDList_Create());
    RUN_TEST(TestDList_Size_Five());
    RUN_TEST(TestDList_Insert_Five());
    RUN_TEST(TestDList_IsEmpty_False());
    RUN_TEST(TestDList_IsEmpty_True());
    RUN_TEST(TestDList_IsSameIterator());
    RUN_TEST(TestDList_SpliceBefore());
    RUN_TEST(TestDList_ForEach_True());
    RUN_TEST(TestDList_ForEach_False());
    RUN_TEST(TestDList_Find_True());
    RUN_TEST(TestDList_Find_False());

    return (0);
}


int TestDList_Create()
{
    dlist_t *dlist = DListCreate();
    
    if(NULL != dlist)
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}


int TestDList_Size_Five()
{
    dlist_iter_t iter = NULL;
    dlist_t *dlist = DListCreate();

    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(iter, &j, dlist);
    iter = DListPushFront(dlist, &k);
    iter = DListPushBack(dlist, &l);
    iter = DListInsertBefore(iter, &m, dlist);
    
    if(5 == DListCount(dlist))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}


int TestDList_Insert_Five()
{
    dlist_iter_t iter = NULL;
    dlist_t *dlist = DListCreate();
    size_t z = 0;
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int array[5] = {15, 5, 10, 25, 20};
    size_t arr_size = sizeof(array)/sizeof(int);
    int list_array[5] = {0};
    
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(iter, &j, dlist);
    iter = DListPushFront(dlist, &k);
    iter = DListPushBack(dlist, &l);
    iter = DListInsertBefore(iter, &m, dlist);
    
    iter = DListBegin(dlist);
    
    for (z = 0; z < arr_size; ++z)
    {
        list_array[z] = *(int *)DListGetData(iter);
        iter = DListNext(iter);
    }
    
    if(True == CheckArrays(array, list_array, arr_size))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}


int TestDList_IsEmpty_False()
{
    dlist_iter_t iter = NULL;
    dlist_t *dlist = DListCreate();

    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
        
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(iter, &j, dlist);
    iter = DListPushFront(dlist, &k);
    iter = DListPushBack(dlist, &l);
    iter = DListInsertBefore(iter, &m, dlist);
    
    if(False == DListIsEmpty(dlist))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}


int TestDList_IsEmpty_True()
{
    dlist_iter_t iter = NULL;
    dlist_t *dlist = DListCreate();

    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
        
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(iter, &j, dlist);
    iter = DListPushFront(dlist, &k);
    iter = DListPushBack(dlist, &l);
    iter = DListInsertBefore(iter, &m, dlist);
    
    iter = DListErase(iter);
    DListPopBack(dlist);
    DListPopBack(dlist);
    DListPopBack(dlist);
    DListPopFront(dlist);
    
    if(True == DListIsEmpty(dlist))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}

int TestDList_IsSameIterator()
{
    dlist_iter_t iter1 = NULL;
    dlist_iter_t iter2 = NULL;
    dlist_iter_t iter = NULL;
    
    dlist_t *dlist = DListCreate();
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(DListBegin(dlist), &j, dlist);
    iter = DListInsertAfter(iter, &k, dlist);
    iter = DListInsertAfter(iter, &l, dlist);
    
    iter1 = DListNext(DListNext(DListBegin(dlist)));
    iter2 = DListPrev(DListPrev(DListEnd(dlist)));
    
    if(True == DListIsSameIterator(iter1, iter2))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}


int TestDList_SpliceBefore()
{
    dlist_iter_t iter1 = NULL;
    dlist_iter_t iter2 = NULL;
    dlist_iter_t iter3 = NULL;
    dlist_iter_t iter = NULL;
    
    dlist_t *dlist1 = DListCreate();
    dlist_t *dlist2 = DListCreate();
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int n = 30;
    int o = 35;
    int p = 40;
    int q = 45;
    int r = 50;
    
    size_t z = 0;
    int array_new_long_test[6] = {40, 15, 20, 25, 45, 50};
    int array_new_short_test[4] = {5, 10, 30, 35};
    size_t arr_size_long = sizeof(array_new_long_test)/sizeof(int);
    size_t arr_size_short = sizeof(array_new_short_test)/sizeof(int);
    
    int array_new_long[6] = {0};
    int array_new_short[4] = {0};
    
    iter1 = DListInsertBefore(DListEnd(dlist1), &i, dlist1);
    iter1 = DListInsertAfter(DListBegin(dlist1), &j, dlist1);
    iter1 = DListInsertAfter(iter1, &k, dlist1);
    iter1 = DListInsertAfter(iter1, &l, dlist1);
    iter1 = DListInsertAfter(iter1, &m, dlist1);
    iter1 = DListInsertAfter(iter1, &n, dlist1);
    iter1 = DListInsertAfter(iter1, &o, dlist1);
    
    iter2 = DListInsertBefore(DListEnd(dlist2), &p, dlist2);
    iter2 = DListInsertAfter(DListBegin(dlist2), &q, dlist2);
    iter2 = DListInsertAfter(iter2, &r, dlist2);
    
    
    iter1 = DListPrev(DListPrev(DListEnd(dlist1)));
    iter3 = DListNext(DListNext(DListBegin(dlist1)));
    iter2 = DListNext(DListBegin(dlist2));
    
    DListSpliceBefore(iter2, iter3, iter1);
    
    
    iter = DListBegin(dlist2);
    
    for (z = 0; z < arr_size_long; ++z)
    {
        array_new_long[z] = *(int *)DListGetData(iter);
        iter = DListNext(iter);
    }
    
    iter = DListBegin(dlist1);
    
    for (z = 0; z < arr_size_short; ++z)
    {
        array_new_short[z] = *(int *)DListGetData(iter);
        iter = DListNext(iter);
    }
    
    if(True == CheckArrays(array_new_short_test,
                           array_new_short, 
                           arr_size_short)
               && CheckArrays(array_new_long_test,
                           array_new_long, 
                           arr_size_long))
    {
        DListDestroy(dlist1);
        DListDestroy(dlist2);
        return (PASS);
    }
    
    DListDestroy(dlist1);
    DListDestroy(dlist2);
    return (FAIL);
}


int TestDList_ForEach_True()
{
    dlist_iter_t iter = NULL;
    dlist_iter_t start = NULL;
    dlist_iter_t end = NULL;
    
    dlist_t *dlist = DListCreate();
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int n = 30;
    int o = 35;
    int p = 40;
    int q = 45;
    int r = 50;
    int param = 100;
    
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(DListBegin(dlist), &j, dlist);
    iter = DListInsertAfter(iter, &k, dlist);
    iter = DListInsertAfter(iter, &l, dlist);
    iter = DListInsertAfter(iter, &m, dlist);
    iter = DListInsertAfter(iter, &n, dlist);
    iter = DListInsertAfter(iter, &o, dlist);
    iter = DListInsertAfter(iter, &p, dlist);
    iter = DListInsertAfter(iter, &q, dlist);
    iter = DListInsertAfter(iter, &r, dlist);
    
    start = DListPrev(DListPrev(DListPrev(DListPrev(DListEnd(dlist)))));
    end = DListEnd(dlist);
    
    
    if(0 == DListForEach(start, end, ActionFuncIntAddition, &param))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
    
}


int TestDList_ForEach_False()
{
    dlist_iter_t iter = NULL;
    dlist_iter_t start = NULL;
    dlist_iter_t end = NULL;
    
    dlist_t *dlist = DListCreate();
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int n = 30;
    int o = 35;
    int p = 40;
    int q = 45;
    int r = 50;
    int param = 5;
    
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(DListBegin(dlist), &j, dlist);
    iter = DListInsertAfter(iter, &k, dlist);
    iter = DListInsertAfter(iter, &l, dlist);
    iter = DListInsertAfter(iter, &m, dlist);
    iter = DListInsertAfter(iter, &n, dlist);
    iter = DListInsertAfter(iter, &o, dlist);
    iter = DListInsertAfter(iter, &p, dlist);
    iter = DListInsertAfter(iter, &q, dlist);
    iter = DListInsertAfter(iter, &r, dlist);
    
    start = DListPrev(DListPrev(DListPrev(DListPrev(DListEnd(dlist)))));
    end = DListEnd(dlist);
    
    
    if(FAILURE == DListForEach(start, end, ActionFuncIntAddition, &param))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}


int TestDList_Find_True()
{
    dlist_iter_t iter = NULL;
    dlist_iter_t start = NULL;
    dlist_iter_t end = NULL;
    
    dlist_t *dlist = DListCreate();
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int n = 30;
    int o = 35;
    int p = 40;
    int q = 45;
    int r = 50;
    int param = 1;
    int user_data = 50;
    
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(DListBegin(dlist), &j, dlist);
    iter = DListInsertAfter(iter, &k, dlist);
    iter = DListInsertAfter(iter, &l, dlist);
    iter = DListInsertAfter(iter, &m, dlist);
    iter = DListInsertAfter(iter, &n, dlist);
    iter = DListInsertAfter(iter, &o, dlist);
    iter = DListInsertAfter(iter, &p, dlist);
    iter = DListInsertAfter(iter, &q, dlist);
    iter = DListInsertAfter(iter, &r, dlist);
    
    start = DListPrev(DListPrev(DListPrev(DListPrev(DListEnd(dlist)))));
    end = DListEnd(dlist);
    
    
    if(True == DListFind(start, end, MatchFuncInts, &param, &user_data))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}


int TestDList_Find_False()
{
    dlist_iter_t iter = NULL;
    dlist_iter_t start = NULL;
    dlist_iter_t end = NULL;
    
    dlist_t *dlist = DListCreate();
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int n = 30;
    int o = 35;
    int p = 40;
    int q = 45;
    int r = 50;
    int param = 1;
    int user_data = 55;
    
    iter = DListInsertBefore(DListEnd(dlist), &i, dlist);
    iter = DListInsertAfter(DListBegin(dlist), &j, dlist);
    iter = DListInsertAfter(iter, &k, dlist);
    iter = DListInsertAfter(iter, &l, dlist);
    iter = DListInsertAfter(iter, &m, dlist);
    iter = DListInsertAfter(iter, &n, dlist);
    iter = DListInsertAfter(iter, &o, dlist);
    iter = DListInsertAfter(iter, &p, dlist);
    iter = DListInsertAfter(iter, &q, dlist);
    iter = DListInsertAfter(iter, &r, dlist);
    
    start = DListPrev(DListPrev(DListPrev(DListPrev(DListEnd(dlist)))));
    end = DListEnd(dlist);
    
    
    if(False == DListFind(start, end, MatchFuncInts, &param, &user_data))
    {
        DListDestroy(dlist);
        return (PASS);
    }
    
    DListDestroy(dlist);
    return (FAIL);
}
/*int TestDList_Find_False();*/

/******************************************************************************/
int MatchFuncInts(const void *node_data, const void *match_data, 
                  const void *param)
{
	(void)param;
	
	return (*(int *)node_data == *(int *)match_data);
}


int ActionFuncIntAddition(void *data, void *param)
{
	if (50 == *(int *)data + *(int *)param)
	{
		return (1);
	}
	return (0);
}

int CheckArrays(int *arr1, int *arr2, int arr_size)
{
	int i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return (False);
		}
	}
	
	return (True);
}
