#include <sys/types.h>  /* ftok */
#include <sys/ipc.h>    /* ftok */
#include <errno.h>      /* errno */
#include <stdio.h>      /* stderr, printf */
#include <sys/ipc.h>    /* msgget, msgsnd */
#include <sys/shm.h>    /* msgget, msgsnd */
#include <string.h>     /* memcpy */
#include <stdlib.h>     /* abort */

#define MSG_MAX_LEN (100)

void CheckReturnVal(int i, const char *msg)
{
    if (-1 == i)
    {
        fprintf(stderr, "there was a problem during %s\n", msg);
        perror("");
        abort();
    } 
}
void CheckReturnPtr(void *ptr, const char *msg)
{
    if (-1 == *(char *)ptr)
    {
        fprintf(stderr, "there was a problem during %s\n", msg);
        perror("");
        abort();
    } 
}


int main()
{
    key_t key;
    char *shm_address = NULL;
    int shm_id = 0;
    
    FILE* fp = NULL;
    char *ftok_file = "/tmp/shm";
    int id = 123456789;
    
    if(NULL == (fp = fopen(ftok_file, "a+")))
    {
        perror("");
        abort();
    }
    fclose(fp);

    key = ftok(ftok_file, id);
    CheckReturnVal(key, "key creation");

    shm_id = shmget(key, MSG_MAX_LEN, 0666 | IPC_CREAT);
    CheckReturnVal(shm_id, "shmget");

    shm_address = shmat(shm_id, NULL, 0);
    CheckReturnPtr(shm_address, "shmat");

    printf("The message in shared memory was: %s\n", shm_address);

    shmdt(shm_address);

    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}