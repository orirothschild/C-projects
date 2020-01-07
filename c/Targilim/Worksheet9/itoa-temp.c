#include <stdio.h> /* print */
#include <stdlib.h> /* absolute */

#define ARR_SIZE 36
#define MAX_SIZE 32
#define NEG 34

char *itoa(int num, int base, char *result_arr);

static const char LUT[ARR_SIZE] = {'0', '1', '2', '3','4', '5', '6', '7', '8', '9',
					  'A', 'B', 'C', 'D','E', 'F', 'G', 'H', 'I', 'J',
					  'K', 'L', 'M', 'N','O', 'P', 'Q', 'R', 'S', 'T',
					  'U', 'X', 'Y', 'Z', '-'};


int main()
{
	int i = 1234;
	int base = 10;
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
/*	ReverseArray(reverse_arr, temp_arr);*/
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


/*void ReverseArray( , , int counter)*/
/*{*/
/*	int i = 0;*/
/*	*/
/*	for (i = 0; i < counter; ++i)*/
/*	{*/
/*		*(reverse_arr + i) = temp_arr[(counter - 1) - i];*/
/*	}*/

/*}*/


/* for watchdog */
/* static char *itoa(int num, int base, char *result_arr)
{
	int i = 0;
	int j = 0;
	int number = num;
	char *temp_arr = {0};
	char *reverse_arr = {0};
	int counter = 0;
	int digits = 0;

    do
    {
        ++digits;
    }
    while (number /= 10);
    number = num;
    
    temp_arr = malloc();

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
} */