#include <iostream>

void Foo(const double& d)
{
    std::cout << "d in Foo is " << d << std::endl;
    std::cout << d << " " << &d << std::endl;
}

void Bar(double& d)
{
    std::cout << "d in Bar is " << d << std::endl;
    std::cout << d << " " << &d << std::endl;
}


int main()
{
    int d = 5;
    double *dp = reinterpret_cast<double*>(&d);

    //std::cout << dp << " " << *dp << std::endl;

    Foo(d);
    Bar(*(reinterpret_cast<double *>(&d)));

    return 0;
}