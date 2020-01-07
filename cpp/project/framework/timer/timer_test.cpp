#include <boost/bind.hpp>   /* bind */
#include <iostream>         /* cout */

#include "timer.hpp"        /* API */
#include "utils.hpp"        /* utils */


using namespace ilrd;

long SecToNano(long seconds);

void PrintHello(int i)
{
    UNUSED(i);
    std::cout << "Hello world" << std::endl;
}

int main()
{
    Reactor r;
    Timer tm(r);

    Timer::nanoSecs two = Timer::nanoSecs(SecToNano(2));
    Timer::nanoSecs ten = Timer::nanoSecs(SecToNano(10));
    Timer::nanoSecs five = Timer::nanoSecs(SecToNano(5));

    tm.Add(two, PrintHello);
    tm.Add(ten, PrintHello);
    tm.Add(five, PrintHello);
    r.Start();

    return 0;
}

long SecToNano(long seconds)
{
    return seconds * 1000000000;
}
