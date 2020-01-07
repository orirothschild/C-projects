#ifndef ILRD_CIRCLE_HPP
#define ILRD_CIRCLE_HPP

#include "glut_utils.h" /* glut utils */
#include "point.hpp"    /* API */
#include "shape.hpp"    /* API */

namespace ilrd
{
class Circle : public Shape
{
public:
    explicit Circle(double x = 0, double y = 0, int color = COLOR_WHITE, size_t radius = 0);
    Circle(const Circle& other_);
    
    void Display(const Point& pivot);
    size_t GetRadius();
    void SetRadius(size_t radius);
    
private:
    size_t m_radius;
};

} // end namespace ilrd

#endif // ILRD_CIRCLE_HPP
