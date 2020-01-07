#include <stdio.h> /*for printf*/
#include <time.h>
#include "schd.h"

time_t SchdActionFunc (void *param);
time_t SchdEndFunc (void *param);
time_t SchdReActionFunc (void *param);
time_t SchdAddFunc (void *param);
time_t SchdErrorFunc (void *param);
time_t SchdEndFileFunc (void *param);

#define RUN_TEST(test) test ? printf("OK: " #test "\n") : \
                              printf("FAILED:  " #test "\n");
                                                           
int main()
{
	scheduler_t *schedualer = SchdCreate();
	uuid_t user_uid = {0};
	int runtimes = 0;
	RUN_TEST (1 == SchdIsEmpty(schedualer));
	RUN_TEST (0 == SchdSize(schedualer));
	printf("\n");
	user_uid = SchdAdd(schedualer, SchdActionFunc, NULL, 5/*(time(NULL)+3)*/);
	RUN_TEST (0 == UUIDIsBadUID(user_uid));
	RUN_TEST (0 == SchdIsEmpty(schedualer));	
	RUN_TEST (1 == SchdSize(schedualer));
	printf("\n");
	RUN_TEST (0 == SchdRemove(schedualer, user_uid));
	RUN_TEST (1 == SchdIsEmpty(schedualer));	
	RUN_TEST (0 == SchdSize(schedualer));
	printf("\n");
	SchdAdd(schedualer, SchdActionFunc, "30", (time(NULL)+30));
	SchdAdd(schedualer, SchdActionFunc, "15", (time(NULL)+15));
	SchdAdd(schedualer, SchdActionFunc, "12", (time(NULL)+12));
	RUN_TEST (1 == SchdRemove(schedualer, user_uid));
	printf("\n");
	user_uid = SchdAdd(schedualer, SchdActionFunc, "2", (time(NULL)+2));
	SchdAdd(schedualer, SchdActionFunc, "16", (time(NULL)+16));
	SchdAdd(schedualer, SchdActionFunc, "20", (time(NULL)+20));
	printf("\n");
	RUN_TEST (0 == SchdRemove(schedualer, user_uid));
	RUN_TEST (0 == SchdIsEmpty(schedualer));	
	RUN_TEST (5 == SchdSize(schedualer));
	printf("\n");
	runtimes = SchdRun(schedualer);
	printf("\n");
	RUN_TEST (1 == SchdIsEmpty(schedualer));	
	RUN_TEST (0 == SchdSize(schedualer));
	printf("\n");
	SchdAdd(schedualer, SchdActionFunc, "4", (time(NULL)+4));
	SchdAdd(schedualer, SchdReActionFunc, schedualer, (time(NULL)+2));
	SchdAdd(schedualer, SchdActionFunc, "1", (time(NULL)+1));
	SchdAdd(schedualer, SchdEndFunc, schedualer, (time(NULL)+3));
	SchdAdd(schedualer, SchdActionFunc, "5", (time(NULL)+5));
	SchdAdd(schedualer, SchdEndFunc, schedualer, (time(NULL)+10));
	SchdAdd(schedualer, SchdAddFunc, schedualer, (time(NULL)+6));
	SchdAdd(schedualer, SchdActionFunc, "7", (time(NULL)+7));
	SchdAdd(schedualer, SchdErrorFunc, schedualer, (time(NULL)+15));
	runtimes = SchdRun(schedualer);
	printf("\n");
	RUN_TEST (-2 == runtimes);	
	RUN_TEST (0 == SchdIsEmpty(schedualer));	
	runtimes = SchdRun(schedualer);
	printf("\n");
	runtimes = SchdRun(schedualer);
	RUN_TEST (-1 == runtimes);	
	SchdRun(schedualer);
	printf("\n");
	SchdAdd(schedualer, SchdActionFunc, "1", (time(NULL)+1));
	SchdAdd(schedualer, SchdEndFileFunc, schedualer, (time(NULL)+3));
	SchdAdd(schedualer, SchdActionFunc, "4", (time(NULL)+4));
	SchdAdd(schedualer, SchdActionFunc, "4", (time(NULL)+4));
	SchdAdd(schedualer, SchdActionFunc, "4", (time(NULL)+4));
	SchdAdd(schedualer, SchdActionFunc, "4", (time(NULL)+4));
	printf("\n");
	SchdRun(schedualer);
	printf("\n");
	RUN_TEST (1 == SchdIsEmpty(schedualer));	
	printf("\n");
	SchdDestroy(schedualer);

	return 1;
}

time_t SchdActionFunc (void *param)
{
	time_t now = time(NULL);
	printf ("should run at %s Seconds, Time now is %s", (char*) param, ctime(&now));
	return 0;
}

time_t SchdReActionFunc (void *param)
{
	static int not_again = 0;
	time_t now = time(NULL);
	
	(void)param;

	printf ("Time now is %s", ctime(&now));
	
	if (0 == not_again)
	{
		++not_again;
		return time(NULL);
	}
	printf ("and now, the re-run!\n");
	return 0;
}

time_t SchdEndFunc (void *param)
{
	(void)param;
	printf ("stopped at user request.\n");
	SchdStop((scheduler_t*) param);
	
	return 0;
}

time_t SchdEndFileFunc (void *param)
{
	FILE *file = fopen ("STOP", "r");	
	if (NULL == file)
	{
		printf ("No STOP file found, repeating in 15 seconds.\n");
		return (time(NULL)+15);
	}
	
	printf ("Found STOP file, Aborting.\n");
	fclose (file);
	remove ("STOP");	
	SchdStop((scheduler_t*) param);
	
	return 0;
}

time_t SchdAddFunc (void *param)
{
	(void)param;
	printf ("adding another function.\n");
	SchdAdd((scheduler_t*) param, SchdActionFunc, "12", time(NULL)+12);
		
	return 0;
}

time_t SchdErrorFunc (void *param)
{
	(void)param;
	printf ("ERROR.\n");
	
	return -1;
}
