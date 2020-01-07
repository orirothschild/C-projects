
#include <sys/timerfd.h>        /* timerfd_create, set */
#include <exception>            /* exceptions */
#include <stdexcept>            /* invalid_argument */
#include <boost/bind.hpp>       /* bind */
#include <boost/chrono.hpp>     /* chrono */

#include "timer.hpp"            /* API */
#include "timer_exceptions.hpp" /* exceptions */

namespace ilrd
{

Timer::Timer(Reactor& reactor)
: m_reactor(reactor)
{
    m_reactor.Add(READ, m_timerFD.GetFD(), boost::bind(&Timer::ReactorPerformFunc, this, _1));
}

Timer::~Timer() noexcept
{
    m_reactor.Remove(READ, m_timerFD.GetFD());
}

void Timer::Add(Timer::nanoSecs ns, Timer::boostFunction func)
{
    if (func.empty())
    {
        throw timer::EmptyFunction();
    }

    timePoint tp = boost::chrono::high_resolution_clock::now();
    nanoSecs now = tp.time_since_epoch();
    now += ns;

    m_pq.push(std::make_pair(now, func));
    ReRegisterTimer();
}

void Timer::ReactorPerformFunc(int fd)
{   
    timePoint tp = boost::chrono::high_resolution_clock::now();
    nanoSecs now = tp.time_since_epoch();
    
    nanoSecs action_time = m_pq.top().first;

    if (now >= action_time)
    {
        m_pq.top().second(fd);
    
        m_pq.pop();

        if (m_pq.empty())
        {
            DeRegisterTimer();
        }
        else
        {
            ReRegisterTimer();
        }   
    }
}

void Timer::ReRegisterTimer()
{
    itimerspec ts = {0, 0, 0, 0};
    ts.it_value.tv_sec = m_pq.top().first.count() / NANOSECONDS;
    ts.it_value.tv_nsec = m_pq.top().first.count() % NANOSECONDS;

    int retval = timerfd_settime(m_timerFD.GetFD(), TFD_TIMER_ABSTIME, &ts, NULL);
    if (ERROR == retval)
    {
        throw timer::BadFD();
    }
}

void Timer::DeRegisterTimer()
{
    itimerspec ts = {0, 0, 0, 0};

    int retval = timerfd_settime(m_timerFD.GetFD(), TFD_TIMER_ABSTIME, &ts, NULL);
    if (-1 == retval)
    {
        throw timer::BadFD();
    }
}

Timer::FDProxy::FDProxy()
: m_fd(CreateTimerFd())
{}

Timer::FDProxy::~FDProxy()
{
    close(m_fd);
}

int Timer::FDProxy::GetFD() const noexcept
{
    return m_fd;
}

int Timer::FDProxy::CreateTimerFd()
{
    int retval = timerfd_create(CLOCK_REALTIME, 0);
    if (-1 == retval)
    {
        throw timer::Exception();
    }

    return retval;
}

} // ilrd
