#include <stdio.h>   /* printf */
#include <string.h>  /* strcmp */
#include "sl_list.h" /* API    */

#include "sll_tests.h" /* test function declarations */

#define RUN_TEST(test) (!test) ? printf("FAIL : "#test"\n" ) : \
printf("PASS : "#test"\n")

int MatchFuncInts(const void *data, const void *param);
int ActionFuncIntAddition(const void *data, const void *param);
void PrintLinkedList(sll_node_t *head);
int CheckArrays(int *arr1, int *arr2, int arr_size);

enum {FAIL, PASS};

int main()
{
	RUN_TEST(TestSLListCreateNode());
	RUN_TEST(TestSLListInsertAfter_TwoNodes());
	RUN_TEST(TestSLListInsert_TwoNodes());
	RUN_TEST(TestSLListInsert_TwoNodesCheckNextNode());
	printf("\n");
	RUN_TEST(TestSLListInsertAfter_ManyNodes());
	RUN_TEST(TestSLListInsertAfter_ManyNodesCheckNextNode());
	RUN_TEST(TestSLListInsert_ManyNodes());
	RUN_TEST(TestSLListInsert_ManyNodesCheckNextNode());
	printf("\n");
	RUN_TEST(TestSLListRemoveAfter_TwoNodesReturn());
	RUN_TEST(TestSLListRemove_TwoNodes());
	RUN_TEST(TestSLListRemove_TwoNodesCheckNextNode());
	printf("\n");
	RUN_TEST(TestSLListHasLoop_True());
	RUN_TEST(TestSLListHasLoop_False());	
	printf("\n");	
	RUN_TEST(TestSLListFind_True());
	RUN_TEST(TestSLListFind_False());
	RUN_TEST(TestSLListForEach_True());
	RUN_TEST(TestSLListForEach_False());
	printf("\n");	
	RUN_TEST(TestSLListFlipFive());
	RUN_TEST(TestSLListCountFive());
	RUN_TEST(TestSLListHasIntersectionTrue());
	RUN_TEST(TestSLListHasIntersectionFalse());
    RUN_TEST(TestSLListHasIntersectionSubList());
			
	return (0);
}


int TestSLListCreateNode()
{
	size_t i = 5;
	sll_node_t *sll = SLListCreateNode(&i, NULL);

	if (NULL != sll)
	{
		SLListDestroyList(sll);
		return (PASS);
	}
	SLListDestroyList(sll);
	
	return (FAIL);
}


int TestSLListInsertAfter_TwoNodes()
{
	int i = 5;
	int j = 10;
	
	sll_node_t *sll1 = SLListCreateNode(&i, NULL);
	sll_node_t *sll2 = SLListCreateNode(&j, NULL);
	
		
	if (10 == *(int *)SLListInsertAfter(sll1,sll2)->data)
	{
		SLListDestroyList(sll1);
		return (PASS);
	}
	SLListDestroyList(sll1);
	
	return (FAIL);
}


int TestSLListInsert_TwoNodes()
{
	int i = 5;
	int j = 10;
	
	sll_node_t *sll1 = SLListCreateNode(&i, NULL);
	sll_node_t *sll2 = SLListCreateNode(&j, NULL);
	
		
	if (10 == *(int *)SLListInsert(sll1,sll2)->data)
	{
		SLListDestroyList(sll1);
		return (PASS);
	}
	SLListDestroyList(sll1);
	
	return (FAIL);
}


int TestSLListInsert_TwoNodesCheckNextNode()
{
	int i = 5;
	int j = 10;
	
	sll_node_t *sll1 = SLListCreateNode(&i, NULL);
	sll_node_t *sll2 = SLListCreateNode(&j, NULL);
	
		
	if (5 == *(int *)SLListInsert(sll1,sll2)->next->data)
	{
		SLListDestroyList(sll1);
		return (PASS);
	}
	SLListDestroyList(sll1);
	
	return (FAIL);
}


int TestSLListInsertAfter_ManyNodes()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);
	
	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	
	if (50 == *(int *)SLListInsertAfter(sll2,sll9)->data)
	{
		SLListDestroyList(sll0);
		return (PASS);
	}
	SLListDestroyList(sll0);
	
	return (FAIL);
}


int TestSLListInsertAfter_ManyNodesCheckNextNode()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);
	
	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	
	if (20 == *(int *)SLListInsertAfter(sll2,sll9)->next->data)
	{
		SLListDestroyList(sll0);
		return (PASS);
	}
	SLListDestroyList(sll0);
	
	return (FAIL);
}

int TestSLListInsert_ManyNodes()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);
	
	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	
		
	if (50 == *(int *)SLListInsert(sll2,sll9)->data)
	{
		SLListDestroyList(sll0);
		return (PASS);
	}
	SLListDestroyList(sll0);
	
	return (FAIL);
}


int TestSLListInsert_ManyNodesCheckNextNode()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);
	
	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	
		
	if (15 == *(int *)SLListInsert(sll2,sll9)->next->data)
	{
		SLListDestroyList(sll0);
		return (PASS);
	}
	SLListDestroyList(sll0);
	
	return (FAIL);
}


/******************************************************************************/
/******************************************************************************/


int TestSLListRemoveAfter_TwoNodesReturn()
{
	int i = 5;
	int j = 10;
	
	sll_node_t *return_node = NULL;
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	
	SLListInsertAfter(sll0,sll1);
	return_node = SLListRemoveAfter(sll0);	
	
		
	if (10 == *(int *)return_node->data)
	{
		SLListDestroyList(sll0);
		SLListDestroyList(return_node);
		return (PASS);
	}
	SLListDestroyList(sll1);
	SLListDestroyList(return_node);
	
	return (FAIL);
}


int TestSLListRemove_TwoNodes()
{
	int i = 5;
	int j = 10;
	int k = 15;
	
	sll_node_t *return_node = NULL;
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	
	return_node = SLListRemove(sll1);
	
	if (10 == *(int *)return_node->data)
	{
		SLListDestroyList(sll0);
		SLListDestroyList(return_node);
		return (PASS);
	}
	SLListDestroyList(sll0);
	SLListDestroyList(return_node);
	
	return (FAIL);
}


int TestSLListRemove_TwoNodesCheckNextNode()
{
	int i = 5;
	int j = 10;
	int k = 15;
	
	sll_node_t *return_node = NULL;
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	
	return_node = SLListRemove(sll1);
		
	if (15 == *(int *)sll0->next->data)
	{
		SLListDestroyList(sll0);
		SLListDestroyList(return_node);
		return (PASS);
	}
	SLListDestroyList(sll0);
	SLListDestroyList(return_node);
	
	return (FAIL);
}


/******************************************************************************/
/******************************************************************************/


int TestSLListHasLoop_True()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);
	
	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);
		
	sll9->next = sll1;		

	if (1 == SLListHasLoop(sll0))
	{
		sll9->next = NULL;
		SLListDestroyList(sll0);
		return (PASS);
	}
	SLListDestroyList(sll0);
	
	return (FAIL);
}


int TestSLListHasLoop_False()
{
	
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);

	if (0 == SLListHasLoop(sll0))
	{

		SLListDestroyList(sll0);

		return (PASS);
	}

	SLListDestroyList(sll0);

	return (FAIL);
}


/******************************************************************************/
/******************************************************************************/


int TestSLListFind_True()
{
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
	int param = 25;
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);

	if (sll4 == (SLListFind(sll0, MatchFuncInts, &param)))
	{
		SLListDestroyList(sll0);

		return (PASS);
	}

	SLListDestroyList(sll0);

	return (FAIL);
}


int TestSLListFind_False()
{
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
	int param = 55;
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);

	if (NULL == (SLListFind(sll0, MatchFuncInts, &param)))
	{
		SLListDestroyList(sll0);

		return (PASS);
	}

	SLListDestroyList(sll0);

	return (FAIL);
}


int TestSLListForEach_True()
{
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
	int param = 25;
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);

	if (1 == (SLListForEach(sll0, ActionFuncIntAddition, &param)))
	{
		SLListDestroyList(sll0);

		return (PASS);
	}

	SLListDestroyList(sll0);

	return (FAIL);
}


int TestSLListForEach_False()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	SLListInsertAfter(sll6,sll7);
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);

	if (0 == (SLListForEach(sll0, ActionFuncIntAddition, &param)))
	{
		SLListDestroyList(sll0);

		return (PASS);
	}

	SLListDestroyList(sll0);

	return (FAIL);
}


/******************************************************************************/
/******************************************************************************/


int TestSLListFlipFive()
{
	int i = 5;
	int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int arr_size = 5;
	int int_arr[5] = {0};
	int int_arr_reverse[5] = {0};
	int idx = 0;
	
	sll_node_t *node = 0;
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *temp = NULL;
	
	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);

	node = sll0;
	for (idx = 0; idx < arr_size; ++idx)
	{
		int_arr[idx] = *(int *)node->data;
		node = node->next;
	}
	
	temp = SLListFlipRecursive(sll0);
	
	node = temp;
	for (idx = 0; idx < arr_size; ++idx)
	{
		int_arr_reverse[arr_size - 1 - idx] = *(int *)node->data;
		node = node->next;
	}
	
	
	if (1 == CheckArrays(int_arr, int_arr_reverse, arr_size))
	{
		SLListDestroyList(temp);
	
		return (PASS);
	}
	SLListDestroyList(temp);
	
	return (FAIL);
}


int TestSLListCountFive()
{
	int i = 5;
	int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
		
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	
	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	
	if (5 == SLListCount(sll0))
	{
		SLListDestroyList(sll0);

		return (PASS);
	}

	SLListDestroyList(sll0);

	return (FAIL);
	
}


int TestSLListHasIntersectionTrue()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);
	
	sll9->next = sll5;
	
	if (sll5 == SLListFindIntersection(sll0, sll7))
	{
		sll9->next = NULL;
		SLListDestroyList(sll0);
		SLListDestroyList(sll7);

		return (PASS);
	}

	SLListDestroyList(sll0);
	SLListDestroyList(sll7);

	return (FAIL);
}


int TestSLListHasIntersectionFalse()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);
	
	if (NULL == SLListFindIntersection(sll0, sll7))
	{
		SLListDestroyList(sll0);
		SLListDestroyList(sll7);

		return (PASS);
	}

	SLListDestroyList(sll0);
	SLListDestroyList(sll7);

	return (FAIL);
}


int TestSLListHasIntersectionSubList()
{
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
	
	sll_node_t *sll0 = SLListCreateNode(&i, NULL);
	sll_node_t *sll1 = SLListCreateNode(&j, NULL);
	sll_node_t *sll2 = SLListCreateNode(&k, NULL);
	sll_node_t *sll3 = SLListCreateNode(&l, NULL);
	sll_node_t *sll4 = SLListCreateNode(&m, NULL);
	sll_node_t *sll5 = SLListCreateNode(&n, NULL);
	sll_node_t *sll6 = SLListCreateNode(&o, NULL);
	sll_node_t *sll7 = SLListCreateNode(&p, NULL);
	sll_node_t *sll8 = SLListCreateNode(&q, NULL);
	sll_node_t *sll9 = SLListCreateNode(&r, NULL);

	SLListInsertAfter(sll0,sll1);
	SLListInsertAfter(sll1,sll2);
	SLListInsertAfter(sll2,sll3);
	SLListInsertAfter(sll3,sll4);
	SLListInsertAfter(sll4,sll5);
	SLListInsertAfter(sll5,sll6);
	
	SLListInsertAfter(sll7,sll8);
	SLListInsertAfter(sll8,sll9);
	
	if (NULL == SLListFindIntersection(sll0, sll5))
	{
		SLListDestroyList(sll0);
		SLListDestroyList(sll7);

		return (PASS);
	}

	SLListDestroyList(sll0);
	SLListDestroyList(sll7);

	return (FAIL);
}


/******************************************************************************/
/******************************************************************************/


int MatchFuncInts(const void *data, const void *param)
{
	return (*(int *)data == *(int *)param);
}


int ActionFuncIntAddition(const void *data, const void *param)
{
	if (50 == *(int *)data + *(int *)param)
	{
		return (1);
	}
	return (0);
}

void PrintLinkedList(sll_node_t *head)
{
	sll_node_t *runner = head;
	printf("the elements are: ");
	while (NULL != runner)
	{
		printf("%d ",*(int *)runner->data);
		runner = runner->next;
	}
	printf("\n");
}

int CheckArrays(int *arr1, int *arr2, int arr_size)
{
	int i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return (0);
		}
	}
	
	return (1);
}

