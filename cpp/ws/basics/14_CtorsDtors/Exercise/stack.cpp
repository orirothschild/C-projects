/* #include <iostream>
#include <assert.h>

#include "stack.hpp"
#include "./../../../../utils.h"


Stack::Node::Node()
: m_data(0)
, m_next(NULL)
{}

Stack::Node::Node(DataType data, const Stack::Node *next)
: m_data(data)
, m_next(NULL)
{
    m_next = next;
}

DataType Stack::Node::GetData() const
{
    return m_data;
}

bool Stack::Node::HasNext() const
{
    return NULL != m_next;
}

const Stack::Node& Stack::Node::GetNext() const
{
    return *m_next;
}

Stack::Stack()
{
    m_dummy.m_next = NULL;
}

static void EmptyStack(Stack& stack)
{
    while (false == stack.IsEmpty())
    {
        stack.Pop();
    }
}

Stack::~Stack()
{
    EmptyStack(*this);
}

static void StackCopy(Stack& stack, const Stack& other_)
{
    int count = other_.Count();
    
    const Stack::Node *iter = (Stack::Node *)other_.m_dummy.m_next;
    for (int i = 0; i < count; ++i)
    {
        DataType data = iter->GetData();
        stack.Push(data);
        iter = &iter->GetNext();
    }
}

Stack::Stack(const Stack& other_)
{
    Stack newStack;
    StackCopy(newStack, other_);
    StackCopy(*this, newStack);
}

Stack& Stack::operator=(const Stack& other_)
{
    Stack newStack;
    StackCopy(newStack, other_);
    EmptyStack(*this);
    StackCopy(*this, newStack);

    return *this;
}

void Stack::Push(DataType data)
{
    Node *new_node = new Node(data, m_dummy.m_next);
    m_dummy.m_next = new_node;
}

void Stack::Pop()
{
    assert(NULL != m_dummy.m_next);
    
    const Node *node_to_destruct = m_dummy.m_next;
    m_dummy.m_next = node_to_destruct->m_next;
    delete node_to_destruct;
}

DataType Stack::Top() const
{
    return m_dummy.m_next->m_data;
}

size_t Stack::Count() const
{
    int counter(0);
    const Node *node_runner = &m_dummy;

    while(node_runner->HasNext())
    {
        ++counter;
        node_runner = &node_runner->GetNext();
    }

    return counter;
}

bool Stack::IsEmpty() const
{
    return NULL == m_dummy.m_next;
} */
