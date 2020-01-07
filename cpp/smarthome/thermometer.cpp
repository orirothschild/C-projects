//
// Created by student on 5/1/19.
//

#include "thermometer.hpp"

namespace ilrd
{

Thermometer::Thermometer(Dispatcher<double>& dispatcher)
: m_dispatcher(dispatcher)
, m_temperature(26.5)
{}

Thermometer::~Thermometer()
{}

void Thermometer::Start()
{
    std::cout << "Thermo::Start" << std::endl;
    int flag = 1;
    while(flag)
    {
        sleep(1);
        double temperature = CheckTemp();
        if (temperature < 24) {temperature = 24;}
        if (temperature > 60) {temperature = 60;}

        if (temperature != m_temperature)
        {
            m_temperature = temperature;
            //std::cout << "Thermo::Start::Before Dispatch" << std::endl;
            m_dispatcher.Dispatch(temperature); // change the function
        }
    }
}

double Thermometer::CheckTemp()
{
    std::cout << "Thermo::CheckTemp" << std::endl;
    srand(time(NULL));
    int temp = rand() % 14;

    double currTemperature = m_temperature;

    if (temp < 5)
    {
        currTemperature -= 0.5;
    }
    else if(temp >= 10)
    {
        currTemperature += 0.5;
    }

    return currTemperature;
}


} // ilrd