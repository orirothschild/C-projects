#include <cmath>                    /* M_PI */

#include "./../include/point.hpp"   /* API   */
#include "shape.hpp"                /* API   */

namespace ilrd
{

Shape::Shape(double x, double y, int color, size_t numOfPoints, double angle)
: m_pt(x,y)
, m_color(color)
, m_numOfPoints(numOfPoints)
, m_angle(angle)
{}

Shape::Shape(const Shape& other_)
: m_pt(other_.m_pt)
, m_color(other_.m_color)
, m_numOfPoints(other_.m_numOfPoints)
{}

void Shape::SetColor(int color)
{
    m_color = color;
}

int Shape::GetColor()
{
    return m_color;
}

double Shape::GetX()
{
    return m_pt.GetX();
}


double Shape::GetY()
{
    return m_pt.GetY();
}

size_t Shape::GetNumOfPoints()
{
    return m_numOfPoints;
}

void Shape::SetRelationalCoordinates(const Point& pivot)
{
    m_pt += pivot;
}

void Shape::UnSetRelationalCoordinates(const Point& pivot)
{
    m_pt -= pivot;
}

void Shape::Display(const Point& pivot)
{
    (void)pivot;
}

void Shape::Move(double x, double y)
{
    Step(&m_pt, x, y);
}

void Shape::Rotate(double angle)
{
    m_angle = angle;
}

Point& Shape::GetCenterPoint()
{
    return m_pt;
}

double Shape::GetAngle()
{
    return m_angle;
}

double Shape::GetAngleInRadians()
{
    return m_angle * M_PI / 180;
}

void Shape::SetAngle(double angle)
{
    m_angle = angle;
}

void Shape::Revolve(const Point& pivot, double angle)
{
    m_pt.Revolve(pivot, angle);
}

double ToRadian(double angle)
{
    return angle * M_PI / 180;
}

double ToDegree(double angle)
{
    return angle * 180 / M_PI;
}

} // end namespace ilrd
