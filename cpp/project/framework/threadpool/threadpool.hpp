#ifndef ILRD_THREADPOOL_HPP
#define ILRD_THREADPOOL_HPP

#include <vector>

#include "boost/thread/mutex.hpp"   /* mutex */
#include "boost/shared_ptr.hpp"     /* shared pointer */
#include "boost/atomic.hpp"         /* atomic, barrier */

#include "waitablequeue_header.hpp" /* API */
#include "thread_header.hpp"        /* API */
#include "reverse_semaphore.hpp"    /* API */
#include "utils.hpp"


namespace ilrd
{

class ThreadPool : public Uncopyable
{
private:
    class BadApple;
public:
    typedef boost::shared_ptr<Thread> SharedThread;
    typedef std::vector<SharedThread> ThreadPoolContainer;
    typedef WaitableQueue<ThreadFunc> TasksQueue;

    explicit ThreadPool(unsigned long numOfThreads = 1);
    ~ThreadPool();

    void AddTask(ThreadFunc function, WaitableQueue<ThreadFunc>::WQPriority priority);
    void IncPoolSize(unsigned long toAdd = 1);
    void DecPoolSize(unsigned long toRemove = 1);
    
    bool Shutdown(unsigned long maxWaitTime);
    size_t ThreadCount() const;

    void Pause();
    void Resume();
    void TestKillThreads();
    
    struct ShutdownException : public std::runtime_error
    {
        explicit ShutdownException(const char *msg = "ShutdownExcpetion\n");
    };
        
private:
    boost::atomic<bool> m_pauseFlag;
    ThreadFunc m_taskWrapper;
    ThreadPoolContainer m_threads;
    TasksQueue m_tasks;
    size_t m_threadsCounter;
    
    boost::condition_variable m_threadsTerminate;
    boost::mutex m_terminateMutex;

    boost::mutex m_lock;
    boost::condition_variable m_condVar;
    
    void TaskWrapper();
    void ShutdownTask(size_t threadsNum);
    void CreateThreads(unsigned long numOfThreads);
    void PoisonedApple(/* SharedThread thread */);
    void PauseTask();
    bool PauseFlag();
    bool Wait(unsigned long maxWaitTime);

};

} // ilrd


#endif // ILRD_THREADPOOL_HPP