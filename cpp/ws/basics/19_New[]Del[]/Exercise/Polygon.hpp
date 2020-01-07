#ifndef ILRD_POLYGON_H
#define ILRD_POLYGON_H

#include <iostream>
#include <cstdio>

#include "point.hpp"



struct Polygon
{    
    explicit Polygon(size_t numPoints = 0); //default ctor
    Polygon(const Polygon& other_); //cctor
    Polygon& operator=(const Polygon& other_); //assignment operator
    ~Polygon();

    void Add(const Point &p);
    bool IsEqual(const Polygon&) const;
    void Print() const;

    size_t m_numPoints;
    Point *m_points;
private:
    Polygon *PolygonDuplicate(const Polygon& other_);
};


#endif  //POLYGON_H