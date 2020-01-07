/***********************************
*                                  *
*   OS - Simple Watchdog System    *
*   written by: Hadar Klein        *
*   reviewed by: Dafna Cohen       *
*                                  *
***********************************/

#include <stdio.h>      /* print  */
#include <assert.h>     /* assert */
#include <unistd.h>     /* fork   */
#include <sys/wait.h>   /* wait   */
#include <stdlib.h>     /* malloc */
#include <string.h>     /* strcat */

#include "utils.h"

void SystemExecute(int argc, char **argv);

int main(int argc, char **argv)
{
    while (1)
    {
        SystemExecute(argc, argv);
    }
    
    return 0;
}


void SystemExecute(int argc, char **argv)
{
    int i = 0;
    int sum = 0;
    char *args_list = NULL;

    assert(NULL != argv);

    for (i = 1; i < argc; ++i)
    {
        sum += strlen(argv[i]);
    }
    sum += 1*argc - 1;

    args_list = (char *)malloc(sum);

    for (i = 1; i < argc; ++i)
    {
        strcat(args_list, argv[i]);
        strcat(args_list, " ");
    }
    strcat(args_list, "\0");

    system(args_list);

    free(args_list);

    sleep(1);
    return;
}
