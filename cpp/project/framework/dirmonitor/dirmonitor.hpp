//
// Created by student on 4/29/19.
//

#ifndef ILRD_DIRMONITOR_HPP
#define ILRD_DIRMONITOR_HPP

#include <string>
#include <boost/function.hpp>

#include "reactor_header.hpp"
#include "dirmonitorfd.hpp"

namespace ilrd
{


class DirMonitor
{
public:
    typedef boost::function<void (std::string)> LoaderFunction;
    
    explicit DirMonitor(Reactor& reactor, const std::string& path, LoaderFunction function);
    ~DirMonitor();

    void MonitorDirectory(int fd);
    void RegisterToReactor();

private:
    Reactor& m_reactor;
    LoaderFunction m_loaderFunction;
    DirMonitorFD m_initfd;
    DirMonitorFD m_watchfd;

};

}

#endif //HADAR_KLEIN_DIRMONITOR_HPP
