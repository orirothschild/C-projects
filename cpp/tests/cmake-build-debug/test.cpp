#include <iostream>
#include <cstdio>

int m_a = 10;
void Inc();


struct Counter
{
    void Inc();
    void Dec();
    void IncThis();
    void DecThis();
    void Foo();
    void Inc(unsigned int delta);

    int m_a;
    int m_b;
    int m_c;
};


void Counter::Inc(unsigned int delta)
{
    (void)delta;
    printf("inside Overloaded Inc\n");
}

void Counter::Foo()
{

}

void Counter::Inc()
{
    ++m_a;
    m_b += 2;
}

void Counter::Dec()
{
    --m_a;
    m_b -= 2;
}

void Counter::IncThis()
{
    ++this->m_a;
    m_b += 2;
}


void Counter::DecThis()
{
    --this->m_a;
    m_b -= 2;
}

void Inc();
//Why is the line below not needed?
// typedef struct Counter Counter;

int main()
{
    unsigned int i = 0;
    Counter x1;
    Counter x2;

    printf("the size of counter is %lu\n", sizeof(x1));
    x1.m_a = 7;
    x2.m_a = 0;
    x2.m_b = 16;
    std::printf("x1.m_a = %d\n", x1.m_a);
    std::printf("x2.m_b = %d\n", x2.m_b);
    std::printf("x2.m_b = %d\n", x2.m_b);

    x1.Inc();
    printf("x1.m_a = %d\n", x1.m_a);
    x1.IncThis();
    printf("x1.m_a = %d\n\n\n", x1.m_a);

    x2.Dec();
    std::printf("x2.m_b = %d\n", x2.m_b);
    Inc();
    x1.Inc(i);




    return 0;
}

void Inc()
{
    printf("foo %d\n", ++m_a);
}
