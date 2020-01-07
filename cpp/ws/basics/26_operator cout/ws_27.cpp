#include <iostream>



class X
{
    friend std::ostream& operator<<(std::ostream& os_, const X& x_);

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

int main()
{
    X x1(3);
    X x2(6);
    
    std::cout
        << " x1:" << x1
        << " x2:" << x2 << std::endl;

    return 0;        
}


