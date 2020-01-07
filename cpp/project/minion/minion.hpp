#ifndef ILRD_MINION_HPP
#define ILRD_MINION_HPP

#include <boost/bind.hpp>       /* boost::bind */

#include "reactor_header.hpp"   /* reactor */
#include "receiver.hpp"         /* receiver */
#include "router.hpp"           /* router */
#include "fd.hpp"               /* fdproxy */
#include "memoryblock.hpp"      /* memory block */


#include "utils.hpp"            /* utils */


namespace ilrd
{

class Minion : private Uncopyable
{
public:
    explicit Minion(const char *port = "8080", const char *address = nullptr);
    ~Minion();

    void RegistrMinionInReactor();
    void Start();
    
private:
    MemoryBlock m_alloced_space;
    FD m_fd;
    Reactor m_reactor;
    Router m_router;
    
};





} // ilrd


#endif // ILRD_MINION_HPP