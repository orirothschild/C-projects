#ifndef ILRD_FUTURE_HPP
#define ILRD_FUTURE_HPP

#include "utils.hpp"

namespace ilrd
{

template <typename T>
class Future : public Uncopyable
{
public:
    explicit Future();
    ~Future();

    T Get();

private:
    T m_future;
};

} // ilrd


#endif // ILRD_WAITABLEQUEUE_HPP