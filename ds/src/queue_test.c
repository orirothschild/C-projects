#include <stdio.h>  /* printf */
#include <stdlib.h> /* free   */
#include "queue.h"
#include "queue_test_funcs.h"

#define RUN_TEST(test) (!test) ? printf("FAIL : "#test"\n") : \
printf("PASS : "#test"\n")

enum {FAIL, PASS};
enum {SUCCESS, FAILURE};

int main()
{
    RUN_TEST(TestQueue_Create());
    RUN_TEST(TestQueue_IsEmpty_True());
    RUN_TEST(TestQueue_IsEmpty_False());
    printf("\n");
    RUN_TEST(TestQueue_Enqueue_One());
    RUN_TEST(TestQueue_Enqueue_One_Peek());
    RUN_TEST(TestQueue_Enqueue_Ten_Peek());
    RUN_TEST(TestQueue_Peek_Zero());
    printf("\n");
    RUN_TEST(TestQueue_Dequeue_First());
    RUN_TEST(TestQueue_Dequeue_Second());
    RUN_TEST(TestQueue_Dequeue_Last());
    printf("\n");
    RUN_TEST(TestQueue_Size_Three());
    RUN_TEST(TestQueue_Size_Zero());
    printf("\n");
    RUN_TEST(TestQueue_Append_Size());
    RUN_TEST(TestQueue_Append_Dequeue());
    RUN_TEST(TestQueue_Append_Dequeue_Queue2_IsEmpty());
    
    return (0);
}



int TestQueue_Create()
{
	queue_t *queue = QueueCreate();

	if (NULL != queue)
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_IsEmpty_True()
{
    queue_t *queue = QueueCreate();

	if (1 == QueueIsEmpty(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_IsEmpty_False()
{
    int i = 5;
    int j = 10;
	int k = 15;
	
	queue_t *queue = QueueCreate();
    
    QueueEnqueue(queue, &i);
	QueueEnqueue(queue, &j);
	QueueEnqueue(queue, &k);
	
	if (0 == QueueIsEmpty(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}

int TestQueue_Enqueue_One()
{
    int i = 5;
    
    queue_t *queue = QueueCreate();
    
	if (SUCCESS == QueueEnqueue(queue, &i))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Enqueue_One_Peek()
{
    int i = 5;
    
    queue_t *queue = QueueCreate();
    QueueEnqueue(queue, &i);
	if (5 == *(int *)QueuePeek(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Enqueue_Ten_Peek()
{
    int i = 5;
    int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int n = 30;
	int o = 35;
	int p = 40;
	int q = 45;
	int r = 50;
	
    queue_t *queue = QueueCreate();
    
    QueueEnqueue(queue, &i);
	QueueEnqueue(queue, &j);
	QueueEnqueue(queue, &k);
	QueueEnqueue(queue, &l);
	QueueEnqueue(queue, &m);
	QueueEnqueue(queue, &n);
	QueueEnqueue(queue, &o);
	QueueEnqueue(queue, &p);
	QueueEnqueue(queue, &q);
	QueueEnqueue(queue, &r);
	
	
	if (5 == *(int *)QueuePeek(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Peek_Zero()
{
    queue_t *queue = QueueCreate();
    
    if (NULL == QueuePeek(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Dequeue_First()
{
    int i = 5;
    int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int n = 30;
	int o = 35;
	int p = 40;
	int q = 45;
	int r = 50;
	
    queue_t *queue = QueueCreate();
    
    QueueEnqueue(queue, &i);
	QueueEnqueue(queue, &j);
	QueueEnqueue(queue, &k);
	QueueEnqueue(queue, &l);
	QueueEnqueue(queue, &m);
	QueueEnqueue(queue, &n);
	QueueEnqueue(queue, &o);
	QueueEnqueue(queue, &p);
	QueueEnqueue(queue, &q);
	QueueEnqueue(queue, &r);
	
	
	if (5 == *(int *)QueueDequeue(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Dequeue_Second()
{
    int i = 5;
    int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int n = 30;
	int o = 35;
	int p = 40;
	int q = 45;
	int r = 50;
	
    queue_t *queue = QueueCreate();
    
    QueueEnqueue(queue, &i);
	QueueEnqueue(queue, &j);
	QueueEnqueue(queue, &k);
	QueueEnqueue(queue, &l);
	QueueEnqueue(queue, &m);
	QueueEnqueue(queue, &n);
	QueueEnqueue(queue, &o);
	QueueEnqueue(queue, &p);
	QueueEnqueue(queue, &q);
	QueueEnqueue(queue, &r);
	
	QueueDequeue(queue);
	
	if (10 == *(int *)QueueDequeue(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Dequeue_Last()
{
    int i = 5;
    int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int n = 30;
	int o = 35;
	int p = 40;
	int q = 45;
	int r = 50;
	
    queue_t *queue = QueueCreate();
    
    QueueEnqueue(queue, &i);
	QueueEnqueue(queue, &j);
	QueueEnqueue(queue, &k);
	QueueEnqueue(queue, &l);
	QueueEnqueue(queue, &m);
	QueueEnqueue(queue, &n);
	QueueEnqueue(queue, &o);
	QueueEnqueue(queue, &p);
	QueueEnqueue(queue, &q);
	QueueEnqueue(queue, &r);
	
	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	
	if (50 == *(int *)QueueDequeue(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Size_Three()
{
    int i = 5;
    int j = 10;
	int k = 15;
		
    queue_t *queue = QueueCreate();
    
    QueueEnqueue(queue, &i);
	QueueEnqueue(queue, &j);
	QueueEnqueue(queue, &k);
		
	if (3 == QueueSize(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Size_Zero()
{
    int i = 5;
    int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int n = 30;
	int o = 35;
	int p = 40;
	int q = 45;
	int r = 50;
	
    queue_t *queue = QueueCreate();
    
    QueueEnqueue(queue, &i);
	QueueEnqueue(queue, &j);
	QueueEnqueue(queue, &k);
	QueueEnqueue(queue, &l);
	QueueEnqueue(queue, &m);
	QueueEnqueue(queue, &n);
	QueueEnqueue(queue, &o);
	QueueEnqueue(queue, &p);
	QueueEnqueue(queue, &q);
	QueueEnqueue(queue, &r);
	
	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	QueueDequeue(queue);
 	
	if (0 == QueueSize(queue))
	{
		QueueDestroy(queue);
		return (PASS);
	}
	QueueDestroy(queue);
	
	return (FAIL);
}


int TestQueue_Append_Size()
{
    int i = 5;
    int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int n = 30;
	int o = 35;
	int p = 40;
	int q = 45;
	int r = 50;
	
    queue_t *queue1 = QueueCreate();
    queue_t *queue2 = QueueCreate();
    
    
    QueueEnqueue(queue1, &i);
	QueueEnqueue(queue1, &j);
	QueueEnqueue(queue1, &k);
	QueueEnqueue(queue1, &l);
	QueueEnqueue(queue1, &m);
	QueueEnqueue(queue1, &n);
	QueueEnqueue(queue1, &o);
	
	QueueEnqueue(queue2, &p);
	QueueEnqueue(queue2, &q);
	QueueEnqueue(queue2, &r);
	
	QueueAppend(queue1, queue2);
	
	
 	
	if (10 == QueueSize(queue1))
	{
		QueueDestroy(queue1);
		QueueDestroy(queue2);
		return (PASS);
	}
	QueueDestroy(queue2);
	QueueDestroy(queue1);
	
	return (FAIL);
}




int TestQueue_Append_Dequeue()
{
    int i = 5;
    int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int n = 30;
	int o = 35;
	int p = 40;
	int q = 45;
	int r = 50;
	
    queue_t *queue1 = QueueCreate();
    queue_t *queue2 = QueueCreate();
    
    
    QueueEnqueue(queue1, &i);
	QueueEnqueue(queue1, &j);
	QueueEnqueue(queue1, &k);
	QueueEnqueue(queue1, &l);
	QueueEnqueue(queue1, &m);
	QueueEnqueue(queue1, &n);
	QueueEnqueue(queue1, &o);
	
	QueueEnqueue(queue2, &p);
	QueueEnqueue(queue2, &q);
	QueueEnqueue(queue2, &r);
	
	QueueAppend(queue1, queue2);
	
	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	QueueDequeue(queue1);
 	
	if (0 == QueueSize(queue1))
	{
		QueueDestroy(queue2);
		QueueDestroy(queue1);
		
		
		return (PASS);
	}
	QueueDestroy(queue2);
	QueueDestroy(queue1);
	
	
	return (FAIL);
}


int TestQueue_Append_Dequeue_Queue2_IsEmpty()
{
    int i = 5;
    int j = 10;
	int k = 15;
	int l = 20;
	int m = 25;
	int n = 30;
	int o = 35;
	int p = 40;
	int q = 45;
	int r = 50;
	
    queue_t *queue1 = QueueCreate();
    queue_t *queue2 = QueueCreate();
    
    
    QueueEnqueue(queue1, &i);
	QueueEnqueue(queue1, &j);
	QueueEnqueue(queue1, &k);
	QueueEnqueue(queue1, &l);
	QueueEnqueue(queue1, &m);
	QueueEnqueue(queue1, &n);
	QueueEnqueue(queue1, &o);
	
	QueueEnqueue(queue2, &p);
	QueueEnqueue(queue2, &q);
	QueueEnqueue(queue2, &r);
	
	QueueAppend(queue1, queue2);
 	
	if (0 == QueueSize(queue2))
	{
		QueueDestroy(queue2);
		QueueDestroy(queue1);
		
		
		return (PASS);
	}
	QueueDestroy(queue2);
	QueueDestroy(queue1);
	
	
	return (FAIL);
}









