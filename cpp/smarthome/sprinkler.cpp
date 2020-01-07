//
// Created by student on 5/1/19.
//
#include <string>
#include <iostream>
#include "sprinkler.hpp"

namespace ilrd
{

void Sprinkler::DispatcherSmokeFunction(bool isSmokey)
{
    if (isSmokey)
    {
        TurnOn();
    }
}

//void Sprinkler::TurnOff()
//{
//    std::cout << "Turn Off" << std::endl;
//}

void Sprinkler::TurnOn()
{
    std::cout << "Sprinkler::Turn On" << std::endl;
}






}