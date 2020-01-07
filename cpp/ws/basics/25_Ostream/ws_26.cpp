#include <iostream>
//#include <cstdio>

class X;

//std::ostream& operator<<(std::ostream& os_, const X& x_);

class X
{
    std::ostream& operator<<(std::ostream& os_);

public:
    X(int a) : m_a(a) {}
    int GetValue() const { return m_a; }

private:
    int m_a;
};

std::ostream& operator<<(std::ostream& os_, const X& x_)
{
    return os_ << x_.GetValue();
}

/* std::ostream& operator<<(std::ostream& os_, char x_)
{
    printf("%p ", &x_);
    return os_ << &x_;
} */



int main()
{
    X x1(3);
    X x2(6);
    int i = 78;
    double d = 3.14;
    float f = 5.17;
    char c = 'Y';

    std::cout
        << " x1:" << x1
        << " x2:" << x2
        << " " << i << " " << &i
        << " " << d << " " << &d
        << " " << f << " " << &f
        << " " << c << " " << (void *)&c << std::endl;

    return 0;        
}

