#include "line.hpp"                 /* API */
#include "./../include/point.hpp"   /* API */

namespace ilrd
{

Line::Line(double x, double y, int color, size_t length, double angle)
: Shape(x, y, color, 2, angle)
, m_length(length)
{}

Line::Line(const Line& other_)
: Shape(other_)
, m_length(other_.m_length)
{}

void Line::Display(const Point& pivot)
{
    double x = GetX() + pivot.GetX();
    double y = GetY() + pivot.GetY();

    int x1 = x - m_length / 2;
    int y1 = y;
    int x2 = x + m_length / 2;
    int y2 = y;

    Point p1(x1,y1);
    Point p2(x2,y2);

    double new_angle = (GetAngleInRadians());
    Point CenterPoint(x, y);

    p1.Revolve(CenterPoint, new_angle);
    p2.Revolve(CenterPoint, new_angle);

    DrawPolygon(GetColor(), GetNumOfPoints(),
               (int)p1.GetX(), (int)p1.GetY(),
               (int)p2.GetX(), (int)p2.GetY());    
}

} // end namespace ilrd
