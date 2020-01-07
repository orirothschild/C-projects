#ifndef ILRD_RECT_HPP
#define ILRD_RECT_HPP

#include <cstddef>      /* size_t */

#include "glut_utils.h" /* glut utils */
#include "point.hpp"    /* API */
#include "shape.hpp"    /* API */

namespace ilrd
{
class Rect : public Shape
{
public:
    explicit Rect(double x = 0, double y = 0, int color = COLOR_WHITE,
                  size_t width = 0, size_t length = 0, double angle = 0);
    Rect(const Rect& other_);
    
    virtual void Display(const Point& pivot);
    void SetLength(size_t length);
    size_t GetLength();
    void SetWidth(size_t width);
    size_t GetWidth();

private:
    size_t m_length;
    size_t m_width;
};

} // end namespace ilrd

#endif // ILRD_RECT_HPP
