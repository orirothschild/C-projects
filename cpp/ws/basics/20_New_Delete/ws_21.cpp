#include <iostream>

//struct X
class X
{
public:
    explicit X(int a_);
    void Foo();

    int GetA() const;
    void SetA(int num);

private:
    int m_a;
    int *m_p;
};

X::X(int a_) : m_a(a_), m_p(new int(a_))
{
}

void X::Foo()
{
    printf("%d\n", m_a);
}


int X::GetA() const
{
    return m_a;
}

void X::SetA(int num)
{
    m_a = num;
}

void Foo(const X &x1)
{
    printf("%d\n", x1.GetA());
}

int main()
{
    X x1(2);

    x1.Foo();
    printf("%d\n", x1.GetA());
    Foo(x1);

    return 0;
}