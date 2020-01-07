#include <stdio.h>


int main()
{
	int x = 20, y = 35;
	printf("x is %d, y is %d\n", x, y);
	x = y++ + x++;
	printf("x is %d, y is %d\n", x, y);
	y = ++y + ++x;
	printf("x is %d, y is %d\n", x, y);
	return 0;


}
