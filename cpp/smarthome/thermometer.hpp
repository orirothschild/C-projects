#ifndef ILRD_THERMOMETER_HPP
#define ILRD_THERMOMETER_HPP

#include "dispatcher.hpp"

namespace ilrd {

class Thermometer
{
public:
    explicit Thermometer(Dispatcher<double>& dispatcher);
    ~Thermometer();

    void Start();

private:
    double CheckTemp();

    Dispatcher<double>& m_dispatcher;
    double m_temperature;

};

} // ilrd

#endif //ILRD_THERMOMETER_HPP
