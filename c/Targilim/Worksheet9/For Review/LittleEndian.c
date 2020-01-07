#include <stdio.h>

#define ENDIANESS() (*(short *)"\1") ? printf("Little\n") : printf("Big\n")

int IsLittleEndian(int i);

int main()
{
	int i = 5;
	char c = IsLittleEndian(i);
			
	if (1 == c)
	{
		printf("Little endian\n");
	}
	else
	{
		printf("Big Endian\n");
	}
	
	ENDIANESS();
		
	return (0);
}


int IsLittleEndian(int i)
{
	int j = i/i;
	
	return (*(char *)&j);
}




/*

	For myself:
	j = 1, meanining 0000 0000 0000 0001
	if the system is big endian, the most signigicant (meaning the biggest)
	numbers would be at the beginning of the representation (on the leftmost side).
	If the system is little endian, the most significant numbers would be on the rightmost
	side.
	Thats why we check if c == 1. if it is, it means that the 0001 is on the leftmost side.
	 

*/
