#include "square.hpp"   /* API */

namespace ilrd
{

Square::Square(double x, double y, int color, size_t height, double angle)
: Rect(x, y, color, height, height, angle)
, m_height(height)
{}

Square::Square(const Square& other_)
: Rect(other_)
, m_height(other_.m_height)
{}

void Square::SetHeight(size_t height)
{
    m_height = height;
}

size_t Square::GetHeight()
{
    return m_height;
}

} // end namespace ilrd
