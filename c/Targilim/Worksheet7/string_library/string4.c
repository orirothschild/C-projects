#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */
#include <assert.h> /* asserts */
#include "string.h"	/* function declarations */


static void SwapIntPtr(int **num1, int **num2)
{
	/* create a temp pointer */
	int *temp = *num1;

	assert('\0' != **num1);
	assert('\0' != **num2);
	
	*num1 = *num2;
	*num2 = temp;
}


static void RmSpaces(char *str)
{
	char *str_runner = str;
	char *begin_ptr = str;
	
	assert('\0' != *str);

	/* Remove inner and trailing whitespaces */	
	while (NULL != str_runner)
	{
		
		if ((' ' != *str_runner) && ('\t' != *str_runner))
		{
			while ((NULL != str_runner) && (' ' != *str_runner) && \
					('\t' != *str_runner))
			{
				*str = *str_runner;
				str++, str_runner++;
			}
			*str = ' ';
			str++;
		}
		++str_runner;

		if ('\0' == *str_runner)
		{
			if(begin_ptr != str)
			{
				str--;
				
			}			
			
			*str = '\0';	
			break;
		}
	}
	str = '\0';
}


static char *BigAddition(char *str1, char *str2)
{
	int remainder = 0;
	int sum = 0;
	int num1 = 0;
	int num2 = 0;
	int i = 0;
	int max_len = 0;
	int difference = 0;
	int length_of_shorter_str = 0;	
	char *longer_str = str1;
	char *shorter_str = str2;
	char *return_ptr;				/* malloc'ed */
	char *begin_return_ptr;			/* depends on return_ptr */
	char *final_return_ptr;			/* malloc'ed */
	
	assert('\0' != *str1);
	assert('\0' != *str2);
	
	/* check which string is longer and initialize accordingly */
	if (StrLength(str2) < StrLength(str1))
	{
		longer_str = str1;
		shorter_str = str2;
	}
	else
	{
		longer_str = str2;
		shorter_str = str1;
	}
	
	length_of_shorter_str = StrLength(shorter_str);

	/* Create a new return string to house the calculated string.
	Cannot be larger than 1 more then the longer str */
	max_len = StrLength(longer_str) + 1;	
	return_ptr = (char *)malloc(sizeof(max_len));
	begin_return_ptr = return_ptr;

	/* initialize return_str and place pointer at the end, before '\0'*/
	for (i = 0; i < max_len +1; i++)
	{
		*return_ptr = '1';
		++return_ptr;
	}	
	*return_ptr = '\0';
	--return_ptr;

	/* move pointers to the end */
	longer_str += StrLength(longer_str) - 1;
	shorter_str += StrLength(shorter_str) - 1;
	
	/* calculations */
	for (i = 0; i < max_len - 1; i++)
	{
		/* get the number in the last place in the string */
		num1 = *longer_str - 48;
		num2 = *shorter_str - 48;

		/* when the shorter one ends, pad with 0 */
		if (length_of_shorter_str <= i )
		{
			num2 = 0;
		}
		
		sum = num1 + num2;
		*return_ptr = ((sum + remainder) % 10) + 48;
		remainder = sum / 10;

		/* move the pointers */
		--longer_str, --shorter_str, --return_ptr;
	}	
	
	/* if last remainder not zero, add last remainder */
	if (0 == remainder)
	{
		++return_ptr;
	}
	else
	{
		*return_ptr = (char)remainder;
	}
	
	/* find the difference between where the pointer began and where it is now */
	difference = return_ptr - begin_return_ptr;
	
	/*newreturnptr = new malloc (max_len - difference)*/
	final_return_ptr = (char *)malloc((max_len) - difference);	

	/* Copy old string to new, smaller string */
	StrCopy(final_return_ptr, return_ptr);	
	
	/* free the first malloc */
	return_ptr = return_ptr - difference;	
	free(return_ptr);
	
	return (final_return_ptr);
}
