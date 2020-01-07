//
// Created by student on 5/1/19.
//

#include <string>

#include "fan.hpp"

namespace ilrd
{

Fan::Fan(std::string id)
: m_id(id)
{}

//Fan::~Fan()
//{}

void Fan::DispatcherTemperatureFunction(double temperature)
{
    if (temperature < 25)
    {
        TurnOff();
    }
    else if (temperature > 28)
    {
        TurnOn();
    }
}

void Fan::DispatcherSmokeFunction(bool isSmokey)
{
    if (isSmokey)
    {
        TurnOff();
    }
}

void Fan::TurnOn()
{
    std::cout << "Turned On" << std::endl;

}

void Fan::TurnOff()
{
    std::cout << "Turned Off" << std::endl;

}

} // ilrd