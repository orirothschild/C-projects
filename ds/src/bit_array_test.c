#include <stdio.h> /* printf */
#include "bit_array.h" /* ADT */

#define RUN_TEST(test) (!test) ? printf("FAIL : " #test"\n" ) : printf("PASS : " #test"\n")

#define U_LONG_MAX 0xFFFFFFFFFFFFFFFF


enum {FAIL, PASS};

int TestBArrIsBitOnIdxOneTrue();
int TestBArrIsBitOnIdxLastTrue();
int TestBArrIsBitOnIdxFiveTrue();
int TestBArrIsBitOnIdxOneFalse();
int TestBArrIsBitOffIdxOneTrue();
int TestBArrIsBitOffIdxOneFalse();
int TestBArrCountBitsOn();
int TestBArrCountBitsOnFast();
int TestBArrCountBitsOff();
int TestBArrSetBitOn();
int TestBArrSetBitOff();
int TestBArrGetBitArrayOn();
int TestBArrGetBitArrayOff();
int TestBArrAreAllBitsOnTrue();
int TestBArrAreAllBitsOnFalse();
int TestBArrAreAllBitsOffTrue();
int TestBArrAreAllBitsOffFalse();
int TestBArrFlipOneBit();
int TestBArrFlipAllBits();
int TestBArrRotateBitsRight();
int TestBArrRotateBitsLeft();
int TestBArrRotateBitsLeftTwo();
int TestBArrMirrorBitArr();
int TestBArrMirrorBitArrFast1();
int TestBArrMirrorBitArrFast2();

int main()
{
	RUN_TEST(TestBArrIsBitOnIdxOneTrue());
	RUN_TEST(TestBArrIsBitOnIdxLastTrue());
	RUN_TEST(TestBArrIsBitOnIdxFiveTrue());
	RUN_TEST(TestBArrIsBitOnIdxOneFalse());
	RUN_TEST(TestBArrIsBitOffIdxOneTrue());
	RUN_TEST(TestBArrIsBitOffIdxOneFalse());
	RUN_TEST(TestBArrCountBitsOn());
	RUN_TEST(TestBArrCountBitsOnFast());
	RUN_TEST(TestBArrCountBitsOff());
	RUN_TEST(TestBArrSetBitOn());
	RUN_TEST(TestBArrSetBitOff());
	RUN_TEST(TestBArrGetBitArrayOn());
	RUN_TEST(TestBArrGetBitArrayOff());
	RUN_TEST(TestBArrAreAllBitsOnTrue());
	RUN_TEST(TestBArrAreAllBitsOnFalse());
	RUN_TEST(TestBArrAreAllBitsOffTrue());
	RUN_TEST(TestBArrAreAllBitsOffFalse());
	RUN_TEST(TestBArrFlipOneBit());
	RUN_TEST(TestBArrFlipAllBits());
	RUN_TEST(TestBArrRotateBitsRight());
	RUN_TEST(TestBArrRotateBitsLeft());
	RUN_TEST(TestBArrRotateBitsLeftTwo());
	RUN_TEST(TestBArrMirrorBitArr());
	RUN_TEST(TestBArrMirrorBitArrFast1());
	RUN_TEST(TestBArrMirrorBitArrFast2());

	return (0);
}


int TestBArrIsBitOnIdxOneTrue()
{
	unsigned long bit_arr = 0x0000000000000001;
	int idx = 0;

	if (1 == BArrIsBitOn(bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrIsBitOnIdxLastTrue()
{
	unsigned long bit_arr = 0x8000000000000000;
	int idx = 63;

	if (1 == BArrIsBitOn(bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrIsBitOnIdxFiveTrue()
{
	unsigned long bit_arr = 0x0000000000000010;
	int idx = 4;

	if (1 == BArrIsBitOn(bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrIsBitOnIdxOneFalse()
{
	unsigned long bit_arr = 0x0000000000000000;
	int idx = 1;

	if (0 == BArrIsBitOn( bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrIsBitOffIdxOneTrue()
{
	unsigned long bit_arr = 0x0000000000000000;
	int idx = 1;
	
	if (1 == BArrIsBitOff(bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrIsBitOffIdxOneFalse()
{
	unsigned long bit_arr = 0x0000000000000001;
	int idx = 0;
	
	if (0 == BArrIsBitOff(bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrCountBitsOn()
{
	unsigned long bit_arr = 0x0001001000010000;
	
	if (3 == BArrCountBitsOn(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrCountBitsOnFast()
{
	unsigned long bit_arr = 0x0001001000010000;
	
	if (3 == BArrCountBitsOnFast(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrCountBitsOff()
{
	unsigned long bit_arr = 0x0001001000010000;
	
	if (61 == BArrCountBitsOff(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrSetBitOn()
{
	unsigned long bit_arr = 0x0000000000000000;
	int idx = 1;
	
	if (2 == BArrSetBitOn(bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrSetBitOff()
{
	unsigned long bit_arr = 0x0000000000000001;
	int idx = 0;
	
	if (0 == BArrSetBitOff(bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrGetBitArrayOn()
{
	if (U_LONG_MAX == BArrGetBitArrayOn())
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrGetBitArrayOff()
{
	if (0 == BArrGetBitArrayOff())
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrAreAllBitsOnTrue()
{
	unsigned long bit_arr = 0xFFFFFFFFFFFFFFFF;
	
	if (1 == BArrAreAllBitsOn(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrAreAllBitsOnFalse()
{
	unsigned long bit_arr = 0x1111111011111111;
	
	if (0 == BArrAreAllBitsOn(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}
int TestBArrAreAllBitsOffTrue()
{
	unsigned long bit_arr = 0x0000000000000000;
	
	if (1 == BArrAreAllBitsOff(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrAreAllBitsOffFalse()
{
	unsigned long bit_arr = 0x0000000010000000;
	
	if (0 == BArrAreAllBitsOff(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrFlipOneBit()
{
	unsigned long bit_arr = 0x0000000000000001;
	int idx = 0;

	if (0 == BArrFlipOneBit(bit_arr, idx))
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrFlipAllBits()
{
	unsigned long bit_arr = 0xFFFFFFFFFFFFFFFF;

	if (0 == BArrFlipAllBits(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrRotateBitsRight()
{
	unsigned long bit_arr = 0x0000000000000001;
	
	if (0x8000000000000000 == BArrRotateBitsRight(bit_arr, 1))
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrRotateBitsLeft()
{
	unsigned long bit_arr = 0x8000000000000000;
	
	if (0x0000000000000001 == BArrRotateBitsLeft(bit_arr, 1))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrRotateBitsLeftTwo()
{
	unsigned long bit_arr = 0xC000000000000000;
	
	if (0x0000000000000003 == BArrRotateBitsLeft(bit_arr, 2))
	{
		return (PASS);
	}
	
	return (FAIL);
}


int TestBArrMirrorBitArr()
{
	unsigned long bit_arr = 0x0000000000000001;

	if (0x8000000000000000 == BArrMirrorBitArr(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);
}

int TestBArrMirrorBitArrFast1()
{	
	unsigned long bit_arr = 0x0000000000000001;

	if (0x8000000000000000 == BArrMirrorBitArrFast(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);	
}


int TestBArrMirrorBitArrFast2()
{	
	unsigned long bit_arr = 0x8000000000000000;

	if (0x0000000000000001 == BArrMirrorBitArrFast(bit_arr))
	{
		return (PASS);
	}
	
	return (FAIL);	
}


