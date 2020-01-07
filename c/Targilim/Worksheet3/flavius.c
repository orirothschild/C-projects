#include <stdio.h>  /* standard */
#include <string.h> /* strlen */

#define ARR_SIZE 6
#define ALIVE 1
#define DEAD 0

int StrToInt(char *str);
int MovePtr(int *int_arr, int ptr, int arr_size);
void InitArray(int *int_arr);


int main(int argc, char **argv)
{

/*	char *arr_size_arg_str = argv[1];   */
	int arr_size = ARR_SIZE;
	int int_arr[ARR_SIZE] = {1};
	int killer = 0;
	int lucky = 0;
	
	
	/* initialize array with 1, because C is annoying */
	InitArray(int_arr);
	
	
	while (ALIVE)
	{
		
		while (DEAD != int_arr[killer])
		{
			
			killer = MovePtr(int_arr, killer, arr_size);
						
			if (ALIVE == int_arr[killer])
			{
				int_arr[killer] = DEAD;
				killer = MovePtr(int_arr, killer, arr_size);
				lucky = killer;
			}
			
			lucky = MovePtr(int_arr, lucky, arr_size);
			
			if (lucky == killer)
			{
				printf("The lucky one was at index %d\n", lucky);
				return (0);
			}
		}		
	}
		
	return (0);
}



void InitArray(int *int_arr)
{
	int i = 0;
	
	for (i= 0; i < ARR_SIZE ;i++)
	{
		*(int_arr + i) = ALIVE;
	} 

}

int MovePtr(int *int_arr, int ptr, int arr_size)
{
	
	do
	{
		if (arr_size == (ptr + 1))
		{
			ptr = 0;
		}
		else
		{
			++ptr;
		}
	}
	while(DEAD == *(int_arr + ptr));
	
	return ptr;
}



int StrToInt(char *str)
{

	int num = 0;
	int i = 0;
	int str_len = strlen(str);
		
	for (i = 0; i < str_len; i++)
	{
		num = (10 * num) + (*str - 48);
		++str;
	}
	
	return (num);
}



/*
Answer:
runner move right. check each time if alive.
if alive, kill;
if runner == head = "you are lucky"


head ++ until find alive.
found alive, bring runner;
*/
