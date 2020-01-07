#include <stdio.h>


int main()
{
	size_t y = 0;
	
	/* should be 8*/
	union numbers
	{
		int i;
		float f;
		double d;
	};
	
	/* should be 18 or 24 because of the stride address*/
	struct x
	{
		int i;
		char c;
		double d;
		short s;
	};
	
	/* should be 6 or 8*/
	struct card
	{
		unsigned int suit : 2;
		unsigned int face_value : 4;
	};

	printf("The size of a char is %lu\n", sizeof(char));
	printf("The size of a short is %lu\n", sizeof(short));
	printf("The size of a int is %lu\n", sizeof(unsigned int));
	printf("The size of a double is %lu\n", sizeof(double));
	printf("The size of a float is %lu\n", sizeof(float));
	printf("The size of a pointer is %lu\n", sizeof(void *));

	union numbers num;
	struct x bob;
	struct card g;
	printf("The size of numbers is %lu\n", sizeof(num));
	printf("The size of x is %lu\n", sizeof(bob));
	printf("The size of card is %lu\n", sizeof(g));

	/*y = sizeof(); */
}



/*

char 1
short 2
int 4
float 4
double 8 
pointer 8





*/
