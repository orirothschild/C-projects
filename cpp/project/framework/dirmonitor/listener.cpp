#include <cerrno>                   /* errno */
#include <stdexcept>                /* invalid_argument */
#include <cstring>                  /* strerror */
#include <errno.h>                  /* errno */
#include <sys/select.h>             /* select */
#include <algorithm>                /* for_each */
#include <cassert>                  /* assert */

#include "listener.hpp"             /* API */
#include "reactor_exceptions.hpp"   /* API */

namespace ilrd
{

Listener::Listener() noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: Ctor" << std::endl;
}

Listener::~Listener() noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: Dtor" << std::endl;
}

Listener::listenervector Listener::Wait(const listenervector& vec) const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: Wait" << std::endl;

    fd_set setArray[NUM_OF_MODES] = {0};
    int max = VecToSets(setArray, vec);


    int flag = FLAG_START;
    while (flag)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: Wait: Max: " << max << std::endl;
        int retval = select(max, &setArray[ilrd::READ], &setArray[ilrd::WRITE],
                        &setArray[ilrd::EXCEPTION], NULL);
        if (ERROR == retval)
        {
            switch (errno)
            {
                case (ENOMEM):
                    Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: Select: Bad Alloc" << std::endl;
                    throw std::bad_alloc();
                    break;
                case (EBADF) :
                    Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: Select: Bad FD" << std::endl;
                    throw reactor::ListenerExceptionBadFD(strerror(errno));
                    break;
                case (EINTR) :
                    continue;
                default :
                    assert(!"impossible error from select");
                    Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: Select: Impossible error" << std::endl;
            }
        }

        flag = FLAG_STOP;
    }
    
    return SetsToVec(setArray, max);
}

class FDSetZero
{
public:
    void operator()(fd_set set)
    {
        FD_ZERO(&set);
    }
};

int Listener::VecToSets(fd_set *setArray, const listenervector& vec) const noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: VecToSets" << std::endl;

    std::for_each(&setArray[0], &setArray[NUM_OF_MODES], FDSetZero());

    listenervector::const_iterator it;
    int max = 0;
    for (it = vec.begin(); it != vec.end(); ++it)
    {
        FD_SET(it->second, &setArray[it->first]);
        max = MAX(max, it->second);
    }

    return max + 1;
}

Listener::listenervector Listener::SetsToVec(fd_set *setArray, int end) const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "Listener: SetsToVec" << std::endl;
    
    listenervector vec;

    for (int i = 0; i < end; ++i)
    {
        for (int j = 0; j < NUM_OF_MODES; ++j)
        {
            if (FD_ISSET(i, &setArray[j]))
            {
                vec.push_back(std::pair<Mode, int>(Mode(j), i));
            }
        }
    }

    return vec;
}

} //end ilrd
