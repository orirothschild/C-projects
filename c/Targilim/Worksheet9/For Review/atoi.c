#include <stdio.h> /* print */
#include <string.h> /* strlen */
#include <ctype.h> /* isdigit */
#include <math.h> /* pow */
#include <assert.h> /* assert */

#define DIGIT 48
#define CHAR 55

int atoi(const char *nptr, int base);


int main()
{
	int j = 0;
	int base = 16;
	char *str = "4D2";
	
	j = atoi(str, base);
	
	printf("this is j %d\n", j);
	
	return (0);
}


int atoi(const char *nptr, int base) 
{
	int i = 0;
	int negative = 1;
	int len = strlen(nptr);
	int num = 0;
	int result = 0;
	
	assert(NULL != nptr);
	assert(0 < base && base < 37);
	assert(*nptr => 48 && *nptr <= 57 );
	assert(*nptr => 65 && *nptr <= 90 );
	assert(*nptr => 97 && *nptr <= 122 );
	
	if ('-' == *nptr)
	{
		negative = -1;
		++nptr;
		i = 1;
	}
	
	for (i = i; i < len; ++i)
	{
		if (0 != isdigit(*nptr))
		{
			num = *nptr - DIGIT;
		}
		else
		{
			num = toupper(*nptr) - CHAR;
		}
		
		num = num * pow(base, (len - 1) - i);
		result += num;
		++nptr;
	}
	
	result *= negative;
	
	return (result);
}
