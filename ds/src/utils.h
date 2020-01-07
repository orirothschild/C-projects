#ifndef UTILS_H
#define UTILS_H

#define WORD_SIZE sizeof(size_t)

#define SIZEOFVAR(X) (unsigned int)((char *)((&X) + 1) - (char *)(&X))
#define SIZEOFTYPE(X) (size_t)((X *)0 + 1)

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define ABS(a) (a > 0 ? a : a * -1)

#define True (1 == 1)
#define False (!True)

#define FAILURE 1
#define SUCCESS 0
#define ERROR -1

#define FAIL 0
#define PASS 1

#define RUN 0
#define STOP 1

#define FOUND 1
#define NOT_FOUND 0

#define UNUSED(X) (void)X

/* for a compare function */
#define IDENTICAL 0

#define POWER(x,exp) (x << exp)

#define ALIGN(ptr, align_to) (ptr + (align_to - 1) & ~(align_to - 1))

#define RUN_TEST(test) (test) ? printf("PASS : "#test"\n") : printf("FAIL : "#test"\n")

#define MOVE(a, b) (void *)((char *)a + abs(b))

/* for sl_list.c */
#define MOVE_NEXT(val) val = val->next
#define MOVE_PREV(val) val = val->prev

#ifndef NDEBUG
    #define PRINT_IN_DEBUG(x) printf("debug mode %s",x)
#else
    #define PRINT_IN_DEBUG(x)
#endif



#endif

