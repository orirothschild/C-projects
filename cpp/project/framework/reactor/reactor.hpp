#ifndef ILRD_REACTOR_HPP
#define ILRD_REACTOR_HPP

#include <vector>               /* vector */
#include <map>                  /* map */
#include <boost/function.hpp>   /* boost function */

#include "listener.hpp"         /* API */
#include "slogger_header.hpp"    /* logger */
#include "utils.hpp"            /* utils */


namespace ilrd
{

class Reactor : private Uncopyable
{
public:
    Reactor();
    ~Reactor() noexcept;

    typedef boost::function <void (int)> bfunc;
    typedef std::pair<Mode, int> paired_int;
    typedef std::map<paired_int, bfunc> Container;
    typedef Listener::listenervector listenervector;

    
    void Add(Mode mode, int fd, bfunc func);
    void Remove(Mode mode, int fd) noexcept;
    void Start();
    void Stop() noexcept;

private:
    bool m_flag;
    Container m_container;
    Listener m_listener;
    
    void PrepareListenerVector(listenervector& vec) const;
    void PerformUserFunction(listenervector& vec);

    enum state
    {
        FSTOP = 0,
        FSTART
    };
};

}//end ilrd

#endif //ILRD_REACTOR_HPP
