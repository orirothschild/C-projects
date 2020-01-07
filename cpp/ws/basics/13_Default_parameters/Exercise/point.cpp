#include <iostream>
#include <cstdio>
#include <cmath>

#include "point.hpp"

double g_Total_Length = 0;

char g_Paren_Table[256] = {0};

void InitTable()
{
    g_Paren_Table['('] = ')';
    g_Paren_Table['['] = ']';
    g_Paren_Table['{'] = '}';
    g_Paren_Table['<'] = '>';
}

Point::Point(int x, int y)
{
    m_x = x;
    m_y = y;

    CalculateLength();
}

Point::~Point()
{
    g_Total_Length -= m_length_sqrt;
}

void Point::SetX(const int x, const int upper_bound)
{
    m_x = x % upper_bound;
    
    CalculateLength();
}

void Point::SetY(const int y, const int upper_bound)
{
    m_y = y % upper_bound;

    CalculateLength();
}

int Point::GetX() const
{
    return m_x;
}

int Point::GetY() const
{
    return m_y;
}

Point& Point::AdjustBy(const Point& p, const int upper_bound)
{
    m_x = (m_x + p.m_x) % upper_bound;
    m_y = (m_y + p.m_y) % upper_bound;

    CalculateLength();

    return *this;
}

Point& Point::AdjustBy(const int dx, const int dy, const int upper_bound)
{
    m_x = (m_x + dx) % upper_bound;
    m_y = (m_y + dy) % upper_bound;

    CalculateLength();

    return *this;
}

double Point::Length()
{        
    return m_length_sqrt;
}

void Point::CalculateLength()
{
    g_Total_Length -= m_length_sqrt;
    m_length_sqrt = sqrt(pow(m_x, 2) + pow(m_y, 2));
    g_Total_Length += m_length_sqrt;
}

void Point::Print(char open, char close) const
{
    printf("%c%d, %d%c\n",open, m_x, m_y, close);
}

void Point::Print(paren p) const
{
    printf("%c%d, %d%c\n",p, m_x, m_y, g_Paren_Table[p]);
}

bool Point::IsEqual(Point p) const
{
    return ((m_x == p.m_x) && (m_y == p.m_y));
}

Point Add(const Point p1, const Point p2, const int upper_bound)
{
    Point ret_point;
    ret_point.m_x = (p1.m_x + p2.m_x) % upper_bound;
    ret_point.m_y = (p1.m_y + p2.m_y) % upper_bound;

    return ret_point;
}

double GetTotalLength()
{
    return g_Total_Length;
}
