#ifndef ILRD_SMOKEDETECTOR_HPP
#define ILRD_SMOKEDETECTOR_HPP


#include "dispatcher.hpp"

namespace ilrd {

class SmokeDetector
{
public:
    explicit SmokeDetector(Dispatcher<bool>& dispatcher);
    ~SmokeDetector();

    void Start();

private:
    bool CheckSmoke();

    Dispatcher<bool>& m_dispatcher;
    bool m_isSmoke;
};

} // ilrd

#endif //ILRD_SMOKEDETECTOR_HPP
