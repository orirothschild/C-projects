/***********************************
*                                  *
*   DS - Scheduler                 *
*   written by: Hadar Klein        *
*   reviewed by: Dafna Cohen       *
*                                  *
***********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memset */

#include "schd.h"   /*  API   */
#include "pqueue.h" /*  API   */
#include "task.h"   /*  tasks */
#include "utils.h"  /*  utils */

const int ALLOCATION_ERROR = -3;
const int STOP_FLAG_USED = -2;
const int TASK_FAILURE = -1;

int SchdIsMatchFunc(const void *task, const void *uid, const void *param);

static time_t SchdSleep(scheduler_t *schd);

static int CompareTaskTimes(const void *task,
                           const void *new_task, 
                           void *param);
                          
struct scheduler
{
    p_queue_t *p_queue;
    int stop_flag;
};

struct p_queue
{
    srt_list_t *slist;
};


scheduler_t *SchdCreate()
{
    scheduler_t *schd = NULL;
    p_queue_t *pq = NULL;
    
    schd = (scheduler_t *)malloc(sizeof(scheduler_t));
    if (NULL == schd)
    {
        return (NULL);
    }
    
    pq = PQueueCreate(CompareTaskTimes);
    if (NULL == pq)
    {
        SchdDestroy(schd); /* Not Sure if this can work, may need to be free */
        return (NULL);
    }
    
    schd->p_queue = pq;
    schd->stop_flag = RUN;
    
    return (schd);
}


void SchdDestroy(scheduler_t *schd)
{
    assert(NULL != schd);
    
    while (0 == SchdIsEmpty(schd))
    {
        TaskRemoveElement(PQueuePeek(schd->p_queue));
        PQueueDequeue(schd->p_queue);
    }
    
    PQueueDestroy(schd->p_queue);
    memset(schd, 0, sizeof(scheduler_t));
    free(schd);
}


size_t SchdSize(scheduler_t *schd)
{
    assert(NULL != schd);
    
    return (PQueueSize(schd->p_queue));
}


int SchdIsEmpty(scheduler_t *schd)
{
    assert(NULL != schd);
    
    return (PQueueIsEmpty(schd->p_queue));
}


void SchdStop(scheduler_t *schd)
{
    assert(NULL != schd);
    
    schd->stop_flag = STOP;
}


uuid_t SchdAdd(scheduler_t *schd,
               user_func_t command_func,
               void *param,
               time_t time)
{
    task_t *task = NULL;
    
    assert(NULL != schd);
    assert(NULL != command_func);
    assert(TASK_FAILURE != time);
    
    task = TaskCreateElement(command_func, param, time);
    if (NULL == task)
    {
        return (g_bad_uuid);
    }

    if (FAILURE == PQueueEnqueue(schd->p_queue, task))
    {
        TaskRemoveElement(task);
        return (g_bad_uuid);
    }
    
    return (TaskGetUUID(task));
}

      
int SchdRemove(scheduler_t *schd, uuid_t uid)
{
    task_t *task = NULL;
    
    assert(NULL != schd);
    assert(0 == SchdIsBadUID(uid));
    
    task = PQueueRemove(schd->p_queue, SchdIsMatchFunc, &uid);
    
    if (NULL != task)
    {
        TaskRemoveElement(task);
        return (SUCCESS);
    }
    
    return (FAILURE);
}


int SchdRun(scheduler_t *schd)
{
    size_t count = 0;
    time_t run_time = 0;
    task_t *task = NULL;
    time_t time_diff = 0;
    
    assert(NULL != schd);
    
    schd->stop_flag = RUN;
    
    while (False == SchdIsEmpty(schd) && RUN == schd->stop_flag)
    {
        time_diff = SchdSleep(schd);
        
        if (0 >= time_diff)
        {
            task = PQueuePeek(schd->p_queue);
            PQueueDequeue(schd->p_queue);
            run_time = TaskRunTask(task);
            ++count;
            
            if (0 < run_time)
            {
                TaskSetTime(task, run_time);
                if (FAILURE == PQueueEnqueue(schd->p_queue, task))
                {
                    TaskRemoveElement(task);
                    return (ALLOCATION_ERROR);
                }
            }
            else
            {
                TaskRemoveElement(task);
                if (TASK_FAILURE == run_time)
                {
                    return (TASK_FAILURE);
                }
            }
        }
    }
    
    if (STOP == schd->stop_flag)
    {
        return (STOP_FLAG_USED);
    }
    
    return (count);   
}


int SchdIsBadUID(uuid_t uid)
{
    return (UUIDIsBadUID(uid));
}


static time_t SchdSleep(scheduler_t *schd)
{
    time_t time_diff = 0;
    
    assert(NULL != schd);
    
    time_diff = difftime(TaskGetTime(PQueuePeek(schd->p_queue)), 
                             time(NULL));
    if (time_diff > 0)
    {
        sleep(time_diff);
        time_diff = difftime(TaskGetTime(PQueuePeek(schd->p_queue)),
                             time(NULL));
    }
    
    return (time_diff);
}


static int CompareTaskTimes(const void *task,
                           const void *new_task, 
                           void *param)
{
	assert(NULL != task);
	assert(NULL != new_task);
	
	(void)param;
	
	return (TaskGetTime(task) > TaskGetTime(new_task));
}

int SchdIsMatchFunc(const void *task, const void *uid, const void *param)
{
    (void)param;
    
    assert(NULL != task);
    assert(NULL != uid);
    
    return (UUIDIsSameUID(TaskGetUUID(task), *(uuid_t*)uid));
}
