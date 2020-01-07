#ifndef ILRD_STATISTICIAN_HPP
#define ILRD_STATISTICIAN_HPP

#include <netdb.h>              /* addrinfo */

#include "reactor_header.hpp"   /* reactor */
#include "packets.hpp"          /* returnpacket */
#include "memoryblock.hpp"      /* memoryBlock */
#include "actionator.hpp"       /* actionator base class */

#include "utils.hpp"            /* utils */

namespace ilrd
{

class Statistician : public Actionator
{
public:
    typedef boost::shared_ptr<Actionator> (*CreateObjectFunction)(std::vector<void *> &args);

    explicit Statistician(Reactor& reactor, MemoryBlock& memBlock);
    ~Statistician();

    void PerformAction(int fd, sockaddr address,
                       socklen_t addrSize,char *buffer);

    static boost::shared_ptr<Actionator> Creator(std::vector<void *> &args);
    
    void PerformCalculation(char request);

    int GetReads() const noexcept;
    int GetWrites() const noexcept;
    void IncrementReads();
    void IncrementWrites();

    static char GetKey();
    static CreateObjectFunction GetCreator();

private:
    void SendPacketBack(int fd) const;
    void RegisterSendInReactor(int fd, char requestType);
    void SetAddress(struct sockaddr address, socklen_t addrLen);
    void SetReturnPacket(StatisticsRequestPacket *requestPacket);
    void InitFuncTable();

    Reactor& m_reactor;
    MemoryBlock& m_memBlock;
    StatisticsReturnPacket m_returnpacket;
    struct sockaddr m_address;
    socklen_t m_addrLen;

    const static char key = 'S';
};

} // ilrd

#endif // ILRD_STATISTICIAN_HPP