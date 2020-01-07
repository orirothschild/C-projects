#include <iostream>
#include <cstdio>

class X
{
public:
    explicit X();
    X(int a) : m_a(a){};
    operator unsigned int();
    operator int();
    
private:
    int m_a;
};

X::X() : m_a(7) {}
X::operator unsigned int()
{
    printf("unsigned int\n");
    return m_a;
}
X::operator int()
{
    printf("int\n");
    return m_a;
}


void Fifi(double x_)
{
    std::cout << x_ << std::endl;
}

int main()
{
    X x1;
    
    Fifi(9);
    //Fifi(x1);

    return 0;
}