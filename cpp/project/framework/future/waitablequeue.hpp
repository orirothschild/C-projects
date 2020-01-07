#ifndef ILRD_WAITABLEQUEUE_HPP
#define ILRD_WAITABLEQUEUE_HPP

#include <queue>

#include "boost/thread/mutex.hpp"
#include "boost/thread/condition_variable.hpp"
#include "utils.hpp"

namespace ilrd
{

template<typename T>
class WaitableQueue : public Uncopyable
{
public:  
    enum WQPriority
    {
        SHUTDOWN = 0,
        PAUSE = SHUTDOWN,
        HIGH,
        MED,
        LOW,
        NUM_OF_PRIORITYS
    };
    /* explicit WaitableQueue();
    ~WaitableQueue(); */

    void Push(const T& t, WQPriority priority);
    void Pop(T& poppedValue);
    //bool IsEmpty() const;

private:
    typedef std::pair<T, WQPriority> WPQPair;
    
    class Comparator
    {
    public:
        bool operator()(const WPQPair& lhs, const WPQPair& rhs);
    };
    
    std::priority_queue<WPQPair, std::vector<WPQPair>, Comparator> m_wpq;
    boost::mutex m_lock;
    boost::condition_variable m_conditionVar;
};

template <typename T>
bool WaitableQueue<T>::Comparator::operator()(const WPQPair& lhs, const WPQPair& rhs)
{
    return lhs.second > rhs.second;
}

/* template <typename T>
WaitableQueue<T>::WaitableQueue()
{}

template<typename T>
WaitableQueue<T>::~WaitableQueue()
{} */

template<typename T>
void WaitableQueue<T>::Push(const T& t, WQPriority priority)
{
    {
        boost::mutex::scoped_lock lock(m_lock);
        m_wpq.push(WPQPair(t, priority));
    }

    m_conditionVar.notify_all();
}

template<typename T>
void WaitableQueue<T>::Pop(T& poppedValue)
{
    boost::mutex::scoped_lock lock(m_lock);
    while (m_wpq.empty())
    {
        m_conditionVar.wait(lock);
    }

    poppedValue = m_wpq.top().first;
    m_wpq.pop();
}

/* template<typename T>
bool WaitableQueue<T>::IsEmpty() const
{
    boost::mutex::scoped_lock lock(m_lock);
    return m_wpq.empty();
} */

} // ilrd

#endif // ILRD_WAITABLEQUEUE_HPP
