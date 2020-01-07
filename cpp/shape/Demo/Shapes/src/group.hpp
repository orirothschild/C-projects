#ifndef ILRD_GROUP_HPP
#define ILRD_GROUP_HPP

#include "point.hpp"    /* API */
#include "shape.hpp"    /* API */


namespace ilrd
{

class Group : public Shape
{
public:
    Group();
    ~Group();
    explicit Group(const Group& other_);

    void AddShape(Shape *shape_);
    void CalculateCenter();
    void Display(const Point& pivot);
    void Rotate(double angle);
    void Revolve(const Point& pivot, double angle);
    void Move(double x, double y);
    void ToCartesian();
    void ToOffset();

private:
    int m_shapeCounter;
    Shape **m_shapeArr;
};

} // end namespace

#endif // ILRD_GROUP_HPP