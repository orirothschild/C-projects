#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "point.hpp"

#define NUM_OF_POINTS (3)

void PrintPointArr(struct Point point)
{
    printf("x is %d, y is %d\n", point.x, point.y);
}


int main()
{
    int i = 0;
    int j = 0;
    int dx = 1;
    int dy = 1;
    int upper_bound = 0;
    
    InitTable();
    
    printf("enter an upper bound please\n");
    std::cin >> upper_bound;
    Point p = {1, 1};
    Point q = {2, 2};
    Point r = {-1, -1};
    struct Point point_arr[NUM_OF_POINTS] = {0,0};

    printf("the input is %d\n", upper_bound);


    for (i = 0; i < NUM_OF_POINTS; ++i)
    {
        point_arr[i].x = i;
        point_arr[i].y = i;
    }

    PrintPointArr(point_arr[0]);
    PrintPointArr(point_arr[1]);
    PrintPointArr(point_arr[2]);
    
    for (i = 0; i < NUM_OF_POINTS; ++i)
    {
        for (j = 0; j < NUM_OF_POINTS; ++j)
        {   
            printf("i is %d\n", i);
            point_arr[i].Print('{', '}');
            printf("the length is %f\n", point_arr[i].Length());
            point_arr[i].AdjustBy(p, upper_bound);
            PrintPointArr(point_arr[i]);
            r = Add(p, q, upper_bound);
            PrintPointArr(r);
            point_arr[i].AdjustBy(dx, dy, upper_bound);
            PrintPointArr(point_arr[i]);
            point_arr[i].Print(point_arr[i].ROUND);
            point_arr[i].Print(point_arr[i].SQUARE);
            point_arr[i].Print(point_arr[i].CURLY);
            point_arr[i].Print(point_arr[i].ANGULAR);
        }
    }

    return 0;
}