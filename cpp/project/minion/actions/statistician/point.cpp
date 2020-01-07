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

void Point::SetX(const int x)
{
    this->x = x;
    
    CalculateLength();
}

void Point::SetY(const int y)
{
    this->y = y;

    CalculateLength();
}

int Point::GetX() const
{
    return x;
}

int Point::GetY() const
{
    return y;
}

Point& Point::AdjustBy(const Point& p, const int upper_bound)
{
    x = (x + p.x) % upper_bound;
    y = (y + p.y) % upper_bound;

    CalculateLength();

    return *this;
}

Point& Point::AdjustBy(const int dx, const int dy, const int upper_bound)
{
    x = (x + dx) % upper_bound;
    y = (y + dy) % upper_bound;

    CalculateLength();

    return *this;
}

double Point::Length()
{        
    return length_sqrt;
}

void Point::CalculateLength()
{
    length_sqrt = sqrt(pow(x, 2) + pow(y, 2));
}

void Point::Print(char open, char close) const
{
    printf("%c%d, %d%c\n",open, x, y, close);
}
void Point::Print(paren p) const
{
    printf("%c%d, %d%c\n",p, x, y, g_Paren_Table[p]);
}

bool Point::IsEqual(Point p) const
{
    if ((this->x == p.x) && (this->y == p.y))
    {
        return true;
    }
    return false;
}

Point Add(const Point p1, const Point p2, const int upper_bound)
{
    Point ret_point;
    ret_point.x = (p1.x + p2.x) % upper_bound;
    ret_point.y = (p1.y + p2.y) % upper_bound;

    return ret_point;
}
