#ifndef ILRD_THREAD_HPP
#define ILRD_THREAD_HPP

#include <pthread.h>
#include "boost/function.hpp"
#include "threadexceptions.hpp"

#include "utils.hpp"

namespace ilrd
{
typedef boost::function<void ()> ThreadFunc;


class Thread : private Uncopyable
{
public:
    explicit Thread(ThreadFunc function);
    ~Thread();
    
    void Join();
    //void Exit();
    bool GetActiveState() const;

private:
    ThreadFunc m_func;
    bool m_isActive;
    bool m_isJoinable;
    pthread_t m_id;
    
    pthread_t CreateThread();
    static void *ThreadFuncWrapper(void *args);

    //void Detach();
    
};

} // ilrd
#endif // ILRD_THREAD_HPP
