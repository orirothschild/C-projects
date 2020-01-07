
#include <boost/bind.hpp>       /* boost bind */
#include <errno.h>              /* errno */
#include <string.h>             /* memset, strerror */
#include <netdb.h>              /* addrinfo */
#include <stdexcept>            /* exceptions */
#include <sstream>

#include "slogger_header.hpp"   /* logger */
#include "reader.hpp"           /* reader */


const int g_BLOCK_IDX_SIZE = 8;

namespace ilrd
{

Reader::Reader(Reactor& reactor, MemoryBlock& memBlock)
: m_reactor(reactor)
, m_memBlock(memBlock)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Ctor" << std::endl;
}

Reader::~Reader()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Dtor" << std::endl;
}

void Reader::SetAddress(struct sockaddr address, socklen_t addrLen)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: SetAddress" << std::endl;

    m_address = address;
    m_addrLen = addrLen;
}

void Reader::SetReturnPacket(ReadRequestPacket *requestPacket)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: GetInstance" << std::endl;

    m_returnpacket.m_type = '\0';
    memcpy(m_returnpacket.m_uid, requestPacket->m_uid, 8);
    m_returnpacket.m_status = '\0';
}

void Reader::PerformAction(int fd, struct sockaddr address, socklen_t addrSize, char *buffer)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Read" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: FD: " << fd << std::endl;

    memset(&m_returnpacket, 0, sizeof(m_returnpacket));
    SetAddress(address, addrSize);
    ReadRequestPacket *requestPacket = reinterpret_cast<ReadRequestPacket *>(buffer);

    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Read: uid" << requestPacket->m_uid << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Read: m_uid" << m_returnpacket.m_uid << std::endl;

    int blockIdx = GetBlockIdx(requestPacket->m_blockIdx);
    IORead(blockIdx);

    SetReturnPacket(requestPacket);
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Read: uid " << requestPacket->m_uid << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Read: m_uid " << m_returnpacket.m_uid << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Read: type " << m_returnpacket.m_type << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: Read: status " << m_returnpacket.m_status << std::endl;

    RegisterSendInReactor(fd);
}

int Reader::GetBlockIdx(char *buffer)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: GetBlockIdx" << std::endl;

    std::stringstream strstream(buffer);
    int blockIdx = 0;

    strstream >> blockIdx;
    return blockIdx;
}

void Reader::IORead(int blockIdx)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: IORead" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: blockIdx: " << blockIdx << std::endl;

    m_ioreader.Read(&m_returnpacket, blockIdx, m_memBlock.GetMemoryBlock());
    
    m_memBlock.IncrementReads();
}

void Reader::SendPacketBack(int fd) const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: SendPacketBack" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: FD: " << fd << std::endl;

    std::cout << "SendBack: this address: " << this << std::endl;

    int flags = 0;

    Slogger::GetInstance().Log(Logger::ERROR) << "Reader: returnpacket.m_packetsize: " << atoi(m_returnpacket.m_packetSize) << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: SendPacketBack: m_uid " << m_returnpacket.m_uid << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: SendPacketBack: type " << m_returnpacket.m_type << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: SendPacketBack: status " << m_returnpacket.m_status << std::endl;
    int retval = sendto(fd, &m_returnpacket, atoi(m_returnpacket.m_packetSize), flags,
                        &m_address, m_addrLen);
    if (-1 == retval)
    {
        Slogger::GetInstance().Log(Logger::ERROR) << "Reader: sendto in reader error";
        throw std::runtime_error("sendto in reader error");
    }

    m_reactor.Remove(WRITE, fd);
}

void Reader::RegisterSendInReactor(int fd)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: RegisterSendInReactor" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: FD: " << fd << std::endl;

    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: RegisterSendInReactor: m_uid " << m_returnpacket.m_uid << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: RegisterSendInReactor: type " << m_returnpacket.m_type << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "Reader: RegisterSendInReactor: status " << m_returnpacket.m_status << std::endl;
    std::cout << "Register: this address: " << this << std::endl;

    m_reactor.Add(WRITE, fd, boost::bind(&Reader::SendPacketBack, *this, _1));
}

boost::shared_ptr<Actionator> Reader::Creator(std::vector<void *> &args)
{
    boost::shared_ptr<Actionator> newObject = 
    boost::shared_ptr<Reader>(new Reader(*(reinterpret_cast<Reactor *>(args[0])),
                                         *(reinterpret_cast<MemoryBlock *>(args[1]))));
    
    return newObject;
}

char Reader::GetKey()
{
    return key;
}

Reader::CreateObjectFunction Reader::GetCreator()
{
    return Reader::Creator;
}

extern "C"
{
    ActionatorAPI api_table = {Reader::GetKey, Reader::GetCreator};
}

} // ilrd