#include <stdio.h>
#include "string.h"

int IsPalindrome(const char *str);


int main()
{

	char str[] = "hello";
	int x = IsPalindrome(str);
	if (1 == x)
	{
		printf("the string is a palindrom\n");
	}
	else
	{
		printf("the string is not a palindrom\n");
	}

	return (0);

}



int IsPalindrome(const char *str)
{
	
	const char *start_runner = str;
	int len = StrLength(str);	
	int half_len = len / 2;	
	const char *end_runner = str;  /**((str)+(len));*/
	

	int i;
	

	for (i=0; i < half_len ; i++)
	{
		if (*start_runner != *end_runner)
		{
			return (0);
		}
		++start_runner, --end_runner;
	}

	return (1);
}
