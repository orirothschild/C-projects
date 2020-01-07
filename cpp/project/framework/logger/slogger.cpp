
#include "boost/atomic.hpp"
#include "slogger.hpp"  /* slogger */


namespace ilrd
{

Logger *Slogger::m_slogger = 0;
boost::mutex Slogger::m_lock;

Logger& Slogger::GetInstance()
{
    Logger *temp_logger = m_slogger;
    boost::atomic_thread_fence(boost::memory_order_acquire);
    if (!m_slogger)
    {
        m_lock.lock();
        temp_logger = m_slogger;
        if (!m_slogger)
        {
            temp_logger = new Logger(DevNull().GetNull(), Logger::ERROR);
            boost::atomic_thread_fence(boost::memory_order_release);
            m_slogger = temp_logger;
        }
        m_lock.unlock();
        //atexit(ClearSlogger);
    }

    return *temp_logger;
}

/* void Slogger::ClearSlogger()
{
    delete m_slogger;
} */

}


