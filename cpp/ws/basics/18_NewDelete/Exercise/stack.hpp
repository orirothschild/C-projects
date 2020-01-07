#ifndef ILRD_STACK_H
#define ILRD_STACK_H

#include <iostream>
#include <assert.h>

#include "./../../../../utils.h"

/* typedef int DataType; */
template  <typename DataType>
class Stack
{
public:
    explicit Stack();
    Stack(const Stack& other_);
    Stack& operator=(const Stack& other_);
    ~Stack();
    

    void Push(DataType data);
    void Pop();
    DataType Top() const;
    size_t Count() const;
    bool IsEmpty() const;

    struct Node
    {
        explicit Node();
        explicit Node(const DataType data, const Node *next);
        
        DataType GetData() const;
        bool HasNext() const;
        const Node &GetNext() const;

        const DataType m_data;
        const Node *m_next;
    };

    Node m_dummy;
};

template<typename DataType>
Stack<DataType>::Node::Node()
: m_data(0)
, m_next(NULL)
{}

template<typename DataType>
Stack<DataType>::Node::Node(DataType data, const Stack<DataType>::Node *next)
: m_data(data)
, m_next(NULL)
{
    m_next = next;
}

template<typename DataType>
DataType Stack<DataType>::Node::GetData() const
{
    return m_data;
}

template<typename DataType>
bool Stack<DataType>::Node::HasNext() const
{
    return NULL != m_next;
}

template<typename DataType>
const typename Stack<DataType>::Node& Stack<DataType>::Node::GetNext() const
{
    return *m_next;
}

template<typename DataType>
Stack<DataType>::Stack()
{
    m_dummy.m_next = NULL;
}

template<typename DataType>
static void EmptyStack(Stack<DataType>& stack)
{
    while (false == stack.IsEmpty())
    {
        stack.Pop();
    }
}

template<typename DataType>
Stack<DataType>::~Stack()
{
    EmptyStack(*this);
}

template<typename DataType>
static void StackCopy(Stack<DataType>& stack, const Stack<DataType>& other_)
{
    int count = other_.Count();
    
    const typename Stack<DataType>::Node *iter = /* (Stack<DataType>::Node *) */other_.m_dummy.m_next;
    for (int i = 0; i < count; ++i)
    {
        DataType data = iter->GetData();
        stack.Push(data);
        iter = &iter->GetNext();
    }
}

template<typename DataType>
Stack<DataType>::Stack(const Stack<DataType>& other_)
{
    Stack newStack;
    StackCopy(newStack, other_);
    StackCopy(*this, newStack);
}

template<typename DataType>
Stack<DataType>& Stack<DataType>::operator=(const Stack<DataType>& other_)
{
    Stack newStack;
    StackCopy(newStack, other_);
    EmptyStack(*this);
    StackCopy(*this, newStack);

    return *this;
}

template<typename DataType>
void Stack<DataType>::Push(DataType data)
{
    Node *new_node = new Node(data, m_dummy.m_next);
    m_dummy.m_next = new_node;
}

template<typename DataType>
void Stack<DataType>::Pop()
{
    assert(NULL != m_dummy.m_next);
    
    const Node *node_to_destruct = m_dummy.m_next;
    m_dummy.m_next = node_to_destruct->m_next;
    delete node_to_destruct;
}

template<typename DataType>
DataType Stack<DataType>::Top() const
{
    return m_dummy.m_next->m_data;
}

template<typename DataType>
size_t Stack<DataType>::Count() const
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

template<typename DataType>
bool Stack<DataType>::IsEmpty() const
{
    return NULL == m_dummy.m_next;
}



#endif  //STACK_H