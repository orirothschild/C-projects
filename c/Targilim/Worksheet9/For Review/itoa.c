#include <stdio.h> /* print */
#include <stdlib.h> /* absolute */

#define ARR_SIZE 36
#define MAX_SIZE 32

char *itoa(int num, int base, char *result_arr);

static const char LUT[ARR_SIZE] = {'0', '1', '2', '3','4', '5', '6', '7', '8', '9',
					  			   'A', 'B', 'C', 'D','E', 'F', 'G', 'H', 'I', 'J',
								   'K', 'L', 'M', 'N','O', 'P', 'Q', 'R', 'S', 'T',
								   'U', 'X', 'Y', 'Z', '-'};


int main()
{
	int i = 1234;
	int base = 16;
	char result_arr[MAX_SIZE + 1] = {0};
	char *return_str = NULL;
	
	printf("the number was: %d\n", i);

	return_str = itoa(i, base, result_arr);

	printf("The number was: %s\n", return_str);

	return (0);
}


char *itoa(int num, int base, char *result_arr)
{
	int i = 0;
	int j = 0;
	int number = num;
	char temp_arr[MAX_SIZE] = {0};
	char reverse_arr[MAX_SIZE] = {0};
	int counter = 0;
	
	while (num)
	{
		temp_arr[i] = LUT[abs(num) % base];
		num /= base;
		++i;
		++counter;
	}

	for (i = 0; i < counter; ++i)
	{
		*(reverse_arr + i) = temp_arr[(counter - 1) - i];
	}
	
	if (0 > number)
	{
		i = 0;
		result_arr[i] = '-';
		j = i + 1;		
	}
	
	for (i = 0; i < counter; ++i)
	{
		result_arr[j] = reverse_arr[i];
		++j;
	}
	
	result_arr[counter + 1] = '\0';

	return (result_arr);
}
