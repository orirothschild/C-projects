//
// Created by student on 5/1/19.
//

#include <iostream>
#include "airconditioner.hpp"


namespace ilrd
{

void AirConditioner::DispatcherTemperatureFunction(double temperature)
{
    std::cout << "AirConditioner::DispatcherTemperatureFunction: temperature: " << temperature << std::endl;

    if (temperature < 25)
    {
        TurnOff();
    }
    else if (temperature > 28)
    {
        TurnOn();
    }
}

void AirConditioner::DispatcherSmokeFunction(bool isSmokey)
{
    if (isSmokey)
    {
        TurnOff();
    }
}

void AirConditioner::TurnOn()
{
    std::cout << "AirConditioner::Turned On" << std::endl;
}

void AirConditioner::TurnOff()
{
    std::cout << "AirConditioner::Turned Off" << std::endl;
}




} // ilrd
