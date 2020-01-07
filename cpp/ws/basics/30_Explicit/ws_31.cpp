#include <iostream>

/* class X
{
public:
    explicit X();
    X(int a_);
    explicit X(int a_, int b_);
    void Foo();
private:
    int m_a;
};

X::X() : m_a(0) {}
X::X(int a_) : m_a(a_) {}
X::X(int a_, int b_) : m_a(a_ + b_) {}
 */
class Y
{
public:
    explicit Y();
    Y(double a_);
    explicit Y(double a_, double b_);
    void Foo();
private:
    double m_a;
};

Y::Y() : m_a(0) {}
Y::Y(double a_) : m_a(a_) {}
Y::Y(double a_, double b_) : m_a(a_ + b_) {}



/* void X::Foo()
{
    std::cout << m_a << std::endl;
}

void Fifi(X x_)
{
    x_.Foo();
} */

void Y::Foo()
{
    std::cout << m_a << std::endl;
}

void Fifi(Y y_)
{
    y_.Foo();
}


int main()
{
    /* X x1(7.1);

    Fifi(x1);
    Fifi(X(7.3));
    Fifi(9.4);
 */
    int i = 7;
    Y y1(i);

    double d = static_cast<double>(i);

    Fifi(y1);
    Fifi(Y(8));
    Fifi(d);

    //Fifi(3,4);

    return 0;
}