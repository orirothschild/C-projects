#include <iostream>

namespace inheritance
{
class X
{
public:
    X(double d_) : m_a(d_){std::cout << "ctor X: " << this << std::endl;}
    virtual ~X(){std::cout << "dtor X: " << this << std::endl;}

private:
    double m_a;
};


class Y : public X
{
public:
    Y(double d_, int i_) : X(d_), m_b(i_) {std::cout << "ctor Y: " << this << std::endl;}
    ~Y() {std::cout << "dtor Y: " << this << std::endl;}
    
private:
    int m_b;
};

} //end namespace

using namespace inheritance;
int main()
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);
    
    X& x1 = y1;
    X& x2 = y2;

    x1 = x2;
    y3 = y4;

    return 0;
}
