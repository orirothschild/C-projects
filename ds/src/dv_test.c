#include <stdio.h> /* printf */
#include "dv.h" /* ADT */

#define RUN_TEST(test) (!test) ? printf("FAIL : " #test"\n" ) : printf("PASS : " #test"\n")

int TestDVectorCreate();
int TestDVectorSize1();
int TestDVectorSize2();
int TestDVectorSize3();
int TestDVectorCapacity1();
int TestDVectorCapacity2();
int TestDVectorCapacity3();
int TestDVectorGetItemAddress1();
int TestDVectorGetItemAddress2();
int TestDVectorPop1();
int TestDVectorPop2();
int TestDVectorPop3();
int TestDVectorReserve1();
int TestDVectorReserve2();

enum {FAIL, PASS};

int main()
{
	RUN_TEST(TestDVectorCreate());
	RUN_TEST(TestDVectorSize1());
	RUN_TEST(TestDVectorSize2());
	RUN_TEST(TestDVectorSize3());
	RUN_TEST(TestDVectorCapacity1());
	RUN_TEST(TestDVectorCapacity2());
	RUN_TEST(TestDVectorCapacity3());
	RUN_TEST(TestDVectorGetItemAddress1());
	RUN_TEST(TestDVectorGetItemAddress2());
	RUN_TEST(TestDVectorPop1());
	RUN_TEST(TestDVectorPop2());
	RUN_TEST(TestDVectorPop3());
	RUN_TEST(TestDVectorReserve1());
	RUN_TEST(TestDVectorReserve2());
	
/*	size_t i = 5;*/
/*	size_t j = 4;*/
/*		*/
/*	vector_t *dv = DVectorCreate(i, j);*/
/*	*/
/*	DVectorDestroy(dv);*/
	
	
	
	return (0);
}


int TestDVectorCreate()
{
	size_t i = 5;
	size_t j = 4;

	if (NULL != DVectorCreate(i, j))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorSize1()
{
	size_t i = 5;
	size_t j = 4;
	
	vector_t *dv = DVectorCreate(i, j);
	
	if (0 == DVectorSize(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorSize2()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	
	if (1 == DVectorSize(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorSize3()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);

	if (6 == DVectorSize(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorCapacity1()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	
	if (5 == DVectorCapacity(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorCapacity2()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	
	
	if (5 == DVectorCapacity(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorCapacity3()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	
	if (10 == DVectorCapacity(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorGetItemAddress1()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	
	if (3 == *(int *)DVectorGetItemAddress(dv, 0))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorGetItemAddress2()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	
	if (5 == *(int *)DVectorGetItemAddress(dv, 2))
	{
		return (PASS);
	}
	
	return (FAIL);
}



int TestDVectorPop1()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	
	DVectorPop(dv);
	
	if (5 == DVectorSize(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorPop2()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	int count = 0;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);

	count += *(int *)DVectorGetItemAddress(dv, 4);
	DVectorPop(dv);
	count += *(int *)DVectorGetItemAddress(dv, 3);
	DVectorPop(dv);
	count += *(int *)DVectorGetItemAddress(dv, 2);
	DVectorPop(dv);
	count += *(int *)DVectorGetItemAddress(dv, 1);
	DVectorPop(dv);
	count += *(int *)DVectorGetItemAddress(dv, 0);
	
	
	if (25 == count)
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorPop3()
{
	size_t i = 100;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	
	DVectorPop(dv);
	
	if (50 == DVectorCapacity(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorReserve1()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	
	DVectorReserve(dv, 20);
	
	if (20 == DVectorCapacity(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestDVectorReserve2()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	vector_t *dv = DVectorCreate(i, j);
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	++k;
	DVectorPush(dv, &k);
	
	DVectorReserve(dv, 4);
	
	if ((DVectorSize(dv)) == DVectorCapacity(dv))
	{
		return (PASS);
	}
	
	return (FAIL);
}


