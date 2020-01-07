#include <iostream>
#include <cstdio>

#include "point.hpp"
#include "Polygon.hpp"

#include "./../../../../utils.h"

#define UPPER_BOUND (100)

Polygon::Polygon(size_t numPoints)
: m_numPoints(numPoints)
, m_points(new Point[numPoints])
{
}

Polygon *Polygon::PolygonDuplicate(const Polygon& other_)
{
    Polygon *dup_polygon = new Polygon(m_numPoints);
    
    for(size_t i = 0; i < m_numPoints; ++i)
    {
        dup_polygon->m_points[i].AdjustBy(other_.m_points[i], UPPER_BOUND);
    }

    return dup_polygon;
}

Polygon::Polygon(const Polygon& other_)
: m_numPoints(other_.m_numPoints)
, m_points(new Point[m_numPoints]) //cctor
{
    for(size_t i = 0; i < m_numPoints; ++i)
    {
        m_points[i].AdjustBy(other_.m_points[i], UPPER_BOUND);
    }
}

Polygon& Polygon::operator=(const Polygon& other_) //assignment operator
{
    m_numPoints = other_.m_numPoints;
    delete[] m_points;
    m_points = new Point[m_numPoints];

    for(size_t i = 0; i < m_numPoints; ++i)
    {
        m_points[i] = other_.m_points[i];
        /* m_points[i].AdjustBy(other_.m_points[i], UPPER_BOUND); */
    }

    return *this;
}

Polygon::~Polygon() //dtor
{
    delete[] m_points;
}

void Polygon::Add(const Point &point)
{
    m_numPoints += 1;
    Point *point_arr = new Point[m_numPoints];

    for(size_t i = 0; i < m_numPoints - 1; ++i)
    {
        point_arr[i] = m_points[i];
    }

    point_arr[m_numPoints - 1] = point;

    delete[] m_points;
    m_points = point_arr;
}

bool Polygon::IsEqual(const Polygon& polygon) const
{
    if (m_numPoints != polygon.m_numPoints)
    {
        return false;
    }

    for(size_t i = 0; i < m_numPoints; ++i)
    {
        if (!(m_points[i].IsEqual(polygon.m_points[i])))
        {
            return false;
        }
    }

    return true;
}

void Polygon::Print() const
{
    for(size_t i = 0; i < m_numPoints; ++i)
    {
        m_points[i].Print('{', '}');
    }
}
