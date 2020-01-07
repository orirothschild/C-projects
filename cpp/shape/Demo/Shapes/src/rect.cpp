#include "rect.hpp" /* API */

namespace ilrd
{

Rect::Rect(double x, double y, int color, size_t length, size_t width,
           double angle)
: Shape(x, y, color, 4, angle)
, m_length(length)
, m_width(width)
{}

Rect::Rect(const Rect& other_)
: Shape(other_)
, m_length(other_.m_length)
, m_width(other_.m_width)
{}

void Rect::Display(const Point& pivot)
{
    double x = GetX() + pivot.GetX();
    double y = GetY() + pivot.GetY();

    double x1 = x - m_width / 2;
    double y1 = y - m_length / 2;
    double x2 = x + m_width / 2;
    double y2 = y + m_length / 2;

    Point p1(x1, y1);
    Point p2(x1, y2);
    Point p3(x2 ,y2);
    Point p4(x2 ,y1);

    double new_angle = (GetAngleInRadians());
    Point CenterPoint(x,y);

    p1.Revolve(CenterPoint, new_angle);
    p2.Revolve(CenterPoint, new_angle);
    p3.Revolve(CenterPoint, new_angle);
    p4.Revolve(CenterPoint, new_angle);

    DrawPolygon(GetColor(), GetNumOfPoints(),
               (int)p1.GetX(), (int)p1.GetY(),
               (int)p2.GetX(), (int)p2.GetY(),
               (int)p3.GetX(), (int)p3.GetY(),
               (int)p4.GetX(), (int)p4.GetY());
}

void Rect::SetLength(size_t length)
{
    m_length = length;
}

size_t Rect::GetLength()
{
    return m_length;
}

void Rect::SetWidth(size_t width)
{
    m_width = width;
}

size_t Rect::GetWidth()
{
    return m_width;
}

} // end namespace ilrd
