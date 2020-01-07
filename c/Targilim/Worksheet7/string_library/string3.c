#include <stdio.h>	/* printf */
#include <assert.h> /* asserts */
#include "string.h"	/* function declarations */


size_t StrSpan(const char *str, const char *accept)
{
	
	const char *str_ptr = str;
	const char *accept_ptr = accept;
	size_t counter = 0;

	assert('\0' != *str);
	assert('\0' != *accept);
	
	
	while('\0' != *str_ptr)
	{
		accept_ptr = accept;
		while('\0' != *accept_ptr)
		{	
			if (*accept_ptr == *str_ptr)
			{
				++counter;
				break;
			}
			++accept_ptr;
		}
		
		if ('\0' == *accept)
		{
			return (counter);
		}
		
		++ str_ptr;
	}
}


char *StrToken(char *str, const char *delim)
{
	
	unsigned int delim_len = StrLength(delim);
	static char * new_ptr;

	assert('\0' != *delim);

	if (str)
	{
		new_ptr = str;
	}
	else
	{
		++new_ptr;
		str = new_ptr;
	}


	while (*new_ptr)
	{
		while(*delim)
		{
			if (*new_ptr == *delim)
			{
				*new_ptr = '\0';
				return str;
			}
			++delim;
			
		}
		delim -= delim_len;
		++new_ptr;
	}
	
	if (!*new_ptr && *str)
	{
		return str;
	}

	return NULL;

}


int IsPalindrome(const char *str)
{
	
	const char *start_runner = str;
	int len = StrLength(str);	
	int half_len = len / 2;	
	const char *end_runner = str+(len-1);
	int i = 0;
	
	assert('\0' != *str);

	for (i = 0; i < half_len ; i++)
	{
		if (*start_runner != *end_runner)
		{			
			return (0);
		}
		++start_runner, --end_runner;
	}

	return (1);
}


static void Boom(int from, int to)
{
	int i = 0;

	for (i = from; i <= to; i++)
	{
		if (!HasSeven(i) && (i % 7 != 0))
		{
			printf("%d ", i);
		}
	}
	printf("\n");

}


static int HasSeven(int num)
{
	int mod_num = num;
	
	while (0 != (mod_num % 10))
	{
		
		if (7 == (mod_num % 10))
		{
			printf("BOOM! ");			
			return (1);
		}
		mod_num /= 10;
	}
	if (7 == mod_num)
	{
		return (1);
	}
	return (0);
}
