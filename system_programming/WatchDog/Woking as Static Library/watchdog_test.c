#include <stdio.h> /* printf */
#include <pthread.h>
#include <unistd.h>

#include "watchdog.h"
/* #include "watchdog_test_funcs.h" */

/* enum {FAIL, PASS};
int main()
{
    RUN_TEST();
    return (0);
}
 */



int main(int argc, char **argv)
{
    pthread_t thread = 0;
    int grace = 5;
    size_t i = 0;
    size_t j = 0;
    MMI(argc, argv, grace, &thread);
    for(i = 0; i < 2147483647; ++i)
    {
        if (i == j * 100000)
        {
            /* printf("reached %i\n", i); */
            ++j;
        }
    }
    DNR(thread);
    printf("after DNR\n");

    return 0;
}