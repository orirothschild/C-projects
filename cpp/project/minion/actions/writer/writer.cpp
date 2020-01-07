
#include <boost/bind.hpp>       /* boost bind */
#include <errno.h>              /* errno */
#include <string.h>             /* memset, strerror */
#include <netdb.h>              /* addrinfo */
#include <stdexcept>            /* exceptions */
#include <sstream>

#include "slogger_header.hpp"
#include "writer.hpp"

const int g_BLOCK_IDX_SIZE = 8;

#define SEVERITY (Logger::ERROR)

namespace ilrd
{
Writer::Writer(Reactor& reactor, MemoryBlock& memBlock)
: m_reactor(reactor)
, m_memBlock(memBlock)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: Ctor " << std::endl;

    memset(&m_returnpacket, 0, sizeof(m_returnpacket));
}

Writer::~Writer()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: Dtor " << std::endl;
}

void Writer::SetAddress(struct sockaddr address, socklen_t addrLen)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: SetAddress " << std::endl;

    m_address = address;
    m_addrLen = addrLen;
}

void Writer::SetReturnPacket(WriteRequestPacket *requestPacket)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: SetReturnPacket " << std::endl;

    m_returnpacket.m_type = '\1';
    memcpy(m_returnpacket.m_uid, requestPacket->m_uid, 8);
    //m_returnpacket.m_status = SUCCESS;
}

void Writer::PerformAction(int fd, struct sockaddr address, socklen_t addrSize, char *buffer)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: Write " << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: FD: " << fd << std::endl;
    SetAddress(address, addrSize);

    WriteRequestPacket *requestPacket = reinterpret_cast<WriteRequestPacket *>(buffer);

    SetReturnPacket(requestPacket);

    int blockIdx = GetBlockIdx(requestPacket->m_blockIdx);

    IOWrite(requestPacket, blockIdx);

    RegisterSendInReactor(fd);
}

int Writer::GetBlockIdx(char *buffer)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: GetBlockIdx" << std::endl;

    std::stringstream strstream(buffer);
    int blockIdx = 0;

    strstream >> blockIdx;
    return blockIdx;
}

void Writer::IOWrite(WriteRequestPacket *requestPacket, int blockIdx)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: IOWrite" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: blockIdx: " << blockIdx << std::endl;
    
    m_returnpacket.m_status = m_iowriter.Write(requestPacket, blockIdx, m_memBlock.GetMemoryBlock());
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: status: " << m_returnpacket.m_status+48 << std::endl;
    if (SUCCESS == m_returnpacket.m_status)
    {
        m_memBlock.IncrementWrites();
    }
}

void Writer::SendPacketBack(int fd) const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: SendPacketBack" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: FD: " << fd << std::endl;

    int flags = 0;

    int retval = sendto(fd, &m_returnpacket, sizeof(WriteReturnPacket), flags,
                        &m_address, m_addrLen);
    if (-1 == retval)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: sendto in writer error" << std::endl;
        throw std::runtime_error("sendto in writer error");
    }

    m_reactor.Remove(WRITE, fd);
}

void Writer::RegisterSendInReactor(int fd)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: RegisterSendInReactor" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: FD: " << fd << std::endl;

    Slogger::GetInstance().Log(Logger::DEBUG) << "Writer: RegisterSendInReactor: \t " << &Writer::SendPacketBack << std::endl;
    m_reactor.Add(WRITE, fd, boost::bind(&Writer::SendPacketBack, *this, _1));
}


boost::shared_ptr<Actionator> Writer::Creator(std::vector<void *> &args)
{
    boost::shared_ptr<Actionator> newObject = 
    boost::shared_ptr<Writer>(new Writer(*(reinterpret_cast<Reactor *>(args[0])),
                                         *(reinterpret_cast<MemoryBlock *>(args[1]))));
    
    return newObject;
}


char Writer::GetKey()
{
    return key;
}

Writer::CreateObjectFunction Writer::GetCreator()
{
    return Writer::Creator;
}

extern "C"
{
    ActionatorAPI api_table = {Writer::GetKey, Writer::GetCreator};
}

} // ilrd
