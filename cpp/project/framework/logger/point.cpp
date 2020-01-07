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


void Point::AdjustBy(struct Point p, int upper_bound)
{
    x = (x + p.x) % upper_bound;
    y = (y + p.y) % upper_bound;
}

void Point::AdjustBy(int dx, int dy, int upper_bound)
{
    x = (x + dx) % upper_bound;
    y = (y + dy) % upper_bound;
}

double Point::Length()
{
    return sqrt((x * x) + (y * y));
}

void Point::Print(char open, char close)
{
    printf("%c%d, %d%c\n",open, x, y, close);
}
void Point::Print(paren p)
{
    printf("%c%d, %d%c\n",p, x, y, g_Paren_Table[p]);
}


struct Point Add(struct Point p1, struct Point p2, int upper_bound)
{
    Point ret_point;
    ret_point.x = (p1.x + p2.x) % upper_bound;
    ret_point.y = (p1.y + p2.y) % upper_bound;

    return ret_point;
}
