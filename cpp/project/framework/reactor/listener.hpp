#ifndef ILRD_LISTENER_HPP
#define ILRD_LISTENER_HPP

#include <vector>               /* vector */

#include "slogger_header.hpp"    /* logger */
#include "utils.hpp"            /* utils */

namespace ilrd
{

enum Mode
{
    FIRST_MODE = 0,
    READ = FIRST_MODE,
    WRITE,
    EXCEPTION,
    NUM_OF_MODES
};


class Listener : private Uncopyable
{
public:
    enum Flag
    {
        FLAG_STOP = 0,
        FLAG_START
    };

    typedef std::vector<std::pair<Mode, int> > listenervector;
  
    explicit Listener() noexcept;
    ~Listener() noexcept;

    listenervector Wait(const listenervector& vec) const;

private:
    int VecToSets(fd_set *setArray, const listenervector& vec) const noexcept;
    listenervector SetsToVec(fd_set *setArray, int max) const;
};




} //end ilrd

#endif //ILRD_LISTENER_HPP