#include <iostream>

class X
{
public:
    X() : m_a(1) {std::cout << "x ctor" << std::endl;}
    virtual ~X() {std::cout << "x dtor" << std::endl;}
    virtual void Foo() {std::cout << "blerg" << std::endl;}
    int m_a;
};

class Y : public X
{
public:
    Y() : m_b(2) {std::cout << "y ctor" << std::endl;}
    ~Y() {std::cout << "y dtor" << std::endl;}
    void Foo() {std::cout << "honk" << std::endl;}
    int m_b;
};

int main()
{
    Y yArr[3];

    for (int i = 0; i < 3; ++i)
    {
        yArr[i].Foo();
    }

    return 0;
}