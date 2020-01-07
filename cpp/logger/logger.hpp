#ifndef ILRD_LOGGER_HPP
#define ILRD_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <cstddef>
#include "utils.hpp"

namespace ilrd
{

typedef std::ostream& (*end_func)(std::ostream& os);

class DevNull
{
public:
    DevNull()
    : m_null() 
    {
        m_null.open("/dev/null");
        if (std::ios_base::failbit == m_null.rdstate())
        {
            throw std::logic_error("open error");
        }
    }
    ~DevNull() {m_null.close();}

    std::ofstream& GetNull() {return m_null;}
private:
    std::ofstream m_null;
};


class Logger
{
private:
    class LoggerWriter;
    class DevNull;

public:
    enum Severity
    {
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR
    };

    /* non-explicit*/ Logger(std::ostream& os, Severity sev);

    LoggerWriter Log(Severity sev);

    void SetOstream(std::ostream& os);
    void SetSeverity(Severity sev);

private:
    std::ostream* m_os;
    std::ostream* m_active_os;
    Severity m_sev;
    
    class LoggerWriter
    {
    public:
        LoggerWriter(std::ostream& os);

        
        
        template<typename T>
        LoggerWriter operator<<(const T& msg);
        LoggerWriter operator<<(end_func endline);
    private:
        std::ostream& m_os;
    };
};

template<typename T>
Logger::LoggerWriter Logger::LoggerWriter::operator<<(const T& msg)
{
    m_os << msg;
 
    return *this;
}

} //end of ilrd namespace

#endif //end of LOGGER_HPP
