
#include <iostream>

#include "thread.hpp"
#include "boost/bind.hpp"

using namespace ilrd;


void PrintBlerg(int *args)
{
    std::cout << *args << std::endl;

    //return nullptr;
}

unsigned long Fibo(int num)
{
    if (1 >= num)
    {
        return num;
    }

    return (Fibo(num - 1) + Fibo(num - 2));
}

void *Wrapper(void *args)
{
    int *num = reinterpret_cast<int *>(args);

    unsigned long *retval = new unsigned long(Fibo(*num));

    return retval;
}




int main()
{
    int i = 5;
    boost::function<void ()> function = boost::bind(PrintBlerg, &i);

    Thread thr(function);

    thr.Join();


    /* int param = 10;
    Thread tblerg(Wrapper, &param);

    unsigned long *retval = reinterpret_cast<unsigned long *>(tblerg.Join());

    std::cout << "Fibo number of " << param << " is: " << *retval << std::endl;

    delete retval; */

    return 0;
}
