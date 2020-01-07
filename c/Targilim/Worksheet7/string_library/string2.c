#include <stdio.h>	/* printf */
#include <string.h> /* strlen */
#include <assert.h> /* asserts */
#include <stdlib.h> /* malloc */
#include "string.h" /* function declarations */


char *StrCharacter(const char *str, int c)
{
	assert('\0' != *str);
	
	while (*str != (char) c)
	{
		/* if the value of the data the pointer points does not exist, 
		return NULL, if it doesn't, increment the pointer */		
		if (!*str++)
		{
			return NULL;			
		}
	}
	return ((char*) str);	
}


char *StrDuplicate(const char *str)
{
	assert('\0' != *str);
	
	char *new_str_ptr = (char*) malloc(StrLength(str));

	if (NULL == new_str_ptr)
	{
		printf("Allocation Failed\n");
		return NULL;
	}
	return (StrCopy(new_str_ptr, str));
}


char *StrConcat(char *dest, const char *src)
{
	char *dest_begin_ptr = dest;

	assert('\0' != *dest);
	assert('\0' != *src);

	while (*dest)
	{
		++dest;
	}
	dest = StrCopy(dest, src);	

	return (dest_begin_ptr);
}


char *StrNConcat(char *dest, const char *src, size_t n)
{
	char *dest_begin_ptr = dest;

	assert('\0' != *dest);
	assert('\0' != *src);
	assert(strlen(src) >= n);

	while (*dest)
	{
		++dest;
	}
	dest = StrNCopy(dest, src, n);

	return (dest_begin_ptr); 
}


char *StrStr(const char *haystack, const char *needle)
{
	int needle_len = StrLength(needle);
	const char *needle_runner = needle;
	const char *hay_runner = haystack;
	int i = 0;

	assert('\0' != *haystack);
	assert('\0' != *needle);


	/* look for the first time the first char from needle shows up */
	char *hay = StrCharacter(haystack, needle[0]);

	
	while (hay)
	{
		hay_runner = hay;
		needle_runner = needle;
		for (i = 0; i < needle_len; i++)
		{
			if (*hay_runner && (*hay_runner == *needle_runner))
			{
				++needle_runner, ++hay_runner;
			}
			else
			{
				break; /* if either hay_runner no longer exists or it does not equal
					 needle_runner, it does not represent the needle any more */
			}
		}
		
		if ((needle_runner - needle) == needle_len)
		{
			return (hay);
		}
		++hay;
		hay = StrCharacter(hay, needle[0]); /* just jumps hay to the next place 
											the first character in needle 
											appears, instead of going over 
											everything */
	}

	return (NULL);
}
