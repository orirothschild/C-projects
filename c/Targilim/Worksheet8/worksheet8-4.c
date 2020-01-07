#include <stdio.h>    /* printf */

#define SIZEOFVAR(X) (unsigned int)((char *)((&X) + 1) - (char *)(&X))
#define SIZEOFTYPE(X) (size_t)((X *)0 + 1)


int main()
{
	int i = 5;
	char c = 'h';
	short s = 1;
	double d = 17;
	
	struct bob
	{
		int z[10];
		int a[20];
		int b;
	};
		
	printf("The size of s is: %d\n",SIZEOFVAR(s));
	
	printf("the size of a double is: %d\n", (int)SIZEOFTYPE(double));

	return (0);
}
