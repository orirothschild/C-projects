/* RC1 */
/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memset */

#include "task.h"   /* API */
#include "utils.h"  /* utilities */



struct task
{
    task_func_t command;
    void *param;
    time_t time;
    uuid_t uid;
};


task_t *TaskCreateElement(const task_func_t command, 
                          void *param,
                          time_t time)
{
    task_t *task = NULL;
    uuid_t uid = {0};
    
    assert(NULL != command);
    assert(-1 != time);
    
    uid = UUIDCreate();
    if (True == UUIDIsSameUID(uid, g_bad_uuid))
    {
        return (NULL);
    }
    
    task = (task_t *)malloc(sizeof(task_t));
    if (NULL == task)
    {
        return NULL;
    }
    
    task->command = command;
    task->param = param;
    task->time = time;
    task->uid = uid;
    
    return (task);
}


void TaskRemoveElement(task_t *task)
{    
    assert(NULL != task);
    
    memset(task, 0, sizeof(task_t));
    
    free(task);
}


time_t TaskGetTime(const task_t *task)
{
    assert(NULL != task);
    
    return (task->time);
}


uuid_t TaskGetUUID(const task_t *task)
{
    assert(NULL != task);
    
    return (task->uid);
}


time_t TaskRunTask(const task_t *task)
{
    assert(NULL != task);
  
    return (task->command(task->param));
}


void TaskSetTime(task_t *task, time_t time)
{
    assert(NULL != task);
    
    task->time = time;
}
