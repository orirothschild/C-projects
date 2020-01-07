#include <iostream>
#include <cstdio>
#include <cmath>


#include "point.hpp"


void Point::AdjustBy(Point p, int upper_bound)
{
    x = (x + p.x) % upper_bound;
    y = (y + p.y) % upper_bound;
}

double Point::Length()
{
    return sqrt((x * x) + (y * y));
}

void Point::Print(char open, char close)
{
    printf("%c%d, %d%c\n",open, x, y, close);
}

struct Point Add(Point p1, Point p2, int upper_bound)
{
    Point ret_point;
    ret_point.x = (p1.x + p2.x) % upper_bound;
    ret_point.y = (p1.y + p2.y) % upper_bound;

    return ret_point;
}
