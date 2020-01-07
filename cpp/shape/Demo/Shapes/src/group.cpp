#include <cassert>  /* assert */
#include <cmath>    /* pi       */

#include "./../include/point.hpp"   /* utils */
#include "group.hpp"                /* API */


namespace ilrd
{

Group::Group()
: Shape()
, m_shapeCounter(0)
, m_shapeArr(new Shape*[20])
{}

Group::Group(const Group& other_)
: Shape()
, m_shapeCounter(other_.m_shapeCounter)
, m_shapeArr(new Shape*[20])
{
    for (int i = 0; i < m_shapeCounter; ++i)
    {
        m_shapeArr[i] = other_.m_shapeArr[i];
    }
}

Group::~Group()
{
    delete[] m_shapeArr;
}

void Group::AddShape(Shape *shape_)
{
    assert(20 > m_shapeCounter);

    ToCartesian();

    m_shapeArr[m_shapeCounter++] = shape_;
    CalculateCenter();

    ToOffset();
}

void Group::ToOffset()
{
    for (int i = 0; i < m_shapeCounter; ++i)
    {
        m_shapeArr[i]->GetCenterPoint() -= GetCenterPoint();
    }
}

void Group::ToCartesian()
{
    for (int i = 0; i < m_shapeCounter; ++i)
    {
        m_shapeArr[i]->GetCenterPoint() += GetCenterPoint();
    }
}

void Group::CalculateCenter()
{
    double averageX = 0;
    double averageY = 0;

    for (int i = 0; i < m_shapeCounter; ++i)
    {
        averageX += m_shapeArr[i]->GetX();
        averageY += m_shapeArr[i]->GetY();
    }

    averageX /= m_shapeCounter;
    averageY /= m_shapeCounter;

    m_pt = Point(averageX, averageY);
}

void Group::Display(const Point& pivot)
{
    (void)pivot;

    for (int i = 0; i < m_shapeCounter; ++i)
    {
        m_shapeArr[i]->Display(GetCenterPoint());
    }
}

void Group::Rotate(double angle)
{
    angle = ToRadian(angle);
    Point centerPoint = GetCenterPoint();

    ToCartesian();
    for (int i = 0; i < m_shapeCounter; ++i)
    {
        double old_angle = m_shapeArr[i]->GetAngleInRadians();
        m_shapeArr[i]->Revolve(centerPoint, angle);
        m_shapeArr[i]->Rotate(ToDegree(old_angle + angle));
    }
    ToOffset();
}

void Group::Revolve(const Point& pivot, double angle)
{
    angle = ToRadian(angle);
    Shape::Revolve(pivot, angle);
}

void Group::Move(double x, double y)
{
    Step(&GetCenterPoint(), x, y);
}

} // end namespace
