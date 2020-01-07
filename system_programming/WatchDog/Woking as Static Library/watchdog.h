#ifndef ILRD_WATCHDOG_MMI_H
#define ILRD_WATCHDOG_MMI_H

void MMI(int argc, char **argv, int grace, pthread_t *thread);
void DNR(pthread_t thread);


#endif
