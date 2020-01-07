
#include <boost/bind.hpp>       /* boost bind */
#include <errno.h>              /* errno */
#include <string.h>             /* memset, strerror */
#include <netdb.h>              /* addrinfo */
#include <stdexcept>            /* exceptions */

#include "slogger_header.hpp"   /* logger */
#include "statistician.hpp"     /* statistician */


const int g_BLOCK_IDX_SIZE = 8;

namespace ilrd
{
typedef void (*CalculationFunction)(StatisticsReturnPacket& returnPacket, Statistician& statistician);
CalculationFunction CalcFuncArray[2] = {0};

Statistician::Statistician(Reactor& reactor, MemoryBlock& memBlock)
: m_reactor(reactor)
, m_memBlock(memBlock)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: Ctor" << std::endl;
    memset(&m_returnpacket, '\0', sizeof(m_returnpacket));
}

Statistician::~Statistician()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: Dtor" << std::endl;
}

void Statistician::SetAddress(struct sockaddr address, socklen_t addrLen)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: SetAddress" << std::endl;

    m_address = address;
    m_addrLen = addrLen;
}

void Statistician::PerformAction(int fd, struct sockaddr address, socklen_t addrSize, char *buffer)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: Calculate" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: FD: " << fd << std::endl;

    InitFuncTable();

    memset(&m_returnpacket, 0, sizeof(m_returnpacket));

    SetAddress(address, addrSize);

    StatisticsRequestPacket *requestPacket = reinterpret_cast<StatisticsRequestPacket *>(buffer);

    //SetReturnPacket(requestPacket);

    PerformCalculation(requestPacket->m_request);

    RegisterSendInReactor(fd, requestPacket->m_request);
}

void Statistician::PerformCalculation(char request)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: PerformCalculation" << std::endl;
    
    int req = request;

    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: PerformCalculation: after req calc: " << req << std::endl;
    
    CalcFuncArray[req](m_returnpacket, *this);
}

void Statistician::SendPacketBack(int fd) const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: SendPacketBack" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: FD: " << fd << std::endl;

    int flags = 0;

    int retval = sendto(fd, &m_returnpacket, sizeof(StatisticsReturnPacket), flags,
                        &m_address, m_addrLen);
    if (-1 == retval)
    {
        Slogger::GetInstance().Log(Logger::ERROR) << "Statistician: sendto in reader error";
        throw std::runtime_error("sendto in reader error");
    }

    m_reactor.Remove(WRITE, fd);
}

void Statistician::RegisterSendInReactor(int fd, char requestType)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: RegisterSendInReactor" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: FD: " << fd << std::endl;

    if ('0' == requestType)
    {
        std::cout << "the number of reads was: " << m_returnpacket.m_data << std::endl;
    }
    else
    {
        std::cout << "the number of writes was: " << m_returnpacket.m_data << std::endl;
    }

    m_reactor.Add(WRITE, fd, boost::bind(&Statistician::SendPacketBack, *this, _1));
}





static void CalcReads(StatisticsReturnPacket& returnPacket, Statistician& statistician)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: CalcReads" << std::endl;
    
    sprintf(returnPacket.m_data, "%d", statistician.GetReads());
}

static void CalcWrites(StatisticsReturnPacket& returnPacket, Statistician& statistician)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: CalcWrites" << std::endl;
    
    sprintf(returnPacket.m_data, "%d", statistician.GetWrites());
}

void Statistician::InitFuncTable()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: InitFucnTable" << std::endl;
    
    CalcFuncArray[0] = CalcReads;
    CalcFuncArray[1] = CalcWrites;
}

int Statistician::GetReads() const noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: GetReads" << std::endl;
    
    return m_memBlock.GetReads();
}

int Statistician::GetWrites() const noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Statistician: GetWrites" << std::endl;
    
    return m_memBlock.GetWrites();
}

boost::shared_ptr<Actionator> Statistician::Creator(std::vector<void *> &args)
{
    boost::shared_ptr<Actionator> newObject = 
    boost::shared_ptr<Statistician>(new Statistician(*(reinterpret_cast<Reactor *>(args[0])),
                                                     *(reinterpret_cast<MemoryBlock *>(args[1]))));
    
    return newObject;
}

char Statistician::GetKey()
{
    return key;
}

Statistician::CreateObjectFunction Statistician::GetCreator()
{
    return Statistician::Creator;
}


extern "C"
{
    ActionatorAPI api_table = {Statistician::GetKey, Statistician::GetCreator};
}

} // ilrd
