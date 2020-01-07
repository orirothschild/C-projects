#include <pthread.h>

#include <stdexcept>
#include <cerrno>
#include <iostream>

#include "thread.hpp"
#include "utils.hpp"
#include "slogger_header.hpp"

namespace ilrd
{

void *Thread::ThreadFuncWrapper(void *args)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Thread: ThreadFuncWrapper" << std::endl;
    Thread *thread = reinterpret_cast<Thread *>(args);

    try
    {
       thread->m_func();
    }
    catch(const SelfTermination& e)
    {
        //std::cout << "exception received" << std::endl;
        //thread->m_isActive = false;  /* for Decrease */
    }

    return nullptr;
}

Thread::Thread(ThreadFunc function)
: m_func(function)
//, m_isActive(true) /* for Decrease */
, m_isJoinable(true)
, m_id(CreateThread())
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Thread: Ctor" << std::endl;
}

pthread_t Thread::CreateThread()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Thread: CreateThread" << std::endl;


    pthread_t threadID = {0};

    int retval = pthread_create(&threadID, NULL, ThreadFuncWrapper, this);
    if (SUCCESS != retval)
    {
        switch (errno)
        {
            case (EAGAIN) :
                throw InsufficientResources();
                break;
            case (EINVAL) :
                assert(!"Thread::CreateThread: EINVAL - Impossible Error\n");
                break;
            case (EPERM) :
                assert(!"Thread::CreateThread: EPERM - Impossible Error\n");
                break;
            default :
                assert(!"Unknown error\n");
        }
    }

    return threadID;
}

Thread::~Thread()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Thread: Dtor" << std::endl;
}

void Thread::Join()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Thread: Join" << std::endl;
    if (m_isJoinable)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Thread: Join: m_isJoinable is true" << std::endl;
        int retval = pthread_join(m_id, nullptr);
        if (SUCCESS != retval)
        {
            switch (errno)
            {
                case (EDEADLK) :
                    throw Deadlock();
                    break;
                case (ESRCH) :
                    throw SearchError();
                    break;
                case (EINVAL) :
                    assert(!"Thread::CreateThread: EINVAL - Impossible Error\n");
                    break;
                default :
                    assert(!"Unexpected Error\n");
            }
        }
        m_isJoinable = false;
    }
}

/* void Thread::Detach()
{
    int retval = pthread_detach(m_id);
    if (SUCCESS != retval)
    {
        switch(errno)
        {
            case (EINVAL) :
                assert(!"Thread::CreateThread: EINVAL - Impossible Error\n");
                break;
            case (ESRCH) :
                throw SearchError();
                break;
            default :
                assert(!"Unexpected Error\n");
        }
    }
    m_isActive = false;
} */

/* void Thread::Exit()
{
    std::cout << "before detach" <<std::endl;
    //Detach();
    //m_isActive = false;
    throw SelfTermination();
    
    //pthread_exit(nullptr);
    //std::cout << "after detach" <<std::endl;
} */

bool Thread::GetActiveState() const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Thread: GetActiveState" << std::endl;


    return m_isActive;
}


} // ilrd
