/* RC15 */
#ifndef ILRD_TASK_H
#define ILRD_TASK_H


#include <time.h>
#include "uuid.h"



typedef struct task task_t;

typedef  time_t (*task_func_t)(void *param);

/*
struct task
{
    task_func_t command;
    void *param;
    time_t time;
    uuid_t uid;
};
*/


/*
* Creates a new task
* Return Value: returns a pointer to the created task, 
                NULL if allocation failure
* Parameters  : 
* Input       : command cannot be NULL
                time must be > 0
* Time Complexity : O(1)
*/
task_t *TaskCreateElement(const task_func_t command, 
                          void *param,
                          time_t time);


/*
* Destroys a task
* Return Value: 
* Parameters  : task: a task element
* Input       : schd and task cannot be NULL
* Time Complexity : O(1)
*/
void TaskRemoveElement(task_t *task);


/*
* Returns the scheduled time of the task 
* Return Value: returns the scheduled time in seconds since the epoch
* Parameters  : task: a task element
* Input       : task cannot be NULL
* Time Complexity : O(1)
*/
time_t TaskGetTime(const task_t *task);


/*
* Returns the uuid of the given task 
* Return Value: returns the uuid
* Parameters  : task: a task element
* Input       : task cannot be NULL
* Time Complexity : O(1)
*/
uuid_t TaskGetUUID(const task_t *task);


/*
* Performs the task 
* Return Value: next time to run the task, 0 means not repeatable.
* Parameters  : task: a task element
* Input       : task cannot be NULL
* Time Complexity : O(1)
*/
time_t TaskRunTask(const task_t *task);


/*
* sets the time in the task
* Return Value: -
* Parameters  : task: a task element
* Input       : task cannot be NULL
* Time Complexity : O(1)
*/
void TaskSetTime(task_t *task, time_t time);


#endif /* ILRD_TASK_H */
