#ifndef ILRD_ROUTER_HPP
#define ILRD_ROUTER_HPP

#include <boost/bind.hpp>       /* boost::bind */
#include "reactor_header.hpp"   /* reactor */
#include "receiver.hpp"         /* receiver */
#include "fd.hpp"               /* fdproxy */
#include "memoryblock.hpp"      /* memoryBlock */
#include "actionator_header.hpp"/* actionator */
#include "factory_header.hpp"   /* factory */
#include "soloader.hpp"         /* soloader */
#include "utils.hpp"            /* utils */

#define g_MAX_BUFFER_SIZE (4113)

namespace ilrd
{

class Router
{
public:
    explicit Router(Reactor &reactor, MemoryBlock& memBlock);
    ~Router();

    void Do(int fd);

private:
    Reactor& m_reactor;
    MemoryBlock& m_memBlock;
    Receiver m_receiver;
    char m_read_buffer[g_MAX_BUFFER_SIZE];
    struct sockaddr m_address;
    socklen_t m_addrLen;
    Factory<char, boost::shared_ptr<Actionator> > m_factory;
    SoLoader m_soloader;
};

} // ilrd


#endif // ILRD_ROUTER_HPP