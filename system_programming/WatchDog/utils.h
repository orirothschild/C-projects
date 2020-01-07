#ifndef UTILS_H
#define UTILS_H

#define WORD_SIZE sizeof(size_t)

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

#define RUN_TEST(test) (test) ? printf("PASS : "#test"\n") : printf("FAIL : "#test"\n")

#define MOVE(a, b) (void *)((char *)a + abs(b))

/* for sl_list.c */
#define MOVE_NEXT(val) val = val->next

#ifndef NDEBUG
    /* #define PRINT_IN_DEBUG(x) printf("debug mode %s",x) */
    #define PRINT_IN_DEBUG(x) printf(x)
#else
    #define PRINT_IN_DEBUG(x)
#endif

#ifndef NDEBUG
    #define DEBUG_2_ARGS(x, y) printf(x, y)
#else
    #define PRINT_IN_DEBUG(x)
#endif

#ifndef NDEBUG
    #define PRINT_IN_DEBUG_3_ARGS(x, y, z) printf(x, y, z)
#else
    #define PRINT_IN_DEBUG(x)
#endif

#define UNUSED(x) (void)x


#endif

