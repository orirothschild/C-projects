#ifndef ILRD_SQUARE_HPP
#define ILRD_SQUARE_HPP

#include <cstddef>      /* size_t */

#include "glut_utils.h" /* glut utils */
#include "point.hpp"    /* API */
#include "rect.hpp"     /* API */

namespace ilrd
{
class Square : public Rect
{
public:
    explicit Square(double x = 0, double y = 0, int color = COLOR_WHITE,
                size_t height = 0, double angle = 0);
    Square(const Square& other_);

    void SetHeight(size_t height);
    size_t GetHeight();

private:
    size_t m_height;
};

} // end namespace ilrd

#endif // ILRD_SQUARE_HPP
                                                                 