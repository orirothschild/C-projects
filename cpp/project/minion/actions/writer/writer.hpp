#ifndef ILRD_WRITER_HPP
#define ILRD_WRITER_HPP

#include <netdb.h>              /* addrinfo */

#include "reactor_header.hpp"   /* reactor */
#include "packets.hpp"          /* returnpacket */
#include "memoryblock.hpp"      /* memoryBlock */
#include "iowriter.hpp"         /* iowriter */
#include "actionator.hpp"       /* actionator base class */

#include "utils.hpp"            /* utils */

namespace ilrd
{

class Writer : public Actionator
{
public:
    typedef boost::shared_ptr<Actionator> (*CreateObjectFunction)(std::vector<void *> &args);

    explicit Writer(Reactor& reactor, MemoryBlock& memBlock);
    ~Writer();

    void PerformAction(int fd, sockaddr address,
                       socklen_t addrSize, char *requestPacket);
    
    static boost::shared_ptr<Actionator> Creator(std::vector<void *> &args);

    static char GetKey();
    static CreateObjectFunction GetCreator();

private:
    void IOWrite(WriteRequestPacket *requestPacket, int blockIdx);
    void SendPacketBack(int fd) const;
    void RegisterSendInReactor(int fd);
    void SetAddress(struct sockaddr address, socklen_t addLen);
    void SetReturnPacket(WriteRequestPacket *requestPacket);

    Reactor& m_reactor;
    MemoryBlock& m_memBlock;
    WriteReturnPacket m_returnpacket;
    IOWriter m_iowriter;
    struct sockaddr m_address;
    socklen_t m_addrLen;
    int GetBlockIdx(char *buffer);

    const static char key = '\1';
};

} // ilrd


#endif // ILRD_WRITER_HPP