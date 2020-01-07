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
    Y() : m_b(){std::cout << "ctor Y: " << this << std::endl;}
    ~Y() {std::cout << "dtor Y: " << this << std::endl;}

private:
    int m_b;
};

void Foo(X x)
{
    std::cout << "Foo" << std::endl;
}

} //end namespace

using namespace inheritance;
int main()
{
    Y y1;
    Foo(y1);

    return 0;
}
