#include <stdio.h> /* printf */
#include "stack.h" /* ADT */

#define RUN_TEST(test) (!test) ? printf("FAIL : " #test"\n" ) : printf("PASS : " #test"\n")

#define U_LONG_MAX 0xFFFFFFFFFFFFFFFF

int TestStackCreate();
int TestStackSize();
int TestStackPeek();
int TestStackPush();
int TestStackPushFail();
int TestStackPop();

enum {FAIL, PASS};



int main()
{
	RUN_TEST(TestStackCreate());
	RUN_TEST(TestStackSize());
	RUN_TEST(TestStackPeek());	
	RUN_TEST(TestStackPush());
	RUN_TEST(TestStackPushFail());
	RUN_TEST(TestStackPop());
	
/*	size_t i = 5;*/
/*	size_t j = 4;*/
/*		*/
/*	stack_t *st = StackCreate(i, j);*/
/*	*/
/*	StackDestroy(st);*/
	
	
	
	return (0);
}


int TestStackCreate()
{
	size_t i = 5;
	size_t j = 4;

	if (NULL != StackCreate(i, j))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestStackSize()
{
	size_t i = 5;
	size_t j = 4;
/*	int k = 3;*/
	
	Stack_t *st = StackCreate(i, j);
/*	StackPush(st, &k);*/
	
	if (0 == StackSize(st))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestStackPeek()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	Stack_t *st = StackCreate(i, j);
	StackPush(st, &k);
	
	if (3 == *((int *)StackPeek(st)))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestStackPush()
{
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	
	Stack_t *st = StackCreate(i, j);

	if (1 == StackPush(st, &k))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestStackPushFail()
{
	size_t i = 1;
	size_t j = 4;
	int k = 3;
	
	Stack_t *st = StackCreate(i, j);

	StackPush(st, &k);


	if (0 == StackPush(st, &k))
	{
		return (PASS);
	}
	
	return (FAIL);
}



int TestStackPop()
{
	size_t n = 0;
	size_t i = 5;
	size_t j = 4;
	int k = 3;
	int count = 0;
	
	Stack_t *st = StackCreate(i, j);
	StackPush(st, &k);
	++k;
	StackPush(st, &k);
	++k;
	StackPush(st, &k);
	++k;
	StackPush(st, &k);
	++k;
	StackPush(st, &k);
	
	for (n = 0; n < i; ++n)
	{
/*		printf("The element is: %d\n", *((int *)StackPeek(st)));*/
		count += *(int *)StackPeek(st);
		StackPop(st);
	}
	
	if (25 == count)
	{
		return (PASS);
	}
	
	return (FAIL);
}

