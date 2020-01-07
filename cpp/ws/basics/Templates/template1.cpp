#include <iostream>
#include <cstdio>   /* cout */

#include "template.hpp"
/* template <typename T>
T Max(T t1, T t2)
{
    return t1 > t2 ? t1 : t2;
} */




int main()
{
    int arr[12];

    std::cout << Max<double>(1.17, 2) << " " << Max<long>(3.7, 12.9) << " " << std::endl;
    
    std::cout << arr << (arr + 8) << std::endl;
    std::cout << Max<char *>((char *)"hi", (char *)"hello") << std::endl;
    std::cout << Max('a', 'b')  << std::endl;

    return 0;
}
