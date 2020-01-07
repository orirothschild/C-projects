#include <stdio.h>


int flipint(int x)
{
	int y = 0;
	int temp = x;

	while (temp / 10)
	{
		y = y + temp % 10;
		y *= 10;
		temp /= 10;
	}
	y += temp;

	printf("for input x = %d, the reverse is %d\n",x,y);

	return 0;

}



int main()
{
	int z = 345678;

	flipint(z);

	return 0;
}
