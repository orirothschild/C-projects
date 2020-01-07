#ifndef STRING_H
#define STRING_H


/* returns the length of the string that is passed to it. */
size_t StrLength(const char *str);
size_t StrLenRecursive(const char *str);

/* returns the value in integer of the difference between str1 and str2. */
int StrCompare(const char *str1, const char *str2);
int StrCompareRecursive(const char *str1, const char *str2);

/* copies the string from src into dest and returns the pointer that points to 
the beginning of dest. */
char *StrCopy(char *dest, const char *src);
char *StrCopyRecursive(char *dest, const char *src);

/* Copies the string src to dest up to the n'th character. If the dest is bigger
than the src, pad it with \0's. */
char *StrNCopy(char *dest, const char *src, size_t n);

/* compares the lower case versions of str1 and str2 and returns the difference
between them, similar to StrCompare. */
int StrCaseCompare(const char *str1, const char *str2);

/* returns a pointer to the first time c shows up in the string,otherwise
 return NULL */
char *StrCharacter(const char *str, int c);

/* dulicates string and returns pointer to the beginning of new string */
char *StrDuplicate(const char *s);

/* append src to the end of dest and return a pointer to dest */
char *StrConcat(char *dest, const char *src);
char *StrConcatRecursive(char *dest, const char *src);

/* append src to the end of dest, but at most n character from src */
char *StrNConcat(char *dest, const char *src, size_t n);

/* returns a pointer to the place where needle starts, if it exists in haystack,
 otherwise, NULL */
char *StrStr(const char *haystack, const char *needle);
char *StrStrRecursive (const char *haystack, const char *needle);

/* returns the length of the substring "accept" that shows up in the string 
"str". */
size_t StrSpan(const char *str, const char *accept);

/* returns a pointer to the last token when called with NULL or reinitializes
 with a new str when given. */
char *StrToken(char *s, const char *delim);

/* returns 1 if the string is a palindrome, otherwise, returns 0 */
int IsPalindrome(const char *str);

/* 7 Boom! */
/* static void Boom(int from, int to);
 */
/* Helper function for 7 Boom function. Returns 1 if the int passed has a 7 
in it somewhere, otherwise returns 0. */
/* static int HasSeven(int num);
 */
/* Swap to pointers to ints */
/* static void SwapIntPtr(int **num1, int **num2);
 */
/* trims leading and trailing whitespaces and tabs and removes extras inside */
/* static void RmSpaces(char *str);
 */
/* calculates addition of big numbers using strings */
/* static char *BigAddition(char *str1, char *str2);
 */
#endif
