#ifndef ILRD_SLOGGER_HPP
#define ILRD_SLOGGER_HPP

#include <boost/thread/mutex.hpp>   /* boost mutex */
#include "logger.hpp"               /* logger */

namespace ilrd
{

class Slogger
{
public:
    ~Slogger();
    static Logger& GetInstance();
    
private:
    Slogger();
    static Logger *m_slogger;
    static boost::mutex m_lock;
    //static void ClearSlogger();
};

} // ilrd

#endif
