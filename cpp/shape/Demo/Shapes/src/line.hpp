#ifndef ILRD_LINE_HPP
#define ILRD_LINE_HPP

#include "glut_utils.h" /* glut utils */
#include "point.hpp"    /* API */
#include "shape.hpp"    /* API */

namespace ilrd
{

class Line : public Shape
{
public:
    explicit Line(double x = 0, double y = 0, int color = COLOR_WHITE,
                  size_t length = 0, double angle = 0);
    Line(const Line& other_);
    
    void Display(const Point& pivot);
    void SetLength();
    size_t GetLength();

private:
    size_t m_length;
};

} // end namespace ilrd

#endif // ILRD_LINE_HPP