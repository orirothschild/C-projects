#include <stdio.h> /* printf */

#include "sorted_list.h"
#include "sorted_list_test_funcs.h"
#include "utils.h"

int ActionFuncIntAddition(void *data, void *param);
int CheckArrays(int *arr1, int *arr2, int arr_size);
int MatchFuncInts(const void *node_data, const void *match_data, 
                  const void *param);
int CompareFuncInts(const void *node_data, const void *match_data, 
                  void *param);

int main()
{
    RUN_TEST(TestSortedList_Create());
    RUN_TEST(TestSortedList_Size_Five());
    RUN_TEST(TestSortedList_Insert_Five());
    RUN_TEST(TestSortedList_IsEmpty_False());
    RUN_TEST(TestSortedList_IsSameIterator());
    RUN_TEST(TestSortedList_Erase());
    RUN_TEST(TestSortedList_Erase_Pop());
    RUN_TEST(TestSortedList_ForEach_True());
    RUN_TEST(TestSortedList_ForEach_False());
    RUN_TEST(TestSortedList_Find_True());
    RUN_TEST(TestSortedList_Find_False());
    RUN_TEST(TestSortedList_Merge());
    RUN_TEST(TestSortedList_Merge_Same());

    
    return (0);
}


int TestSortedList_Create()
{
    srt_list_t *slist = SortedListCreate(CompareFuncInts);
    
    if(NULL != slist)
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_Size_Five()
{
    srt_list_t *slist = SortedListCreate(CompareFuncInts);
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 1;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &m, &param);
    SortedListInsert(slist, &l, &param);
    SortedListInsert(slist, &k, &param);
    
    
    if(5 == SortedListSize(slist))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_Insert_Five()
{
    srt_list_iter_t iter = NULL;
    srt_list_t *slist = SortedListCreate(CompareFuncInts);
    
    int z = 0;
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 1;
    int array[5] = {5, 10, 15, 20, 25};
    int test_arr[5] = {0};
    int arr_size = 5;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &m, &param);
    SortedListInsert(slist, &l, &param);
    SortedListInsert(slist, &k, &param);
    
    iter = SortedListBegin(slist);
    
    for (z = 0; z < arr_size; ++z)
    {
        test_arr[z] = *(int *)SortedListGetData(iter);
        iter = SortedListNext(iter);
    }
    
    if(True == CheckArrays(array, test_arr, arr_size))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_IsEmpty_False()
{
    srt_list_t *slist = SortedListCreate(CompareFuncInts);

    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 1;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &m, &param);
    SortedListInsert(slist, &l, &param);
    SortedListInsert(slist, &k, &param);
    
    if(False == SortedListIsEmpty(slist))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_IsSameIterator()
{
    srt_list_iter_t iter1 = NULL;
    srt_list_iter_t iter2 = NULL;
    srt_list_t *slist = SortedListCreate(CompareFuncInts);

    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 1;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &m, &param);
    SortedListInsert(slist, &l, &param);
    SortedListInsert(slist, &k, &param);
    
    iter1 = SortedListPrev(SortedListEnd(slist));
    iter2 = SortedListPrev(SortedListEnd(slist));
    
    if(True == SortedListIsSameIterator(iter1, iter2))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_Erase()
{
    srt_list_iter_t iter = NULL;
    
    srt_list_t *slist = SortedListCreate(CompareFuncInts);

    int i = 5;
    int param = 1;
        
    iter = SortedListInsert(slist, &i, &param);
    
    SortedListErase(iter);
    
    if(True == SortedListIsEmpty(slist))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_Erase_Pop()
{
    srt_list_iter_t iter = NULL;
    
    srt_list_t *slist = SortedListCreate(CompareFuncInts);

    int z = 0;
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 1;
    int array[2] = {10, 15};
    int test_arr[2] = {0};
    int arr_size = 2;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &k, &param);
    SortedListInsert(slist, &l, &param);
    iter = SortedListInsert(slist, &m, &param);
    
    SortedListErase(iter);
    SortedListPopBack(slist);
    SortedListPopFront(slist);
    
    iter = SortedListBegin(slist);
    
    for (z = 0; z < arr_size; ++z)
    {
        test_arr[z] = *(int *)SortedListGetData(iter);
        iter = SortedListNext(iter);
    }
    
    if(True == CheckArrays(array, test_arr, arr_size))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_ForEach_True()
{
    srt_list_iter_t start = NULL;
    srt_list_iter_t end = NULL;
    
    srt_list_t *slist = SortedListCreate(CompareFuncInts);

    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 100;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &k, &param);
    SortedListInsert(slist, &l, &param);
    SortedListInsert(slist, &m, &param);
    
    start = SortedListNext(SortedListBegin(slist));
    end = SortedListEnd(slist);
    
    
    if(0 == SortedListForEach(start, end, ActionFuncIntAddition, &param))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_ForEach_False()
{
    srt_list_iter_t start = NULL;
    srt_list_iter_t end = NULL;
    
    srt_list_t *slist = SortedListCreate(CompareFuncInts);
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 30;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &k, &param);
    SortedListInsert(slist, &l, &param);
    SortedListInsert(slist, &m, &param);
    
    start = SortedListNext(SortedListBegin(slist));
    end = SortedListEnd(slist);
    
    
    if(FAILURE == SortedListForEach(start, end, ActionFuncIntAddition, &param))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_Find_True()
{
    srt_list_iter_t start = NULL;
    srt_list_iter_t end = NULL;
    
    srt_list_t *slist = SortedListCreate(CompareFuncInts);
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 1;
    const int user_data = 25;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &k, &param);
    SortedListInsert(slist, &l, &param);
    SortedListInsert(slist, &m, &param);
    
    start = SortedListNext(SortedListBegin(slist));
    end = SortedListEnd(slist);
    
    if(True == SortedListFind(start, end, MatchFuncInts, &param, &user_data))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_Find_False()
{
    srt_list_iter_t start = NULL;
    srt_list_iter_t end = NULL;
    
    srt_list_t *slist = SortedListCreate(CompareFuncInts);
    
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int param = 1;
    const int user_data = 30;
    
    SortedListInsert(slist, &i, &param);
    SortedListInsert(slist, &j, &param);
    SortedListInsert(slist, &k, &param);
    SortedListInsert(slist, &l, &param);
    SortedListInsert(slist, &m, &param);
    
    start = SortedListNext(SortedListBegin(slist));
    end = SortedListEnd(slist);
    
    if(False == SortedListFind(start, end, MatchFuncInts, &param, &user_data))
    {
        SortedListDestroy(slist);
        return (PASS);
    }
    
    SortedListDestroy(slist);
    return (FAIL);
}


int TestSortedList_Merge()
{
    srt_list_iter_t start = NULL;
    srt_list_iter_t end = NULL;
    srt_list_iter_t iter = NULL;
    
    srt_list_t *slist1 = SortedListCreate(CompareFuncInts);
    srt_list_t *slist2 = SortedListCreate(CompareFuncInts);
    
    int z = 0;
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
    
    int array[9] = {5, 15, 20, 25, 30, 35, 40, 45, 50};
    int test_arr[9] = {0};
    int arr_size = 9;
    
    SortedListInsert(slist1, &i, &param);
    SortedListInsert(slist1, &k, &param);
    SortedListInsert(slist1, &n, &param);
    SortedListInsert(slist1, &p, &param);
    SortedListInsert(slist1, &r, &param);
    
    SortedListInsert(slist2, &j, &param);
    SortedListInsert(slist2, &l, &param);
    SortedListInsert(slist2, &m, &param);
    SortedListInsert(slist2, &o, &param);
    SortedListInsert(slist2, &q, &param);
    
    start = SortedListNext(SortedListBegin(slist2));
    end = SortedListEnd(slist2);
    
    SortedListMerge(slist1, start, end, &param);
    
    iter = SortedListBegin(slist1);
    
    for (z = 0; z < arr_size; ++z)
    {
        test_arr[z] = *(int *)SortedListGetData(iter);
        iter = SortedListNext(iter);
    }
    
    
    if(True == CheckArrays(array, test_arr, arr_size))
    {
        SortedListDestroy(slist1);
        SortedListDestroy(slist2);
        return (PASS);
    }
    
    SortedListDestroy(slist1);
    SortedListDestroy(slist2);
    return (FAIL);
}

int TestSortedList_Merge_Same()
{
    srt_list_iter_t start = NULL;
    srt_list_iter_t end = NULL;
    srt_list_iter_t iter = NULL;
    
    srt_list_t *slist1 = SortedListCreate(CompareFuncInts);
    srt_list_t *slist2 = SortedListCreate(CompareFuncInts);
    
    int z = 0;
    int i = 5;
    int j = 10;
    int k = 15;
    int l = 20;
    int m = 25;
    int n = 30;
    int o = 30;
    int p = 40;
    int q = 45;
    int r = 50;
    int param = 1;
    
    int array[9] = {5, 15, 20, 25, 30, 30, 40, 45, 50};
    int test_arr[9] = {0};
    int arr_size = 9;
    
    SortedListInsert(slist1, &i, &param);
    SortedListInsert(slist1, &k, &param);
    SortedListInsert(slist1, &n, &param);
    SortedListInsert(slist1, &p, &param);
    SortedListInsert(slist1, &r, &param);
    
    SortedListInsert(slist2, &j, &param);
    SortedListInsert(slist2, &l, &param);
    SortedListInsert(slist2, &m, &param);
    SortedListInsert(slist2, &o, &param);
    SortedListInsert(slist2, &q, &param);
    
    start = SortedListNext(SortedListBegin(slist2));
    end = SortedListEnd(slist2);
    
    SortedListMerge(slist1, start, end, &param);
    
    iter = SortedListBegin(slist1);
    
    for (z = 0; z < arr_size; ++z)
    {
        test_arr[z] = *(int *)SortedListGetData(iter);
        iter = SortedListNext(iter);
    }
    
    
    if(True == CheckArrays(array, test_arr, arr_size))
    {
        SortedListDestroy(slist1);
        SortedListDestroy(slist2);
        return (PASS);
    }
    
    SortedListDestroy(slist1);
    SortedListDestroy(slist2);
    return (FAIL);
}
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


int CompareFuncInts(const void *node_data, const void *match_data, 
                  void *param)
{
	(void)param;
	
	return (*(int *)node_data > *(int *)match_data);
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
