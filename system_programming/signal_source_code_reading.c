
#include <signal.h>

__sighandler_t blerg;

int main()
{
    signal(SIGUSR1, blerg);

    return 0;
}