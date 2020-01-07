//
// Created by student on 4/29/19.
//

#include <dlfcn.h>
#include <boost/bind.hpp>   /* boost bind */
#include <boost/filesystem.hpp>

#include "soloader.hpp"


namespace ilrd
{


SoLoader::SoLoader(Factory<char, boost::shared_ptr<Actionator> >& factory, Reactor& reactor, const std::string& path)
: m_factory(factory)
, m_dirMonitor(reactor, path, boost::bind(&SoLoader::Connect, this, _1))
, m_path(path)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Ctor " << std::endl;
    LoadSoAtStartUp();
}

SoLoader::~SoLoader()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Dtor " << std::endl;
}

void SoLoader::Connect(const std::string& str)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect " << std::endl;


    std::cout << m_path << std::endl;
    std::cout << str << std::endl;
    std::string fullPath = m_path + str;
    //std::string fullPath = "./statistician.so";
    std::cout << fullPath << std::endl;
    std::cout << fullPath.c_str() << std::endl;

    
    DLHandler handler(dlopen(fullPath.c_str(), RTLD_LAZY));
    //std::cout << dlerror() << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect: Debug1" << std::endl;
    while (nullptr == handler.GetDLHandler())
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect: Debug2" << std::endl;
        handler.SetDLHandler(dlopen(fullPath.c_str(), RTLD_LAZY));
    }
    
    /* if (nullptr == handler.GetDLHandler())
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect: Debug2" << std::endl;
        //throw some exception
    } */
    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect: Debug3" << std::endl;
    ActionatorAPI *api_table = reinterpret_cast<ActionatorAPI *>(dlsym(handler.GetDLHandler(), "api_table"));

    if (api_table == nullptr)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect: Debug9" << std::endl;    
    }
    api_table->GetKey();

    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect: Debug4" << std::endl;
    m_factory.Register(api_table->GetKey(), api_table->GetCreator());


    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect: Debug5" << std::endl;
    m_soContainer.push_back(handler);


    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: Connect: Debug6" << std::endl;
}

void SoLoader::LoadSoAtStartUp()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "SoLoader: LoadSoAtStartup " << std::endl;

    boost::filesystem::path path(m_path);
    boost::filesystem::directory_iterator i;

    for (i = boost::filesystem::directory_iterator(path); i != boost::filesystem::directory_iterator(); i++)
    {
        if (!boost::filesystem::is_directory(i->path())) //we eliminate directories
        {
            Connect(i->path().filename().string().c_str());
        }
        else
            continue;
    }
}

} // ilrd
