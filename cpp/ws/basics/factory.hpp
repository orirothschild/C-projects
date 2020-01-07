#ifndef ILRD_FACTORY_HPP
#define ILRD_FACTORY_HPP

#include <vector>               /* vector */
#include <map>                  /* map */
#include <boost/shared_ptr.hpp> /* shared ptr */
#include "slogger_header.hpp"   /* slogger */

namespace ilrd
{

template <class Key, class Type>
class Factory
{
public:
    typedef Type (*CreateObjectFunction)(std::vector<void *> &args);
    typedef std::map<Key, CreateObjectFunction> FactoryContainer;
    
    void Register(const Key& keyname, CreateObjectFunction pCreateFunc);
    Type CreateObject(const Key& keyname, std::vector<void *> &args);


private:
    FactoryContainer m_FactContainer;
};

template <class Key, class Type>
void Factory<Key, Type>::Register(const Key& keyname, CreateObjectFunction pCreateFunc)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: Register" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "keyname is: " << keyname << std::endl;

    m_FactContainer[keyname] = pCreateFunc;
}

template <class Key, class Type>
Type Factory<Key, Type>::CreateObject(const Key& keyname, std::vector<void *> &args)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "keyname is: " << keyname << std::endl;

    typename FactoryContainer::iterator iter = m_FactContainer.find(keyname);
    
    Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject" << std::endl;
    if (m_FactContainer.end() != iter)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject1" << std::endl;
        
        return iter->second(args);
        Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject1" << std::endl;
    }
    Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject" << std::endl;
    
    throw "GenericFactory::CreateObject: key was not found. Was it registered?";
    Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject" << std::endl;
}

/* namespace ilrd
{

template <class Key, class Type>
class Factory
{
    typedef Type (*CreateObjectFunction)(std::vector<void *> &args);
    typedef std::map<Key, CreateObjectFunction> FactoryMap;

public:
    void Register(const Key& keyname, CreateObjectFunction pCreateFunc)
    {
        //m_FactMap.insert(keyname, pCreateFunc);
        Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: Register" << std::endl;
        Slogger::GetInstance().Log(Logger::DEBUG) << "keyname is: " << keyname << std::endl;
        m_FactMap[keyname] = pCreateFunc;
    }

    Type CreateObject(const Key& keyname, std::vector<void *> &args)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject" << std::endl;
        Slogger::GetInstance().Log(Logger::DEBUG) << "keyname is: " << keyname << std::endl;
        typename FactoryMap::iterator iter = m_FactMap.find(keyname);
        Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject" << std::endl;
        if (m_FactMap.end() != iter)
        {
            Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject1" << std::endl;
            return iter->second(args);
            Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject1" << std::endl;
        }
        Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject" << std::endl;
        throw "GenericFactory::CreateObject: key was not found. Was it registered?";
        Slogger::GetInstance().Log(Logger::DEBUG) << "Factory: CreateObject" << std::endl;
    }

private:
    FactoryMap m_FactMap;
}; */


} // ilrd



#endif // ILRD_FACTORY_HPP