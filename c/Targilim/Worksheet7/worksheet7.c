#include <stdio.h>
#include "helper.h"

static int x = 2;


int main()
{

	int y = x + 2;
	char str3[] = "whatever";
	printf("the string was: %s\n", str3);
	
	*(str3 + 1) = 'a';	
	printf("the string was: %s\n", str3);
	
	return (0);
}
