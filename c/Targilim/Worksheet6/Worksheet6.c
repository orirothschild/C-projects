#include <stdio.h> /*printf*/
#include <assert.h> /* assert */

#define UINT_MAX 2147483648
#define BITS 32

int BitAddition(unsigned int x, int y);
double Pow2(unsigned int x, int y);
int IsPowerOfTwoLoop(unsigned int n);
int IsPowerOfTwoNoLoop(unsigned int n);
void ThreeBitsOnOne(unsigned int *array, int arr_size);
void ByteMirror(unsigned int num);
void ByteMirrorLoop(unsigned int num);
int FunctionTwo(unsigned char num);
int FunctionOne(unsigned char num);
int FunctionThree(unsigned char num);
int ClosestDivider(unsigned int num);
void SwapTwoVars(unsigned int x, unsigned int y);
int CountSetBitsLoop(unsigned int num);
int CountSetBits(unsigned int num);
void PrintFloatBits(float f);



int main()
{

/*	double d = 32;
	double d2 = -2;
	double d3 = 0;
	d3 = pow2(d,d2);

	printf("%f * 2^%f is: %f \n", d, d2, d3);
*/	
	
/*
	unsigned int i = 255;
	int result = 0;
	result = IsPowerOfTwoLoop(i);
	if (1 == result)
	{
		printf("%u is a power of 2\n", i);
	}
	else
	{
		printf("%u is not a power of 2\n", i);
	}
*/	

/*
	unsigned int uint_array[3] = {5, 7, 1};
	ThreeBitsOnOne(uint_array, 3);
*/
/*
	unsigned int num = 9;
	ByteMirror(num);
	ByteMirrorLoop(num);
*/
/*
	unsigned char c = 'S';    S = 0101 0011
						should be 0100 0111 which 71
	int x = 0;
	int y = 0;
*/

/*	x = FunctionOne(c);
	printf("x was %d\n", x);
	0 0 1 1 1 1 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 1 1 1 1 1 

	
	x = FunctionTwo(c);
	printf("x was %d\n", x);
*/	

/*
	printf("c was %d\n", c);
	x = FunctionThree(c);
	printf("x was %d\n", x);
	y = FunctionThree(c);
	printf("y was %d\n", y);
*/

/*	
	int x = 0;
	int y = 31;
	x = ClosestDivider(y);
	printf("x was %d\n", x);
*/


/*	unsigned int x = 0;
	unsigned int y = 7;   */
/*	x = CountSetBitsLoop(y);
	printf("x was %d\n", x);
*/

/*
	SwapTwoVars(x, y);	
*/

/*	
	x = CountSetBits(y);
	printf("x was %d\n", x);
*/

/*
	float f = 5;
	float *fp = &f;
	PrintFloatBits(f);
*/

	unsigned int x = 7;
	int y = 1;
	printf("the number is: %u\n", x);
	y = BitAddition(x, y);
	printf("the number is: %u\n", y);


	return (0);
}



/* Functions */
double Pow2(unsigned int x, int y)
{
	double z = 0;
	
	if (y < 0)
	{
		y = ~y;
		z = x >> (y + 1);
	}
	else
	{
		z = x << y;
	}

	return (z);
}


int IsPowerOfTwoLoop(unsigned int n)
{
	unsigned int mask = 1;

	do
	{
		if (mask == (n | mask))
		{
			return (1);
		}
		mask <<= 1;
	}
	while (mask < UINT_MAX);
	
	return (0);
}


int IsPowerOfTwoNoLoop(unsigned int n)
{
	if (0 == (n & (n - 1)))
	{
		return (1);
	}

	return (0);
}


/* addition by columns */
int BitAddition(unsigned int x, int y)
{
	int carry = 0;
	
	assert(y >= 0);
	
	while (y != 0)
	{

		/* the carry over to the next digit */
		carry = x & y;
		
		/* x is now the digit that is left after the addition of the 
		current column */
		x = x ^ y;
		
		/* move the carry over to the next column */
		y = carry << 1;
	}
	
	return (x);
}

unsigned int AddOne(unsigned int x)
{
	unsigned int mask = 1;
	while (x & mask)
	{
		x = x ^ mask;
		mask <<= 1;
	}

	x = x ^ mask;
	
	return (x);
}

void ThreeBitsOnOne(unsigned int *array, int arr_size)
{
	int i = 0;
	unsigned int mask = 1;
	int counter = 0;
	
	assert(arr_size >= 0);

	for (i = 0; i < arr_size; ++i)
	{
		mask = 1;
		counter = 0;
		do
		{
			if (mask == (array[i] & mask))
			{
				++counter;
			}
			mask  <<= 1;	
		}
		while (mask < BITS);
		
		if (3 == counter)
		{
			printf("%u in array[%d] has 3 or more bits on '1'\n", array[i], i );
		}
	}	
}


void ByteMirror(unsigned int num)
{
	printf("the num is %u\n", num);


	num = num >> 16 | num << 16;

	/* shift each side after using a mask by goups of 8 */
	num = (num & 0xFF00FF00) >> 8 | (num & 0x00FF00FF) << 8;

	
	/* shift each side after using a mask by goups of 4 */
	num = (num & 0xF0F0F0F0) >> 4 | (num & 0x0F0F0F0F) << 4;
	
	
	/* shift each side after using a mask by goups of 2 */
	num = (num & 0xCCCCCCCC) >> 2 | (num & 0x33333333) << 2;
	
	
	/* shift each side after using a mask by goups of 1 */
	num = (num & 0xAAAAAAAA) >> 1 | (num & 0x55555555) << 1;
	
	
	printf("the num is %u\n", num);	
}


void ByteMirrorLoop(unsigned int num)
{
	unsigned int mask = 1;
	unsigned int mirror = 0;
	int i = 0;
	
	printf("The number is: %u\n", num);
	
	/* for each bit, check against a mask, if it is set, add 1 to the beginning */
	for (i = 0; i < BITS; ++i)
	{
		if ((mask & num) == mask)
		{
			mirror = mirror ^ (mask >> i);
		}
		
		mask <<= 1;
		mirror <<= 1;
	}
	
	printf("The mirror of the number is: %u\n", mirror);
}


/* No if, receive unsigned char, return true if bits 2 and 6 set */
int FunctionOne(unsigned char num)
{
	unsigned int mask6 = 0x00000020;
	unsigned int mask2 = 0x00000002;
	unsigned int temp6 = (mask6 & num);
	unsigned int temp2 = (mask2 & num);
	
	return (temp6 && temp2);
}

/* No if, receive unsigned char, return true if bits 2 or 6 set */
int FunctionTwo(unsigned char num)
{	
	unsigned int mask6 = 0x00000020;
	unsigned int mask2 = 0x00000002;
	unsigned int temp2 = (mask2 & num);
	unsigned int temp6 = (mask6 & num);
	
	return (temp6 || temp2);
}

/* No if, receive unsigned char, switch bits 3 and 5 */
int FunctionThree(unsigned char num)
{
	unsigned char mask_num = 0;
	unsigned char temp = 0;
	unsigned char temp2 = 0;
	
	/* combine results of mask5 and mask3 after moving them */
	temp = ((num & 0x10) >> 2 | (num & 0x04) << 2);
	
	/* mask for the given num where 3 and 5 are 0's */
	mask_num = 0xEB;
	
	temp2 = mask_num & num;
	
	return ((temp | temp2));
}


/* if equal then return the runner. It it's next multiple of 2 is bigger than 
the input, then that means the closest multiple of 16 is the previous multipe */
int ClosestDivider(unsigned int num)
{
	unsigned int div = 16;
	
	while (div <= num)
	{	
		if ((num == div) || ((div << 1) > num))
		{
			return (div);
		}
		
		div <<= 1;
	}

	return (0);
}


/* comments as an example */
void SwapTwoVars(unsigned int x, unsigned int y)
{

	printf("x is %u, y is %u\n", x, y);
	/* x = 1010, y = 1111 */
	/* x -> 0101 */
	/* y -> 1010 */
	/* x -> 1111 */
	
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
	
	printf("x is %u, y is %u\n", x, y);
}


int CountSetBitsLoop(unsigned int num)
{
	unsigned int counter = 0;
	int i = 0;
	unsigned int mask = 1;
	
	do
	{
		if (mask == (mask & num))
		{
			++counter;
		}
		++i;
		mask <<= 1;
	}
	while (i < BITS);

	return (counter);
}

/* Using Hamming Weight algorithm to count set bits*/
int CountSetBits(unsigned int num)
{
	unsigned int b0  = 0;
	unsigned int b1  = 0;
	unsigned int c   = 0;
	unsigned int d0  = 0;
	unsigned int d2  = 0;
	unsigned int e   = 0;
	unsigned int f0  = 0;
	unsigned int f4  = 0;
	unsigned int g   = 0;
	unsigned int h0  = 0;
	unsigned int h8  = 0;
	unsigned int i   = 0;
	unsigned int j0  = 0;
	unsigned int j16 = 0;
	unsigned int k   = 0;

	/* mask half the bits, them mask the other half. 
	c is the 'count' of the number bits set in the 2 places checked. */
	b0 = (num >> 0) & 0x55555555;
	b1 = (num >> 1) & 0x55555555;
	c = b0 + b1;
	
	/* mask half the bits, them mask the other half.
	e is the 'count' of the number bits set in the 4 places checked. */
	d0 = (c >> 0) & 0x33333333;
	d2 = (c >> 2) & 0x33333333;
	e = d0 + d2;
	
	/* mask half the bits, them mask the other half.
	g is the 'count' of the number bits set in the 8 places checked. */
	f0 = (e >> 0) & 0x0F0F0F0F;
	f4 = (e >> 4) & 0x0F0F0F0F;
	g = f0 + f4;
	
	/* mask half the bits, them mask the other half.
	i is the 'count' of the number bits set in the 16 places checked. */
	h0 = (g >> 0) & 0x00FF00FF;
	h8 = (g >> 8) & 0x00FF00FF;
	i = h0 + h8;
	
	/* mask half the bits, them mask the other half.
	k is the 'count' of the number bits set in the 32 places checked. */
	j0 = (i >> 0)   & 0x0000FFFF;
	j16 = (i >> 16) & 0x0000FFFF;
	k = j0 + j16;

	return (k);
}


void PrintFloatBits(float f)
{
	float *fp = &f;
	int *pointer = (int *)fp;
	int i = 0;
	unsigned int mask = 0x80000000;

	assert(NULL != F);
	
	do 
	{
		if (mask == (*pointer & mask))
		{
			printf("1 ");
		}
		else
		{
			printf("0 ");
		}
		mask >>= 1;
		++i;
	}
	while (i < BITS);

	printf("\n");
}

