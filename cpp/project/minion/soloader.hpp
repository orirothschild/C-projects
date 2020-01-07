//
// Created by student on 4/29/19.
//

#ifndef ILRD_SOLOADER_HPP
#define ILRD_SOLOADER_HPP

#include <vector>                   /* vector */
#include <dlfcn.h>                  /* dlclose */
#include <string>   

#include "actionator.hpp"           /* actionator */
#include "factory_header.hpp"       /* factory API */
#include "dirmonitor_header.hpp"    /* dirmonitor API */
#include "reactor_header.hpp"


namespace ilrd
{

class SoLoader /* : public Uncopyable */
{
public:

    explicit SoLoader(Factory<char, boost::shared_ptr<Actionator> >& factory, Reactor& reactor, const std::string& path);
    ~SoLoader();

    void Connect(const std::string& str);

private:
    void LoadSoAtStartUp();

    class DLHandler 
    {
    public:
        /* not explicit */DLHandler(void *handler)
        : m_handler(handler)
        {}
        ~DLHandler()
        {
            dlclose(m_handler);
        }

        void *GetDLHandler() const
        {
            return m_handler;
        }
        void SetDLHandler(void *handler)
        {
            m_handler = handler;
        }
    private:
        void *m_handler;
    };

    typedef std::vector<DLHandler> SOContainer;

    Factory<char, boost::shared_ptr<Actionator> >& m_factory;
    DirMonitor m_dirMonitor;
    SOContainer m_soContainer;
    const std::string m_path;
    
};

}


#endif //HADAR_KLEIN_SOLOADER_HPP
