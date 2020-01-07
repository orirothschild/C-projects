#include <stdio.h> /* printf */

#include "multicqueue.h"
#include "multicqueue_test_funcs.h"
#include "utils.h"


int main()
{
    RUN_TEST(TEST_Create_CQ());
    RUN_TEST(TEST_Insert_3_CQ());
    RUN_TEST(TEST_Insert_11());
/*     RUN_TEST();
    RUN_TEST(); */

    return (0);
}


int TEST_Create_CQ()
{
    cqueue_t *que = NULL;

    que = CQueueCreate();

    if (NULL != que)
    {
        CQueueDestroy(que);
        return PASS;
    }

    CQueueDestroy(que);
    return FAIL;
}


int TEST_Insert_3_CQ()
{
    cqueue_t *que = NULL;

    que = CQueueCreate();
    CQueueEnqueue(que, 1);
    CQueueEnqueue(que, 2);
    CQueueEnqueue(que, 3);

    PrintQueue(que);

    if (NULL != que)
    {
        CQueueDestroy(que);
        return PASS;
    }

    CQueueDestroy(que);
    return FAIL;
}


int TEST_Insert_11()
{
    cqueue_t *que = NULL;

    que = CQueueCreate();

    CQueueEnqueue(que, 1);
    CQueueEnqueue(que, 2);
    CQueueEnqueue(que, 3);
    CQueueEnqueue(que, 4);
    CQueueEnqueue(que, 5);
    CQueueEnqueue(que, 6);
    CQueueEnqueue(que, 7);
    CQueueEnqueue(que, 8);
    CQueueEnqueue(que, 9);
    CQueueDequeue(que);
    CQueueEnqueue(que, 10);
    CQueueEnqueue(que, 11);

    PrintQueue(que);

    if (NULL != que)
    {
        CQueueDestroy(que);
        return PASS;
    }

    CQueueDestroy(que);
    return FAIL;
}


