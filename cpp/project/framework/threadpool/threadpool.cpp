

#include <stdlib.h>

#include <iostream>

#include "boost/bind.hpp"   /* boost bind */
#include "threadpool.hpp"   /* API */
#include "slogger_header.hpp"

typedef boost::chrono::high_resolution_clock hiResClock;

namespace ilrd
{

ThreadPool::ThreadPool(unsigned long numOfThreads)
: m_pauseFlag(true)
, m_taskWrapper(boost::bind(&ThreadPool::TaskWrapper, this))
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: Ctor" << std::endl;
    CreateThreads(numOfThreads);
}

void ThreadPool::CreateThreads(unsigned long numOfThreads)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: CreateThreads" << std::endl;
    for (unsigned long i = 0; i < numOfThreads; ++i)
    {
        SharedThread thread(new Thread(m_taskWrapper));
        m_threads.push_back(thread);
    }
}

ThreadPool::~ThreadPool()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: Dtor" << std::endl;
    
    
    //static int i = 0;
    //int numOfThreads = m_threads.size();

    /* for (int i = 0; i < numOfThreads; ++i)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: Dtor: i: " << i << std::endl;

        m_threads[i].get()->Join();
    } */
    ThreadPoolContainer::iterator iter;
    for (iter = m_threads.begin(); iter != m_threads.end(); ++iter)
    {
        //Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: Dtor: i: " << i << std::endl;
        
        (*iter)->Join();
        //++i;
    
        /* if ((*iter)->GetActiveState() == false)
        {
            std::cout << "dtor counter is: " << ++i << std::endl;    
            m_threads.erase(iter);
        } */
    }
    
    //m_threads.clear();
}


void ThreadPool::TestKillThreads()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: TestKillThreads" << std::endl;
    /* static int i = 0;
    ThreadPoolContainer::iterator iter;
    for (iter = m_threads.begin(); iter != m_threads.end(); ++iter)
    {
        if ((*iter)->GetActiveState() == false)
        {
            std::cout << "dtor counter is: " << ++i << std::endl;
            m_threads.erase(iter);
        }
    } */

    m_threads.clear();
}

/* Future<void> */void ThreadPool::AddTask(ThreadFunc function, WaitableQueue<ThreadFunc>::WQPriority priority)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: AddTask" << std::endl;
    //Future<void> future = std::async(function);
    
    //1. create promise object
    //2. take function and create new boost function that binds it with promis object
    //3. get future from promise object
    //4. Push new binded function
    //4. return future object

    m_tasks.Push(function, priority);

    //return future;
}

void ThreadPool::IncPoolSize(unsigned long toAdd)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: IncPoolSize" << std::endl;


    CreateThreads(toAdd);
}

void ThreadPool::DecPoolSize(unsigned long toRemove)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: DecPoolSize" << std::endl;


    UNUSED(toRemove);
}

bool ThreadPool::Shutdown(unsigned long maxWaitTime)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: Shutdown" << std::endl;


    m_threadsCounter = ThreadCount();
    Thread thread(boost::bind(&ThreadPool::ShutdownTask, this, m_threadsCounter));
    
    bool retval = Wait(maxWaitTime);
    thread.Join();

    return retval;
}

bool ThreadPool::Wait(unsigned long maxWaitTime)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: Wait" << std::endl;
    

    hiResClock::time_point finishTime = hiResClock::now() +
                                        boost::chrono::seconds(maxWaitTime);

    boost::unique_lock<boost::mutex> lock(m_terminateMutex);
    bool retval = static_cast<bool>(m_threadsTerminate.wait_until(lock, finishTime));
    if (0 == retval)
    {
        return true;
    }
    return false;
}

void ThreadPool::ShutdownTask(size_t threadsNum)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: ShutdownTask" << std::endl;


    ThreadFunc poisonedApple = boost::bind(&ThreadPool::PoisonedApple, this);
    for (size_t i = 0; i < threadsNum; ++i)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: ShutdownTask: addtask i: " << i << std::endl;
        
        
        AddTask(poisonedApple, WaitableQueue<ThreadFunc>::SHUTDOWN);
    }
}

void ThreadPool::PoisonedApple(/* SharedThread thread */)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: PoisonedApple" << std::endl;


    throw ShutdownException();
}

size_t ThreadPool::ThreadCount() const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: ThreadCount" << std::endl;


    return m_threads.size();
}

void ThreadPool::TaskWrapper()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: TaskWrapper" << std::endl;


    ThreadFunc function;

    while (true/* m_pauseFlag.load(boost::memory_order_consume) || PauseFlag() */)
    {
        m_tasks.Pop(function);
        try
        {
            Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: TaskWrapper: function" << std::endl;
            function();
        }
        catch(const ThreadPool::ShutdownException& e)
        {            
            {
                boost::mutex::scoped_lock lock(m_terminateMutex);
                Slogger::GetInstance().Log(Logger::INFO) << "ThreadPool: TaskWrapper: m_threadCounter: " << m_threadsCounter << std::endl;
                --m_threadsCounter;
            }
            
            if (0 >= m_threadsCounter)
            {
                m_threadsTerminate.notify_one();
            }
            //std::cout << "blerg" << std::endl;
            throw SelfTermination();
        }
        catch(...)
        {
            continue;
            //IncPoolSize(1);
        }
    }
    //std::cout << "threadId is: " << pthread_self() << std::endl;
}

void ThreadPool::Pause()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: Pause" << std::endl;


    if (m_pauseFlag.load(boost::memory_order_consume) == true)
    {
        int numOfThreads = m_threads.size();
        Slogger::GetInstance().Log(Logger::INFO) << "ThreadPool: Pause: size: " << numOfThreads << std::endl;

        m_pauseFlag.store(false, boost::memory_order_release);
        for (int i = 0; i < numOfThreads; ++i)
        {
            ThreadFunc function = boost::bind(&ThreadPool::PauseTask, this);
            AddTask(function, WaitableQueue<ThreadFunc>::PAUSE);
        }
    }
    
}

void ThreadPool::Resume()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: Resume" << std::endl;
    m_pauseFlag.store(true, boost::memory_order_release);
    m_condVar.notify_all();
}

bool ThreadPool::PauseFlag()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: PauseFlag" << std::endl;
    boost::mutex::scoped_lock lock(m_lock);
    m_condVar.wait(lock);
    
    return true;
}

void ThreadPool::PauseTask()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "ThreadPool: PauseTask" << std::endl;
    boost::mutex::scoped_lock lock(m_lock);
    if (m_pauseFlag.load(boost::memory_order_consume) == false)
    {
        Slogger::GetInstance().Log(Logger::INFO) << "ThreadPool: PauseTask: " << std::endl;
        m_condVar.wait(lock);
    }
}



ThreadPool::ShutdownException::ShutdownException(const char *msg)
: std::runtime_error(msg)
{}

} // ilrd
