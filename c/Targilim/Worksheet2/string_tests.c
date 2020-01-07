#include <stdio.h>   /* printf */
#include "string.h" /* API    */

#define RUN_TEST(test) (!test) ? printf("FAIL : "#test"\n" ) : \
printf("PASS : "#test"\n")

int TestString_StrLengthRecursive();
int TestString_StrCompareRecursive();
int TestString_StrCopyRecursive();
int TestString_StrConcatRecursive();
int TestString_StrStrRecursive();

enum {FAIL, PASS};

int main()
{
	RUN_TEST(TestString_StrLengthRecursive());
	RUN_TEST(TestString_StrCompareRecursive());
	RUN_TEST(TestString_StrCopyRecursive());
    RUN_TEST(TestString_StrConcatRecursive());
    RUN_TEST(TestString_StrStrRecursive());

    return 0;

}


int TestString_StrLengthRecursive()
{
    char *str = "hi there";

    if (8 == StrLenRecursive(str))
    {
        return PASS;
    }

    return FAIL;
}


int TestString_StrCompareRecursive()
{
    char *str1 = "hello";
    char *str2 = "helo";

    if (-3 == StrCompareRecursive(str1, str2))
    {
        return PASS;
    }

    return FAIL;

}


int TestString_StrCopyRecursive()
{
    char src[] = "hello";
	char dest[6];	
	StrCopyRecursive(dest, src);
	/* printf("this is now the dest: %s\n", dest); */
    if (0 == StrCompare(dest, src))
    {
        return PASS;
    }

    return FAIL;

}


int TestString_StrConcatRecursive()
{ 
	char str1[30] = "hello ";
	char str2[30] = "there!";
	char *new_str = StrConcatRecursive(str1, str2);
/*  	printf("the new string is:\n%s\n", new_str);
	printf("the new string is:\n%s\n", str1);
    printf("the new string is:\n%s\n", str2); */
    /* StrConcatRecursive(str1, str2); */

    if (0 == StrCompare(new_str, "hello there!"))
    {
        return PASS;
    }

    return FAIL;
}


int TestString_StrStrRecursive()
{
	char hay[] = "Hello there!";
	char needle[] = "the";
	char *new_str = StrStrRecursive(hay, needle);
/* 	printf("%s\n", new_str);
 */
    if (0 == StrCompare(new_str, "there!"))
    {
        return PASS;
    }

    return FAIL;
}
