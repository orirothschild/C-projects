#include <stdio.h>	/* printf */
#include <ctype.h>	/* tolower */
#include <stdlib.h>	/* malloc */
#include <assert.h> /* assert */
#include "string.h"	/* function declarations */

/* static void Boom(int from, int to); */
/* static int HasSeven(int num);
 *//* static void SwapIntPtr(int **num1, int **num2); */
/* static void RmSpaces(char *str); */
/* static char *BigAddition(char *str, char *str2); */
/* static void ValCheck (); */
/* static void IndefLoop(); */
static int CheckSubString (const char *haystack, const char *needle);


	/* printf("the length of 'hi' is: %lu\n", StrLength("hi")); */
	/* printf("the length of 'hi there' is: %lu\n", StrLenRecursive("hi there"));*/
	/*printf("the difference of 'hello' and 'helo' is: %d\n", StrCompare("hello", "helo"));*/
	/* printf("the difference of 'hello' and 'helo' is: %d\n", StrCompareRecursive("hello", "helo")); */


	/* char src[] = "hello";
	char dest[6];	
	StrCopy(dest, src);
	printf("this is now the dest: %s\n", dest); */
	
	/* char src[] = "hello";
	char dest[6];	
	StrCopyRecursive(dest, src);
	printf("this is now the dest: %s\n", dest);
 */

	/*char src[] = "hi there my name is bob";
	char dest[9];
	int n = 8;
	StrNCopy(dest, src, n);
	printf("this is now the dest: %s\n", dest);*/

	/*char str1[] = "hello";
	char str2[] = "HELLN";	
	printf("the number is %d\n", StrCaseCompare(str1, str2));
	*/

	/*	
	char test[] = "abc";
	int c = 'b';
	StrCharacter(test, c);
	*/

	/*	
	char str_to_dup[5] = "start";
	char *new_str = StrDuplicate(str_to_dup);
	printf("%s\n", new_str);
	free(new_str);
	*/
	
	
	/* char str1[] = "hello ";
	char str2[] = "there!";
	char *new_str1 = StrConcat(str1, str2);
	printf("the new string is:\n%s\n", new_str1); */
	
 /* 
	char str3[30] = "hello ";
	char str4[30] = "there!";
	char *new_str2 = StrConcatRecursive(str3, str4);
	printf("the new string is:\n%s\n", new_str2);
	printf("the new string is:\n%s\n", str3);
 */
	/*
	char str1[30] = "hello ";
	char str2[6] = "there!";
	int x = 3;
	char *new_str = StrNConcat(str1, str2, x);
	printf("the new string is:\n%s\n", new_str);
	*/

	/* 
	char hay[] = "Hello there!";
	char needle[] = "the";
	char *new_str = StrStr(hay, needle);
	printf("%s\n", new_str);
	 */

/*
	char hay[] = "Hello there!";
	char needle[] = "the";
	char *new_str = StrStrRecursive(hay, needle);
	printf("%s\n", new_str);
*/	



/*
	char big[] = "abcdef";
	char small[] = "aghf";
	int len = StrSpan(big , small);
	printf("this is the length: %d\n", len);
*/


	/*
	char str[] ="This,is,text";
	char str1[] = ",";
    char * pch;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = StrToken(str, str1);
    while (pch)
    {

		printf ("%s\n",pch);
        pch = StrToken(NULL, ",");
    }
	*/


	/*
	char test_str[] = "hello";
	int x = IsPalindrome(test_str);
	if (1 == x)
	{
		printf("is palindrome\n");
	}
	else
	{
		printf("is not a palindrome\n");
	}
	*/

	/*
	int x = 0;
	int y = 29;
	Boom(x, y);
	*/

	/*
	int i = 1;
	int j = 2;
	int *ip = &i;
	int *jp = &j;
	printf("i is %d\n", *ip);
	printf("j is %d\n", *jp);
	printf("i address is %p\n", (void *)ip);
	printf("j address is %p\n", (void *)jp);
	SwapIntPtr(&ip, &jp);
	printf("i is %d\n", *ip);
	printf("j is %d\n", *jp);
	printf("i address is %p\n", (void *)ip);
	printf("j address is %p\n", (void *)jp);
	*/

	/*
	char test_str[] = "hitherebob";
	printf("the string is:%s\n", test_str);	
	RmSpaces(test_str);
	printf("the string is:%s\n", test_str);
	*/

	/*
	char a_number[] = "1234";
	char b_number[] = "678";
	char *result = BigAddition(a_number, b_number);
	printf("This is the result: %s\n", result);
	free(result);
	*/

	/*
	ValCheck();
	*/

	/* IndefLoop(); */


/* returns the length of the string that is passed to it. */
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

size_t StrLenRecursive(const char *str)
{
	if ('\0' == *str)
	{
		return 0;
	}

	return 1 + StrLenRecursive(str + 1);
}

/* returns the value in integer of the difference between str1 and str2. */
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

int StrCompareRecursive(const char *str1, const char *str2)
{
	if ('\0' == *str1 || *str1 != *str2)
	{
		return *str1 - *str2;
	}

	return StrCompareRecursive(str1 + 1, str2 + 1);
}
/* copies the string from src into dest and returns the pointer that points to 
the beginning of dest. */
char *StrCopy(char *dest, const char *src)
{
	char *dest_begin_ptr = dest;
	
	
	while (*src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	*dest = '\0';


	return (dest_begin_ptr);
}



char *StrCopyRecursive(char *dest, const char *src)
{
	if ('\0' != *src)
	{
		StrCopyRecursive(dest + 1, src +1);
	}

	*dest = *src;
	
	return dest;
}

/* Copies the string src to dest up to the n'th character. If the dest is bigger
than the src, pad it with \0's. */
char *StrNCopy(char *dest, const char *src, size_t n)
{
	unsigned int i = 0;
	char *dest_begin_ptr = dest;

	assert('\0' != *dest);
	assert(StrLength(src) >= n);

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


/* compares the lower case versions of str1 and str2 and returns the difference
between them, similar to StrCompare. */
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


/* returns a pointer to the first time c shows up in the string,otherwise
 return NULL */
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


/* dulicates string and returns pointer to the beginning of new string */
char *StrDuplicate(const char *str)
{
	char *new_str_ptr = (char*) malloc(StrLength(str));

	assert('\0' != *str);

	if (NULL == new_str_ptr)
	{
		printf("Allocation Failed\n");
		return NULL;
	}
	return (StrCopy(new_str_ptr, str));
}

/* append src to the end of dest and return a pointer to dest */
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



char *StrConcatRecursive(char *dest, const char *src)
{
	if ('\0' == *dest)
	{
		StrCopyRecursive(dest, src);
	}

	StrConcatRecursive(dest + 1, src);

	return dest;
}



/* append src to the end of dest, but at most n character from src */
char *StrNConcat(char *dest, const char *src, size_t n)
{
	char *dest_begin_ptr = dest;

	assert('\0' != *dest);
	assert('\0' != *src);
	assert(StrLength(src) >= n);

	while (*dest)
	{
		++dest;
	}
	dest = StrNCopy(dest, src, n);

	return (dest_begin_ptr); 
}

/* returns a pointer to the place where needle starts, if it exists in haystack,
 otherwise, NULL */

char *StrStr(const char *haystack, const char *needle)
{
	int needle_len = StrLength(needle);
	const char *needle_runner = needle;
	const char *hay_runner = haystack;
	int i = 0;
	char *hay = NULL;

	assert('\0' != *haystack);
	assert('\0' != *needle);

	/* look for the first time the first char from needle shows up */
	hay = StrCharacter(haystack, needle[0]);

	
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


char *StrStrRecursive (const char *haystack, const char *needle)
{
    if ('\0' == *haystack)
    {
        return (NULL);
    }

    if (*haystack == *needle)
    {
        if (1 == CheckSubString(haystack + 1, needle + 1))
        {
            return ((char *)haystack);
        }        
    }

    return StrStrRecursive(haystack + 1, needle);
}

static int CheckSubString (const char *haystack, const char *needle)
{
    if ('\0' == *needle)
    {
        return 1;
    }
    
    if (*haystack != *needle)
    {
        return 0;
    }

    return CheckSubString (haystack + 1, needle + 1);
}


/* returns the length of the substring "accept" that shows up in the string 
"str". */
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
		
		++str_ptr;
	}

	return counter;
}





/* returns a pointer to the last token when called with NULL or reinitializes
 with a new str when given. */
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
		printf("this is Start runner in for: %d\n", *start_runner);
		printf("this is end runner in for: %d\n", *end_runner);
		if (*start_runner != *end_runner)
		{
			printf("this is Start runner: %d\n", *start_runner);
			printf("this is end runner: %d\n", *end_runner);			
			return (0);
		}
		++start_runner, --end_runner;
	}

	return (1);
}

/* 7 Boom! */
/* static void Boom(int from, int to)
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

} */

/* Helper function for 7 Boom function. Returns 1 if the int passed has a 7 
in it somewhere, otherwise returns 0. */
/* static int HasSeven(int num)
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
} */


/* Swap to pointers to ints */
/* static void SwapIntPtr(int **num1, int **num2)
{
	 create a temp pointer 
	int *temp = *num1;

	assert('\0' != **num1);
	assert('\0' != **num2);
	
	*num1 = *num2;
	*num2 = temp;
} */


/* trims leading and trailing whitespaces and tabs and removes extras inside */
/* static void RmSpaces(char *str)
{
	char *str_runner = str;
	char *begin_ptr = str;
	
	assert('\0' != *str);

	 Remove inner and trailing whitespaces *
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
} */





/* static char *BigAddition(char *str1, char *str2)
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
	char *return_ptr;				
	char *begin_return_ptr;		
	char *final_return_ptr;		
	
	assert('\0' != *str1);
	assert('\0' != *str2);
	
	 check which string is longer and initialize accordingly
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

	 Create a new return string to house the calculated string.
	Cannot be larger than 1 more then the longer str 
	max_len = StrLength(longer_str) + 1;	
	return_ptr = (char *)malloc(sizeof(max_len));
	begin_return_ptr = return_ptr;

	initialize return_str and place pointer at the end, before '\0'
	for (i = 0; i < max_len +1; i++)
	{
		*return_ptr = '1';
		++return_ptr;
	}	
	*return_ptr = '\0';
	--return_ptr;

	 move pointers to the end 
	longer_str += StrLength(longer_str) - 1;
	shorter_str += StrLength(shorter_str) - 1;
	
	 calculations 
	for (i = 0; i < max_len - 1; i++)
	
		 get the number in the last place in the string 
		num1 = *longer_str - 48;
		num2 = *shorter_str - 48;

		 when the shorter one ends, pad with 0 
		if (length_of_shorter_str <= i )
		{
			num2 = 0;
		}
		
		sum = num1 + num2;
		*return_ptr = ((sum + remainder) % 10) + 48;
		remainder = sum / 10;

		 move the pointers 
		--longer_str, --shorter_str, --return_ptr;
	}	
	
	 if last remainder not zero, add last remainder 
	if (0 == remainder)
	{
		++return_ptr;
	}
	else
	{
		*return_ptr = (char)remainder;
	}
	
	 find the difference between where the pointer began and where it is now 
	difference = return_ptr - begin_return_ptr;
	
	newreturnptr = new malloc (max_len - difference)
	final_return_ptr = (char *)malloc((max_len) - difference);	

	 Copy old string to new, smaller string 
	StrCopy(final_return_ptr, return_ptr);	
	
	 free the first malloc 
	return_ptr = return_ptr - difference;	
	free(return_ptr);
	
	return (final_return_ptr);
}
 */



/* static void ValCheck ()
{ */

/*	
	char str[] = "hi there!";
	char *no_free = (char *)malloc(sizeof(str));
	StrCopy(no_free, str);
*/


/* 
	char *arr_10[10] = {0};
	char *ptr = arr_10[11];
	printf("the 11'th character: %c\n", *ptr);
	*ptr = 'h';

 */
/*
	char str[] = "hi there!";
	char *str2 = {0};	
	char *free_ptr = (char *)malloc(sizeof(str));
	StrCopy(free_ptr, str);
	free(free_ptr);
	str2 = *free_ptr;
*/	

/*
	char str[] = "hi there!";
	char *free_ptr = (char *)malloc(sizeof(str));
	StrCopy(free_ptr, str);
	free(free_ptr);
	*free_ptr;
*/

	/* char str[] = "hi there"; */
	/*printf("%s\n", str);*/
/*
}

*/
/* 
static void IndefLoop()
{

	int i = 1;

	while(i)
	{
		
	}


}


 */
