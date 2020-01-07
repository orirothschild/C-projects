#include <sys/types.h>  /* ftok */
#include <sys/ipc.h>    /* ftok */
#include <errno.h>      /* errno */
#include <stdio.h>      /* stderr, printf */
#include <sys/ipc.h>    /* msgget, msgsnd */
#include <sys/msg.h>    /* msgget, msgsnd */
#include <stdlib.h>     /* abort */

typedef struct msgbuf
{
    long mtype;       /* message type, must be > 0 */
    char mtext[100];  /* message data */
} message_t;


void CheckReturnVal(int i, const char *msg)
{
    if (-1 == i)
    {
        fprintf(stderr, "there was a problem during %s\n", msg);
        perror("");
        abort();
    } 
}


int main()
{
    message_t msg;
    int retval = 0;
    int msgq_id = 0;
    key_t key;
    char *ftok_file = "/tmp/msgq";
    int id = 123456789;

    key = ftok(ftok_file, id);
    CheckReturnVal(key, "key creation");

    msgq_id = msgget(key, IPC_CREAT | 0666);
    CheckReturnVal(msgq_id, "msgget");

    retval = msgrcv(msgq_id, &msg, sizeof(msg), 1, 0);    
    CheckReturnVal(retval, "msgrcv");

    printf("the message was: %s\n", msg.mtext);

    /* retval = msgsnd(msgq_id, &msg, sizeof(msg), 0);    
    CheckReturnVal(retval, "msgsnd"); */

    retval = msgctl(msgq_id, IPC_RMID, NULL);
    CheckReturnVal(retval, "msgctl");

    
    return 0;
}