#include <stdio.h>



int power(int x)
{
    int i;
	long double d = 1;
	double e = x;	

	if (x < 0)
	{
		x = -x;
	}	
	
	for (i = 0; i < x; i++)
	{
		d *= 10;
	}
	
	if (e < 0)
	{
		d = 1 / d;
	}

    printf("for x = %d, the power is %Le\n",x,d);
    return 0;

}

int main()
{
    int z = -3;
    power(z);    
    return 0;
}


