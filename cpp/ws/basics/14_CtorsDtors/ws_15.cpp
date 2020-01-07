#include <cstdio>


struct X
{
    //explicit X(); //default initialization - called constructor or Ctor

    //X(int a_, int b_); //regular (non default) Ctor

    //X(const X& other_); //copy initialization - copy constructor CCtor

    //X& operator=(const X& other_); // copy assignment operator

    ~X(); //de-initialization funciton - called the destructor, Dtor

    int m_a;
    int m_b;
};

struct Y
{
    X m_x;
    int m_i;
};

/* X::X() : m_a(3), m_b(4)
{
    printf("Default Ctor: %p, %d, %d\n", (void *)this, m_a, m_b);
    m_a = 9;
    //m_b = 11;
} */

/* X::X(int a_, int b_) : m_a(a_), m_b(b_)
{
    printf("Ctor(int, int) : %p, %d, %d\n", (void *)this, m_a, m_b);
} */

/* X::X(const X& other_) : m_a(other_.m_a), m_b(other_.m_b)
{
    printf("Copy Ctor : %p, %d, %d\n", (void *)this, m_a, m_b);
} */

/* X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    //m_b = other_.m_b; 
    printf("Copy Assignment: %p, %d, %d\n", (void *)this, m_a, m_b);

    return *this;
} */

X::~X()
{
    printf("Dtor: %p, %d, %d\n", (void *)this, m_a, m_b);
}

int main()
{
    /* X x1; */
    X x1 = {0, 1};
    //X x2(7, 1);
    //X x3(8, 10);
    /* X x3; */
    X x4(x1);
 
    /* x1 = x3; */
    //X x5 = x3;

    /* Y y1 = {x1, 0}; */
    //y1.m_x.m_b = 750; //Why is this line commented
    /* Y y2(y1); */
    /* Y y3; */
    /* Y y4(1,1); */
    
    /* y3 = y1; */


    return 0;
}