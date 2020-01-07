

#include "logger.hpp" /* API */



namespace ilrd
{
DevNull g_null;

Logger::Logger(std::ostream& os, Severity sev)
: m_os(&os)
, m_active_os(&os)
, m_sev(sev)
{}

Logger::LoggerWriter::LoggerWriter(std::ostream& os)
: m_os(os)
{}

void Logger::SetOstream(std::ostream& os)
{
    m_os = &os;
}

void Logger::SetSeverity(Logger::Severity sev)
{
    m_sev = sev;
}

Logger::LoggerWriter Logger::Log(Logger::Severity sev)
{
    m_active_os = m_os;

    if (m_sev > sev)
    {
        m_active_os = &g_null.GetNull();
    }
    
    return LoggerWriter(*m_active_os);
}

Logger::LoggerWriter Logger::LoggerWriter::operator<<(end_func endline)
{
    m_os << endline;
    
    return *this;
}

} //end namespace