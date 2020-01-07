#include <cstddef>      /* size_t */
#include "circle.hpp"   /* API */


namespace ilrd
{

Circle::Circle(double x, double y, int color, size_t radius)
: Shape(x, y, color, 1)
, m_radius(radius)
{}

Circle::Circle(const Circle& other_)
: Shape(other_)
, m_radius(other_.m_radius)
{}


void Circle::Display(const Point& pivot)
{   
    DrawCircle(GetColor(), GetX() + pivot.GetX(), GetY() + pivot.GetY(),
               GetRadius());
}


size_t Circle::GetRadius()
{
    return m_radius;
}

void Circle::SetRadius(size_t radius)
{
    m_radius = radius;
}

} // end namespace ilrd
