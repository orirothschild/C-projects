#ifndef ILRD_MINION_HPP
#define ILRD_MINION_HPP

#include <netdb.h>              /* sockaddr */
#include <stdexcept>            /* exceptions */
#include <string>               /* string */          

#include "router.hpp"           /* router */
//#include "reader.hpp"           /* reader */
//#include "writer.hpp"           /* writer */
//#include "statistician.hpp"     /* statistician */
#include "utils.hpp"            /* utils */
#include "slogger_header.hpp"   /* slogger */

//const char *PATH = "/home/student/hadar-klein/cpp/project/minion/soloadertest/innerfolder/";
const char *PATH = "./plugins/";

namespace ilrd
{

Router::Router(Reactor &reactor, MemoryBlock& allocated_space)
: m_reactor(reactor)
, m_memBlock(allocated_space)
, m_soloader(m_factory, m_reactor, PATH)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Router: Ctor " << std::endl;
}

Router::~Router()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Router: Dtor " << std::endl;
}

void Router::Do(int fd)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Router: Do " << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Router: FD: " << fd << std::endl;

    memset(&m_address, 0 , sizeof(m_address));
    m_addrLen = sizeof(m_address);

    m_receiver.ReceiveData(fd, m_read_buffer, &m_address, &m_addrLen);
    
    Slogger::GetInstance().Log(Logger::DEBUG) << "Router: Do: before factory " << std::endl;
    // create the factory and register the creators
    //Factory<char, boost::shared_ptr<Actionator> > m_factory;

    //m_factory.Register('\0', &Reader::Creator);
    //m_factory.Register('\1', &Writer::Creator);
    //m_factory.Register('S', &Statistician::Creator);
    
    // create args vector - change to a struct. Need to change in the m_factory header as well
    std::vector<void *> args;
    args.push_back(&m_reactor);
    args.push_back(&m_memBlock);
    
    boost::shared_ptr<Actionator> actionObject = m_factory.CreateObject(m_read_buffer[0], args);
    actionObject->PerformAction(fd, m_address, m_addrLen, m_read_buffer);
}

} // ilrd


#endif // ILRD_MINION_HPP