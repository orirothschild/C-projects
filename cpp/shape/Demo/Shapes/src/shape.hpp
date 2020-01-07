#ifndef ILRD_SHAPE_HPP
#define ILRD_SHAPE_HPP

#include "glut_utils.h" /* glut utils */
#include "point.hpp"    /* API */

namespace ilrd
{
class Shape
{
public:
    Shape(double x = 0, double y = 0, int color = COLOR_BLACK,
          size_t numOfPoints = 0, double angle = 0); // not explicit
    Shape(const Shape& other_);

    virtual void Display(const Point& pivot) = 0;
    virtual void Rotate(double angle);
    virtual void Move(double x, double y);
    virtual void Revolve(const Point& pivot, double angle);

    virtual void SetColor(int color);
    virtual int GetColor();
    Point& GetCenterPoint();
    double GetX();
    double GetY();
    void SetAngle(double angle);
    double GetAngle();
    double GetAngleInRadians();
    size_t GetNumOfPoints();
/* 
    void SetRelationalCoordinates(const Point& pivot);
    void UnSetRelationalCoordinates(const Point& pivot); */

protected:
    Point m_pt;
    int m_color;
    size_t m_numOfPoints;
    double m_angle;
};

double ToRadian(double angle);
double ToDegree(double angle);

} // end namespace ilrd

#endif // ILRD_SHAPE_HPP
