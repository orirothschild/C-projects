#include <iostream>
#include <cstdio>   /* cout */

#include "template.hpp"

template<typename T>
/* T Max(T t1, T t2)
{
    return t1 > t2 ? t1 : t2;
} */

/* template<typename T> */
void foo(T t)
{
    std::cout << t << " Generic foo\n";
}

void foo(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}


int main()
{
    foo(5);
    foo<double>(5.1);

    return 0;
}
