#include <stdio.h> /* printf */

#include "simple_watchdog.h"
#include "simple_watchdog_test_funcs.h"


enum {FAIL, PASS};
int main()
{
    RUN_TEST();
    return (0);
}
