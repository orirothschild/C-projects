#include <iostream>
#include <cstdio>
#include <cmath>

#include "point.hpp"

char g_Paren_Table[256] = {0};


void InitTable()
{
    g_Paren_Table['('] = ')';
    g_Paren_Table['['] = ']';
    g_Paren_Table['{'] = '}';
    g_Paren_Table['<'] = '>';
}


Point& Point::AdjustBy(const Point& p, const int upper_bound)
{
    x = (x + p.x) % upper_bound;
    y = (y + p.y) % upper_bound;

    return *this;
}


Point& Point::AdjustBy(const int dx, const int dy, const int upper_bound)
{
    x = (x + dx) % upper_bound;
    y = (y + dy) % upper_bound;

    return *this;
}


double Point::Length() const
{
    return sqrt((x * x) + (y * y));
}


void Point::Print(const char open, const char close) const
{
    printf("%c%d, %d%c\n",open, x, y, close);
}


void Point::Print(paren p) const
{
    printf("%c%d, %d%c\n",p, x, y, g_Paren_Table[p]);
}


Point Add(const Point p1, const Point p2, const int upper_bound)
{
    Point ret_point;
    ret_point.x = (p1.x + p2.x) % upper_bound;
    ret_point.y = (p1.y + p2.y) % upper_bound;

    return ret_point;
}
