#include <stdio.h>	/* printf */
#include <string.h> /* strlen */
#include <ctype.h>	/* tolower */
#include "string.h" /* function declarations */


size_t StrLength(const char *str)
{
	const char *runner = str;
	
	assert('\0' != *str);
		
	while (*runner)
	{
		++runner;
	}

	return (runner - str);
}


int StrCompare(const char *str1, const char *str2)
{
	assert('\0' != *str1);
	assert('\0' != *str2);
	
	while (*str1 && (*str1 == *str2))
	{
		++str1, ++str2;
	}
	
	return (*str1 - *str2);
}



char *StrCopy(char *dest, const char *src)
{
	char *dest_begin_ptr = dest;
	
	assert('\0' != *dest);
	
	while (*src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	*dest = '\0';


	return (dest_begin_ptr);
}


char *StrNCopy(char *dest, const char *src, size_t n)
{
	unsigned int i = 0;
	char *dest_begin_ptr = dest;

	assert('\0' != *dest);
	assert(strlen(src) >= n);

	while (*src && i < n)
	{
		*dest = *src;
		++src;
		++dest;
		++i;
	}

	while (*dest)
	{
		*dest = '\0';
		++dest;
	}	

	return(dest_begin_ptr);
}


int StrCaseCompare(const char *str1, const char *str2)
{
	assert('\0' != *str1);
	assert('\0' != *str2);
	
	while (*str1 && (tolower(*str1) == tolower(*str2)))
	{
		++str1, ++str2;
	}
	
	return (tolower(*str1) - tolower(*str2));
}
