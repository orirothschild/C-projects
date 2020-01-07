#include <iostream>
#include <cstdio>
#include <cstdlib>

struct Counter
{
    void Inc();
    void Dec();
    void Foo();
    void Inc(unsigned int delta);

    int m_a;
    int m_b;
    int m_c;
};

struct X
{
    explicit X(); //default initialization - called constructor or Ctor

    X(int a_, int b_); //regular (non default) Ctor

    X(const X& other_); //copy initialization - copy constructor CCtor

    X& operator=(const X& other_); // copy assignment operator

    ~X(); //de-initialization funciton - called the destructor, Dtor

    int m_a;
    int m_b;
};

struct Y
{
    X m_x;
    int m_i;
};

X::X() : m_a(3), m_b(4)
{
    printf("Default Ctor: %p, %d, %d\n", (void *)this, m_a, m_b);
    m_a = 9;
    //m_b = 11;
}

X::X(int a_, int b_) : m_a(a_), m_b(b_)
{
    printf("Ctor(int, int) : %p, %d, %d\n", (void *)this, m_a, m_b);
}

X::X(const X& other_) : m_a(other_.m_a), m_b(other_.m_b)
{
    printf("Copy Ctor : %p, %d, %d\n", (void *)this, m_a, m_b);
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    //m_b = other_.m_b; 
    printf("Copy Assignment: %p, %d, %d\n", (void *)this, m_a, m_b);

    return *this;
}

X::~X()
{
    printf("Dtor: %p, %d, %d\n", (void *)this, m_a, m_b);
}


int main()
{
    X* xp = new X[10];
    float *f = new float(12.6);
    /* float f = 12.6;
    float *fp = (float *)malloc(sizeof(float *));
    fp = &f; */

    std::cout << "f is " << *f << std::endl;

    delete f;

    std::cout << "f is " << *f << std::endl;

    f = new float[4];
    f[0] = 3.14;
    f[1] = 15.3;
    f[2] = 2.17;
    f[3] = 1.13;
    
    std::cout << "f[1] is " << f[1] << std::endl;
    std::cout << "f[3] is " << f[3] << std::endl;
    
    delete[] f;

    std::cout << "f[1] is " << f[1] << std::endl;
    std::cout << "f[3] is " << f[3] << std::endl;

    Counter *c1 = new Counter;
    X *x1 = new X;
    Y *y1 = new Y;

    delete y1;
    delete c1;
    delete x1;

    delete[] xp;
    
}