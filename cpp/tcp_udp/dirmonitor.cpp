//
// Created by student on 4/29/19.
//

#include <sys/inotify.h>    /* inotify_init */
#include <boost/bind.hpp>   /* boost bind */
#include "dirmonitor.hpp"


namespace ilrd
{

DirMonitor::DirMonitor(Reactor& reactor, const std::string& path, LoaderFunction function)
: m_reactor(reactor)
, m_loaderFunction(function)
, m_initfd()
, m_watchfd(m_initfd, path)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "DirMonitor: Ctor" << std::endl;
    
    
    RegisterToReactor();
}


DirMonitor::~DirMonitor()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "DirMonitor: Dtor" << std::endl;


    inotify_rm_watch(m_initfd.GetDirMonitorFD(), m_watchfd.GetDirMonitorFD());
}

typedef struct inotify_event NotifyEvent;
void DirMonitor::MonitorDirectory(int fd)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "DirMonitor: MonitorDirectory:" << std::endl;


    char buffer[5000];

    int retval = read(fd, buffer, sizeof(buffer));
    if (-1 == retval)
    {
        //throw things
    }

    NotifyEvent *event = reinterpret_cast<NotifyEvent *>(buffer);
    if (((event->mask & IN_MOVED_TO) || (event->mask & IN_CREATE)) && (event->len > 0))
    {
        m_loaderFunction(event->name);
    }
}

void DirMonitor::RegisterToReactor()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "DirMonitor: RegisterToReactor" << std::endl;
    
    
    Reactor::bfunc function = boost::bind(&DirMonitor::MonitorDirectory, this, _1);
    m_reactor.Add(Mode::READ, m_initfd.GetDirMonitorFD(), function);
}

} // ilrd