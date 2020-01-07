#include <stdio.h>




int main ()
{


	int x = 0;
	int int_arr5[5] = {1,2,3,4,5};
	int int_arr10[10] = {0};
	int *arr_ptr = int_arr5;

	printf("The size of an int %lu\n", sizeof(x));
	printf("The size of int_arr5 %lu\n", sizeof(int_arr5));
	printf("The size of int_arr10 %lu\n", sizeof(int_arr10));
	printf("The size of arr_ptr %lu\n", sizeof(arr_ptr));



	return (0);
}
