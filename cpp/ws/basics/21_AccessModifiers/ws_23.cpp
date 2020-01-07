#include <iostream>
#include <cstdio>

class X
{
public:
    X(int a) : m_a(a)
    {}

    bool operator==(const X& other_) const
    {
        return m_a == other_.m_a;
    }

    int GetValue() const
    {
        return m_a;
    }

private:
    int m_a;
};

X operator+(const X& x1_, const X& x2_)
{
    return X(x1_.GetValue() + x2_.GetValue());
}



int main()
{
    X x1(3);
    X x2(6);

    printf("x1+X2: %d\n", (x1+x2).GetValue());
    printf("x1==X2: %d\n", (x1==x2));

    return 0;
}