#ifndef ILRD_TIMER_HPP
#define ILRD_TIMER_HPP

#include <queue>                    /* priority_queue */
#include <vector>                   /* vector */
#include <boost/chrono.hpp>         /* nanoseconds */
#include <boost/function.hpp>       /* boost function */

#include "reactor_header.hpp"       /* API */
#include "utils.hpp"                /* utils */

namespace ilrd
{

class Timer : private Uncopyable
{
public:
    explicit Timer(Reactor& reactor);
    ~Timer() noexcept;

    typedef boost::function<void (int)> boostFunction;
    typedef boost::chrono::nanoseconds nanoSecs;
    typedef std::pair<nanoSecs, boostFunction> pqPair;
    typedef boost::function<void (void)> uFunc;
    typedef boost::chrono::high_resolution_clock::time_point timePoint;

    void Add(nanoSecs time_ns, boostFunction f);

private:
    class TimerComparator //: private Uncopyable
    {
    public:
        bool operator()(Timer::pqPair lhs, Timer::pqPair rhs) const noexcept
        {
            return lhs.first > rhs.first;
        }
    private:
    };

    class FDProxy
    {
    public:
        explicit FDProxy();
        ~FDProxy();

        int GetFD() const noexcept;

    private:
        int m_fd;

        int CreateTimerFd();
    };

    typedef std::priority_queue<pqPair, std::vector<pqPair>, TimerComparator> timerpq;

    Reactor& m_reactor;
    timerpq m_pq;
    FDProxy m_timerFD;

    void ReactorPerformFunc(int fd);
    void ReRegisterTimer();
    void DeRegisterTimer();

    static const long NANOSECONDS = 1000000000;
};

} // ilrd

#endif // ILRD_TIMER_HPP
