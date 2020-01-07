#include <iostream>
#include <assert.h>

#include "stack.hpp"
#include "./../../../../utils.h"/*  home/hadar/hadar-klein/cpp/utils.h" */

int TESTBuildStackAddTwoAndPopOne();
int TESTBuildStackAddTwo();
int TESTStackCount();
int TESTStackIsEmpty();
int TESTStackAssignment();
int TESTStackCCtor();

int main()
{
    RUN_TEST(TESTBuildStackAddTwoAndPopOne());
    RUN_TEST(TESTBuildStackAddTwo());
    RUN_TEST(TESTStackCount());
    RUN_TEST(TESTStackIsEmpty());
    RUN_TEST(TESTStackAssignment());
    RUN_TEST(TESTStackCCtor());
    
    return 0;
}


int TESTBuildStackAddTwoAndPopOne()
{
    int input1 = 5;
    int input2 = 9;
    Stack<int> *stack = new Stack<int>();
    
    stack->Push(input1);
    stack->Push(input2);

    stack->Pop();

    if (5 == stack->Top())
    {
        delete stack;
        return PASS;
    }

    delete stack;
    return FAIL;
}


int TESTBuildStackAddTwo()
{
    int input1 = 5;
    int input2 = 9;
    Stack<int> *stack = new Stack<int>();

    stack->Push(input1);
    stack->Push(input2);

    if (9 == stack->m_dummy.m_next->GetData())
    {
        delete stack;
        return PASS;    
    }

    delete stack;
    return FAIL;
}


int TESTStackCount()
{
    int input1 = 5;
    int input2 = 9;
    Stack<int> *stack = new Stack<int>();

    stack->Push(input1);
    stack->Push(input2);

    if (2 == stack->Count())
    {
        delete stack;
        return PASS;    
    }

    delete stack;
    return FAIL;
}


int TESTStackIsEmpty()
{
    Stack<int> *stack = new Stack<int>();

    if (stack->IsEmpty())
    {
        delete stack;
        return PASS;    
    }

    delete stack;
    return FAIL;
}


int TESTStackAssignment()
{
    int input1 = 5;
    int input2 = 9;
    Stack<int> stack1;
    Stack<int> stack2;

    stack1.Push(input1);
    stack1.Push(input2);

    stack2 = stack1;

    while (!stack1.IsEmpty())
    {
        if (stack1.Top() != stack2.Top())
        {
            return FAIL;
        } 
        stack1.Pop();
        stack2.Pop();
    }

    return PASS;
}


int TESTStackCCtor()
{
    int input1 = 5;
    int input2 = 9;
    Stack<int> stack1;

    stack1.Push(input1);
    stack1.Push(input2);

    Stack<int> stack2(stack1);

    while (!stack1.IsEmpty())
    {
        if (stack1.Top() != stack2.Top())
        {
            return FAIL;
        } 
        stack1.Pop();
        stack2.Pop();
    }

    return PASS;
}