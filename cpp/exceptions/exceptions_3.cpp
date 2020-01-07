#include <iostream>
#include <exception>
#include <cstdlib>

using namespace std;

class X
{
public:
    X() : m_a(1) { std::cout << "X Ctor" << std::endl; }
    ~X(); /* { std::cout << "X Dtor" << std::endl; }; */
private:
    int m_a;
};

int Foo(int);
int Bar();

X::~X()
{
    std::cerr << "X Dtor " << Foo(m_a) << std::endl;
}

int Foo(int)
{
    //throw std::bad_alloc();
    
    throw bad_alloc();

    return 0;
}


int Bar()
{
    //throw std::bad_cast();
    return 12;
}

void Fishi()
{
    X x1;
    Foo(5);
    Bar();
}

int main()
{
    //Foo(4);
    //Bar();

    try
    {
        Fishi();
    }
    catch(exception& e)
    {
        cerr << "blerg1: " << e.what() << '\n';
    }
    /* catch(...)
    {
        cerr << "blerg2: " << '\n';
    } */
    
    
    return 0;
}