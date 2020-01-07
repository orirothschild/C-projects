#ifndef ILRD_SLL_TEST_H
#define ILRD_SLL_TEST_H

int TestSLListCreateNode();
int TestSLListInsertAfter_TwoNodes();
int TestSLListInsert_TwoNodes();
int TestSLListInsert_TwoNodesCheckNextNode();

int TestSLListInsertAfter_ManyNodes();
int TestSLListInsertAfter_ManyNodesCheckNextNode();
int TestSLListInsert_ManyNodes();
int TestSLListInsert_ManyNodesCheckNextNode();

int TestSLListRemoveAfter_TwoNodesReturn();
int TestSLListRemove_TwoNodes();
int TestSLListRemove_TwoNodesCheckNextNode();
int TestSLListRemoveAfter_ManyNodes();
int TestSLListRemoveAfter_ManyNodesCheckNextNode();
int TestSLListRemove_ManyNodes();
int TestSLListRemove_ManyNodesCheckNextNode();

int TestSLListHasLoop_True();
int TestSLListHasLoop_False();


int TestSLListFind_True();
int TestSLListFind_False();
int TestSLListForEach_True();
int TestSLListForEach_False();

int TestSLListFlipFive();
int TestSLListCountFive();
int TestSLListHasIntersectionTrue();
int TestSLListHasIntersectionFalse();
int TestSLListHasIntersectionSubList();

#endif
