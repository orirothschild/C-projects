#include <stdio.h>

#include "b.h"
#include "a.h"

int FooInB()
{
	printf("Inside B oh boy\n");

    FooInA();

	return 0;
}