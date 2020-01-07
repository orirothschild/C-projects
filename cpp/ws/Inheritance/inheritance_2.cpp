#include <iostream>

namespace inheritance
{
class X
{
public:
    X() : m_a(){std::cout << "ctor X: " << this << std::endl;}
    virtual ~X(){std::cout << "dtor X: " << this << std::endl;}

private:
    double m_a;
};


class Y : public X
{
public:
    Y() : X(), m_b(){std::cout << "ctor Y: " << this << std::endl;}
    ~Y() {std::cout << "dtor Y: " << this << std::endl;}
private:
    int m_b;
};


} //end namespace

using namespace inheritance;
int main()
{
    X* xp = new X[5];
    Y* yp = new Y[5];
    std::cout << std::endl;

    X* x2 = new X[2];

    std::cout << std::endl;

    delete[] x2;

    std::cout << std::endl;

    delete[] xp;

    return 0;
}
