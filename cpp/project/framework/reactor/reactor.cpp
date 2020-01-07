#include <cstring>                  /* strerror */
#include <errno.h>                  /* errno */

#include "reactor.hpp"              /* API */
#include "utils.hpp"                /* utils */

#include "reactor_exceptions.hpp"   /* API */

namespace ilrd
{

Reactor::Reactor()
: m_flag(FSTOP)
, m_listener()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Ctor" << std::endl;
}

Reactor::~Reactor() noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Dtor" << std::endl;
}

void Reactor::Add(Mode mode, int fd, bfunc func)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Mode: " << mode << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: FD: " << fd << std::endl;

    using namespace reactor;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add1" << std::endl;
    if (func.empty())
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add2" << std::endl;
        Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add: Empty Function" << std::endl;
        throw ExceptionEmptyFunction();
    }
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add3" << std::endl;
    if (0 > fd || fd > FD_SETSIZE)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add4" << std::endl;
        Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add: Bad FD" << std::endl;
        throw ExceptionBadFD();
    }
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add5" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add: address of func" << &func << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add: mode: " << mode << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add: fd: " << fd << std::endl;

    /* paired_int pairdint(mode, 15);
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add8a" << std::endl;
    std::pair<paired_int, bfunc> blerg(pairdint, func);
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add8b" << std::endl;

    std::pair<Container::iterator, bool> retval = m_container.insert(blerg);
 */
    std::pair<Container::iterator, bool> retval = 
                 m_container.insert(std::make_pair(paired_int(mode, fd), func));
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add8c" << std::endl;
    if (!retval.second)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add6" << std::endl;
        Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add: Duplicate key" << std::endl;
        throw ExceptionDuplicateKey();
    }
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Add7" << std::endl;
}

void Reactor::Remove(Mode mode, int fd) noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Remove" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Remove: mode: " << mode << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Remove: fd: " << fd << std::endl;

    m_container.erase(std::pair<Mode, int>(mode, fd));
}

void Reactor::Start()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Start" << std::endl;

    m_flag = FSTART;

    while(m_flag)
    {
        listenervector vec;
        PrepareListenerVector(vec);

        vec = m_listener.Wait(vec);
        
        PerformUserFunction(vec);
        //sleep(0.5);
    }
}

void Reactor::Stop() noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: Stop" << std::endl;

    m_flag = FSTOP;
}

void Reactor::PrepareListenerVector(listenervector& vec) const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: PrepareListenerVector" << std::endl;
    
    Container::const_iterator iter;

    for (iter = m_container.begin(); iter != m_container.end(); ++iter)
    {
        vec.push_back(iter->first);
    }
}

void Reactor::PerformUserFunction(listenervector& vec)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reactor: PerformUserFunction" << std::endl;
    
    listenervector::iterator liter;
    Container::iterator riter;

    for (liter = vec.begin(); liter != vec.end(); ++liter)
    {
        riter = m_container.find(*liter);
        if (riter != m_container.end())
        {
            riter->second(liter->second);
        }
    }
}

}//end ilrd
