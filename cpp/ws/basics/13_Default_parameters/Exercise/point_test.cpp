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
    int i = 0;
    int j = 0;
    int dx = 1;
    int dy = 1;
    int upper_bound = 0;
    
    InitTable();
    
    std::cout << "enter an upper bound please" << std::endl;
    std::cin >> upper_bound;

    Point p = {1, 1, -1};
    p.CalculateLength();
    Point& pr = p;

    Point q = {2, 2, -1};
    Point r = {-1, -1, -1};
    Point p2 = {1, 2, -1};
    q.CalculateLength();
    r.CalculateLength();
    p2.CalculateLength();
    

    std::cout << p.IsEqual(p2) << std::endl;

    Point point_arr[NUM_OF_POINTS] = {0, 0, -1};

    std::cout << "the input is " << upper_bound << std::endl;


    for (i = 0; i < NUM_OF_POINTS; ++i)
    {
        point_arr[i].x = i;
        point_arr[i].y = i;
    }

    PrintPointArr(p);
    PrintPointArr(q);
    PrintPointArr(r);

    p.AdjustBy(q, upper_bound).AdjustBy(dx,dy, upper_bound).AdjustBy(r, upper_bound);

    PrintPointArr(p);
    PrintPointArr(q);
    PrintPointArr(r);

    for (i = 0; i < NUM_OF_POINTS; ++i)
    {
        for (j = 0; j < NUM_OF_POINTS; ++j)
        {   
            std::cout << "i is " << i << std::endl;
            point_arr[i].Print('{', '}');
            std::cout << "the length is " << point_arr[i].Length() << std::endl;
            point_arr[i].AdjustBy(pr, upper_bound);
            PrintPointArr(point_arr[i]);
            r = Add(p, q, upper_bound);
            PrintPointArr(r);
            point_arr[i].AdjustBy(dx, dy, upper_bound);
            PrintPointArr(point_arr[i]);
            point_arr[i].Print(point_arr[i].ROUND);
            point_arr[i].Print();
            point_arr[i].Print(point_arr[i].CURLY);
            point_arr[i].Print(point_arr[i].ANGULAR);
        }
    }

    return 0;
}