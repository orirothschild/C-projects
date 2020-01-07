#include <stdio.h>

int SwapTwoVars(int *x, int *y)
{
	int temp;
	printf("a is %d, z is %d\n", *x, *y);

	temp = *x;
	*x = *y;
	*y = temp;

	printf("a is %d, z is %d\n", *x, *y);
	
	return 0;
}




int main()
{
	int z = 12, a = 34;
	int *z_ptr = &z;
	int *a_ptr = &a;
	SwapTwoVars(z_ptr, a_ptr);
	return 0;
}
