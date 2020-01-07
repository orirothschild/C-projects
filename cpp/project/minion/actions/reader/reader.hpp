#ifndef ILRD_READER_HPP
#define ILRD_READER_HPP

#include <netdb.h>              /* addrinfo */
#include <boost/shared_ptr.hpp>

#include "reactor_header.hpp"   /* reactor */
#include "packets.hpp"          /* returnpacket */
#include "memoryblock.hpp"      /* memoryblock */
#include "ioreader.hpp"         /* ioreader */
#include "actionator.hpp"       /* actionator base class */

#include "utils.hpp"            /* utils */

namespace ilrd
{

class Reader : public Actionator
{
public:
    typedef boost::shared_ptr<Actionator> (*CreateObjectFunction)(std::vector<void *> &args);

    explicit Reader(Reactor& reactor, MemoryBlock& memBlock);
    ~Reader();

    void PerformAction(int fd, sockaddr address,
                       socklen_t addrSize, char *requestPacket);

    static boost::shared_ptr<Actionator> Creator(std::vector<void *> &args);

    static char GetKey();
    static CreateObjectFunction GetCreator();

private:
    void IORead(int blockIdx);
    void SendPacketBack(int fd) const;
    void RegisterSendInReactor(int fd);
    void SetAddress(struct sockaddr address, socklen_t addrLen);
    void SetReturnPacket(ReadRequestPacket *requestPacket);

    Reactor& m_reactor;
    MemoryBlock& m_memBlock;
    ReadReturnPacket m_returnpacket;
    IOReader m_ioreader;
    struct sockaddr m_address;
    socklen_t m_addrLen;
    int GetBlockIdx(char *buffer);

    const static char key = '\0';
};

} // ilrd


#endif // ILRD_READER_HPP