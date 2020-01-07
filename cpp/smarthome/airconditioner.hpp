#ifndef ILRD_AIRCONDITIONER_HPP
#define ILRD_AIRCONDITIONER_HPP

#include <string>

namespace ilrd
{

class AirConditioner
{
public:
    explicit AirConditioner() = default;
    ~AirConditioner() = default;

    void DispatcherTemperatureFunction(double temperature);
    void DispatcherSmokeFunction(bool isSmokey);

private:
    void TurnOn();
    void TurnOff();
};

} // ilrd

#endif //ILRD_AIRCONDITIONER_HPP
