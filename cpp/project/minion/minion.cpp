
#include "minion.hpp"   /* minion */
#include "slogger_header.hpp"    /* logger */

namespace ilrd
{

Minion::Minion(const char *port, const char *address)
: m_fd(address, port)
, m_router(m_reactor, m_alloced_space)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Minion: Ctor" << std::endl;
    
    RegistrMinionInReactor();
}

Minion::~Minion()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Minion: Dtor" << std::endl;
}

void Minion::Start()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Minion: Start" << std::endl;
    m_reactor.Start();
}
void Minion::RegistrMinionInReactor()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Minion: Register" << std::endl;
    
    m_reactor.Add(READ, m_fd.GetFD(), boost::bind(&Router::Do, &m_router, _1));
}

} // ilrd