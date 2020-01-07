#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "bit_array.h" /* ADT */

/* #define U_LONG_MAX = 18,446,744,073,709,551,615 */
static const unsigned long U_LONG_MAX = 0xFFFFFFFFFFFFFFFF;
static const unsigned long U_LONG_MIN = 0x0000000000000000;
static int MAX_IDX = 63;
static int MIN_IDX = 0;
static int NUM_OF_BITS = 64;
static int BYTES = 8;
static int BYTE = 8;
static int ROTATE_BOUND = 64;
static int ZERO = 48;

enum {False, True};

static unsigned long BArrIndexMaskBuilder(int index);

const char LUT_set_bits[256] = {'0', '1', '1', '2', '1', '2', '2', '3', '1', '2'
, '2','3', '2', '3', '3', '4', '1', '2', '2', '3', '2', '3', '3', '4', '2', '3',
 '3', '4', '3', '4', '4', '5', '1', '2', '2', '3', '2', '3', '3', '4', '2', '3',
 '3', '4', '3', '4', '4', '5', '2', '3', '3', '4', '3', '4', '4', '5', '3', '4',
 '4', '5', '4', '5', '5', '6', '1', '2', '2', '3', '2', '3', '3', '4', '2', '3',
 '3', '4', '3', '4', '4', '5', '2', '3', '3', '4', '3', '4', '4', '5', '3', '4',
 '4', '5', '4', '5', '5', '6', '2', '3', '3', '4', '3', '4', '4', '5', '3', '4',
 '4', '5', '4', '5', '5', '6', '3', '4', '4', '5', '4', '5', '5', '6', '4', '5',
 '5', '6', '5', '6', '6', '7', '1', '2', '2', '3', '2', '3', '3', '4', '2', '3',
 '3', '4', '3', '4', '4', '5', '2', '3', '3', '4', '3', '4', '4', '5', '3', '4',
 '4', '5', '4', '5', '5', '6', '2', '3', '3', '4', '3', '4', '4', '5', '3', '4',
 '4', '5', '4', '5', '5', '6', '3', '4', '4', '5', '4', '5', '5', '6', '4', '5',
 '5', '6', '5', '6', '6', '7', '2', '3', '3', '4', '3', '4', '4', '5', '3', '4',
 '4', '5', '4', '5', '5', '6', '3', '4', '4', '5', '4', '5', '5', '6', '4', '5',
 '5', '6', '5', '6', '6', '7', '3', '4', '4', '5', '4', '5', '5', '6', '4', '5',
 '5', '6', '5', '6', '6', '7', '4', '5', '5', '6', '5', '6', '6', '7', '5', '6',
 '6', '7', '6', '7', '7', '8'};

const unsigned char LUT_num[256] = {0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 
80, 208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 
216, 56, 184, 120, 248, 4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 
52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 
188, 124, 252, 2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 
114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 
250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246, 
14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254, 1, 
129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241, 9, 137, 73,
201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249, 5, 133, 69, 197, 
37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245, 13, 141, 77, 205, 45, 
173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253, 3, 131, 67, 195, 35, 163, 
99, 227, 19, 147, 83, 211, 51, 179, 115, 243, 11, 139, 75, 203, 43, 171, 107, 
235, 27, 155, 91, 219, 59, 187, 123, 251, 7, 135, 71, 199, 39, 167, 103, 231, 
23, 151, 87, 215, 55, 183, 119, 247, 15, 143, 79, 207, 47, 175, 111, 239, 31, 
159, 95, 223, 63, 191, 127, 255};

int BArrIsBitOn(unsigned long bit_arr, int idx)
{
	unsigned long mask  = BArrIndexMaskBuilder(idx);
		
	assert(idx >= MIN_IDX && idx <= MAX_IDX);
	
	if (mask == (bit_arr & mask))
	{
		return (True);
	}
	return (False);
}

int BArrIsBitOff(unsigned long bit_arr, int idx)
{
	unsigned long mask = BArrIndexMaskBuilder(idx);
	
	assert(idx >= MIN_IDX && idx <= MAX_IDX);
	
	if (mask != (bit_arr & mask))
	{
		return (True);
	}
	return (False);
}


int BArrCountBitsOnFast(unsigned long bit_arr)
{
	int result = 0;
	int i = 0;
	unsigned long mask = 0x00000000000000FF;
	unsigned int byte = 0x00000000;
	
	for (i = 0; i < BYTES; ++i)
	{
		byte = LUT_set_bits[(bit_arr >> (i * BYTE))  & mask] - ZERO;
		result += byte;
	}
	
	return (result);
}

int BArrCountBitsOn(unsigned long bit_arr)
{
	int result = 0;
	
	bit_arr = (((bit_arr >> 0)  & 0x5555555555555555) + 
			   ((bit_arr >> 1)  & 0x5555555555555555));
	
	bit_arr = (((bit_arr >> 0)  & 0x3333333333333333) +
			   ((bit_arr >> 2)  & 0x3333333333333333));
			  
	bit_arr = (((bit_arr >> 0)  & 0x0F0F0F0F0F0F0F0F) +
			   ((bit_arr >> 4)  & 0x0F0F0F0F0F0F0F0F));
	
	bit_arr = (((bit_arr >> 0)  & 0x00FF00FF00FF00FF) +
			   ((bit_arr >> 8)  & 0x00FF00FF00FF00FF));
			  
	bit_arr = (((bit_arr >> 0)  & 0x0000FFFF0000FFFF) +
			   ((bit_arr >> 16) & 0x0000FFFF0000FFFF));		  

	bit_arr = (((bit_arr >> 0)  & 0x00000000FFFFFFFF) + 
			   ((bit_arr >> 32) & 0x00000000FFFFFFFF));

	result = (int)bit_arr;

	return (result);
}


int BArrCountBitsOff(unsigned long bit_arr)
{
	int result = BArrCountBitsOn(bit_arr);
	
	result = NUM_OF_BITS - result;
	
	return (result); 
}


unsigned long BArrSetBitOn(unsigned long bit_arr, int idx)
{
	unsigned long mask = BArrIndexMaskBuilder(idx);
	
	assert(idx >= MIN_IDX && idx <= MAX_IDX);
	
	bit_arr = bit_arr | mask;
	
	return (bit_arr);
}


unsigned long BArrSetBitOff(unsigned long bit_arr, int idx)
{
	unsigned long mask = BArrIndexMaskBuilder(idx);
	
	assert(idx >= MIN_IDX && idx <= MAX_IDX);
	
	bit_arr = bit_arr & ~mask;
	
	return (bit_arr);
}


unsigned long BArrGetBitArrayOn()
{
	return (U_LONG_MAX);
}


unsigned long BArrGetBitArrayOff()
{
	return (U_LONG_MIN);
}


int BArrAreAllBitsOn(unsigned long bit_arr)
{
	if (U_LONG_MAX == bit_arr)
	{
		return (True);
	}
	
	return (False);
}


int BArrAreAllBitsOff(unsigned long bit_arr)
{
	if (U_LONG_MIN == bit_arr)
	{
		return (True);
	}
	
	return (False);
}


unsigned long BArrFlipOneBit(unsigned long bit_arr, int idx)
{
	unsigned long mask = BArrIndexMaskBuilder(idx);
	
	assert(idx >= MIN_IDX && idx <= MAX_IDX);
	
	bit_arr = bit_arr ^ mask;
	
	return (bit_arr);
}


unsigned long BArrFlipAllBits(unsigned long bit_arr)
{
	return (~bit_arr);
}


unsigned long BArrRotateBitsRight(unsigned long bit_arr, int rot_time)
{
	int i = 0;
	unsigned long temp = 0ul;
	unsigned long mask = 0x0000000000000001;
	
	assert(rot_time >= 0);
	
	rot_time = rot_time % ROTATE_BOUND;
	
	for (i = 0; i < rot_time; ++i)
	{
		temp = 0ul;
		if (mask == (bit_arr & mask))
		{
			temp = 0x8000000000000000;
		}
		bit_arr = bit_arr >> 1;
		bit_arr = bit_arr ^ temp;
	}
	
	return (bit_arr);
}


unsigned long BArrRotateBitsLeft(unsigned long bit_arr, int rot_time)
{
	int i = 0;
	unsigned long temp = 0ul;
	unsigned long mask = 0x8000000000000000;
	
	assert(rot_time >= 0);
	
	rot_time = rot_time % ROTATE_BOUND;
	
	for (i = 0; i < rot_time; ++i)
	{
		temp = 0ul;
		if (mask == (bit_arr & mask))
		{
			temp = 0x0000000000000001;
		}
		bit_arr = bit_arr << 1;
		bit_arr = bit_arr ^ temp;
	}
	
	return (bit_arr);
}


unsigned long BArrMirrorBitArr(unsigned long bit_arr)
{

	bit_arr = ((bit_arr & 0xFFFFFFFF00000000) >> 32 |
			   (bit_arr & 0x00000000FFFFFFFF) << 32);
	
	bit_arr = ((bit_arr & 0xFFFF0000FFFF0000) >> 16 |
			   (bit_arr & 0x0000FFFF0000FFFF) << 16);
	
	bit_arr = ((bit_arr & 0xFF00FF00FF00FF00) >> 8 |
			   (bit_arr & 0x00FF00FF00FF00FF) << 8);
	
	bit_arr = ((bit_arr & 0xF0F0F0F0F0F0F0F0) >> 4 |
			   (bit_arr & 0x0F0F0F0F0F0F0F0F) << 4);
	
	bit_arr = ((bit_arr & 0xCCCCCCCCCCCCCCCC) >> 2 |
			   (bit_arr & 0x3333333333333333) << 2);		   
	
	bit_arr = ((bit_arr & 0xAAAAAAAAAAAAAAAA) >> 1 |
			   (bit_arr & 0x5555555555555555) << 1);		   
			   
	return (bit_arr);		   
			   
}


unsigned long BArrMirrorBitArrFast(unsigned long bit_arr)
{
	unsigned long result = 0ul;
	unsigned long mask = 0x00000000000000FF;
	int i = 0;
	unsigned char byte = 0;

	for (i = 0; i < BYTES; ++i)
	{
		byte = LUT_num[(bit_arr >> (i * BYTE)) & mask];
		result += byte;
		if (i != BYTES - 1)
		{
			result <<= BYTE;
		}
	}
	
	return (result);
}


static unsigned long BArrIndexMaskBuilder(int idx)
{
	unsigned long index = 1ul << idx;
/*	idx = 1 << idx;*/
		
	return (index);
}


