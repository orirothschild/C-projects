#ifndef ILRD_FAN_HPP
#define ILRD_FAN_HPP

#include <string>

namespace ilrd
{

class Fan
{
public:
    explicit Fan(std::string id);
    ~Fan();

    void DispatcherTemperatureFunction(double temperature);
    void DispatcherSmokeFunction(bool isSmokey);

private:
    void TurnOn();
    void TurnOff();

    std::string m_id;
};

} // ilrd

#endif //ILRD_FAN_HPP
