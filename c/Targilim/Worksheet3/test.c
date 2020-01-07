#include <stdio.h>
#include <string.h>
#include <ctype.h>


char *strlwr(char *str);

int main()
{

	int new = 0;
	char *str = "hello";
	char *new_str = "HELLO";
	char bob = (char)tolower(*new_str);

	char test_str[] = "HELlo";
	char *test_ptr;

	printf("%s\n", new_str);

	new = tolower(*new_str);
	

	printf("new is: %d\n", new);
	printf("bob is: %c\n", bob);

	test_ptr = strlwr(test_str);

	printf("this is test_str: %s\n", test_str);



	return (0);
}





char *strlwr(char *str)
{

	char *return_ptr = str;
	char *runner = str;
	

	while(*runner)
	{
		*runner = tolower(*runner);
		++runner;
	}
	


	return (return_ptr);


}
