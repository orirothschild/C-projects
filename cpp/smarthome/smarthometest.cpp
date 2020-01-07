#include <iostream>
#include <thread>
#include "dispatcher.hpp"
#include "thermometer.hpp"
#include "smokedetector.hpp"
#include "airconditioner.hpp"
#include "sprinkler.hpp"
#include "boost/bind.hpp"


using namespace ilrd;

void DoubleTestFunc(double d)
{
    std::cout << "double d: " << d << std::endl;
}

void BoolTestFunc(bool b)
{
    std::cout << "bool b: " << b << std::endl;
}

void RunThermo(Thermometer thermo)
{
    //std::cout << "debug 14" << std::endl;
    thermo.Start();
}

void RunSmokey(SmokeDetector smokey)
{
    //std::cout << "debug 15" << std::endl;
    smokey.Start();
}

int main()
{
    AirConditioner ac;
    Sprinkler sp;
    //std::cout << "debug 1" << std::endl;
    Dispatcher<double> double_dispatcher;

    //std::cout << "debug 2" << std::endl;
    Dispatcher<bool> bool_dispatcher;

    //std::cout << "debug 3" << std::endl;
    Dispatcher<double>::SharedPtr temperaturePtr = double_dispatcher.Register(boost::bind(&AirConditioner::DispatcherTemperatureFunction, ac, _1));
    double_dispatcher.Unregister(temperaturePtr);
    //std::cout << "debug 4" << std::endl;
    Dispatcher<bool>::SharedPtr smokePair = bool_dispatcher.Register(boost::bind(&Sprinkler::DispatcherSmokeFunction, sp, _1));

    //std::cout << "debug 5" << std::endl;
    Thermometer thermo(double_dispatcher);

    //std::cout << "debug 6" << std::endl;
    SmokeDetector smokey(bool_dispatcher);

    //std::cout << "debug 7" << std::endl;
    //std::cout << "debug 8" << std::endl;
    std::thread thermothread(RunThermo, thermo);

    //std::cout << "debug 9" << std::endl;
    std::thread smokeythread(RunSmokey, smokey);

    //std::cout << "debug 10" << std::endl;
    //std::cout << "debug 11" << std::endl;
    thermothread.join();

    //std::cout << "debug 12" << std::endl;
    smokeythread.join();

    //std::cout << "debug 13" << std::endl;

    return 0;
}