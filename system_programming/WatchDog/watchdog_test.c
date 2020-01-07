#include <stdio.h>      /* printf */
#include <pthread.h>    /* pthread */


#include "watchdog_mmi.h"

int main(int argc, char **argv)
{
    pthread_t thread = 0;
    int grace = 5;
    size_t i = 0;
    
    MMI(argc, argv, grace, &thread);
    for(i = 0; i < 2147483647; ++i);
    DNR(thread);
    printf("after DNR\n");

    return 0;
}