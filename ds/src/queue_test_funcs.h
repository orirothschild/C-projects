#ifndef ILRD_QUEUE_TESTS_FUNCS_H
#define ILRD_QUEUE_TESTS_FUNCS_H

int TestQueue_Create();
int TestQueue_IsEmpty_True();
int TestQueue_IsEmpty_False();

int TestQueue_Enqueue_One();
int TestQueue_Enqueue_One_Peek();
int TestQueue_Enqueue_Ten_Peek();
int TestQueue_Peek_Zero();
int TestQueue_IsEmpty1();

int TestQueue_Dequeue_First();
int TestQueue_Dequeue_Second();
int TestQueue_Dequeue_Last();

int TestQueue_Size_Three();
int TestQueue_Size_Zero();

int TestQueue_Append_Size();
int TestQueue_Append_Dequeue();
int TestQueue_Append_Dequeue_Queue2_IsEmpty();

#endif
