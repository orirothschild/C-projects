#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "point.hpp"

#define NUM_OF_POINTS (3)

void PrintPointArr(struct Point point)
{
    std::cout << "x is " << point.x << " y is " << point.y << std::endl;
}


int main()
{
    int dx = 1;
    int dy = 1;
    int upper_bound = 0;
    
    InitTable();
    
    std::cout << "enter an upper bound please" << std::endl;
    std::cin >> upper_bound;

    Point p = {1, 1};
    Point q = {2, 2};
    Point r = {-1, -1};
    
    std::cout << "the input is " << upper_bound << std::endl;

    PrintPointArr(p);
    PrintPointArr(q);
    PrintPointArr(r);

    p.AdjustBy(q, upper_bound).AdjustBy(dx,dy, upper_bound).AdjustBy(r, upper_bound);

    PrintPointArr(p);
    PrintPointArr(q);
    PrintPointArr(r);

    return 0;
}