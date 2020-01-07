#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strings */

#ifndef HEADER_FILE
#define HEADER_FILE


/* checks that an allocation worked properly, else, exits */
void CheckAlloc(void *ptr);

/* helper function, initializes an array of size WORD with a given char */
void InitializeArr(char *word_arr, int c);

/* Copies a char c n times into a memory block str */
void *MemSet(void *str, int c, size_t n);

/* Copies the first n bytes from src to dest, overrides the existing data */
void *MemCpy(void *dest, const void *src, size_t n);

/* Copies the first n bytes from src to dest, overrides the existing data */
void *MemMove(void *dest, const void *src, size_t n);


#endif
