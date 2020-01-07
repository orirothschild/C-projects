#include <boost/lambda/lambda.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>
//#include <boost/bind/placeholders.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "./../reactor/reactor.hpp"

int testfunc1();
int testfunc2();
void testfunc3();
void testfunc4();
void PrintSomething(int);


class TestClass
{
public:
    TestClass() : m_fd(0) {}
    ~TestClass() {}

    //typedef void result_type;

    void print(int i) {std::cout << "class print func: " << m_fd << " " << i << std::endl;}
    //typedef void result_type;
    //void operator()(int i) {std::cout << "class print func: " << m_fd << " " << i << std::endl;}
    int operator() (int x) {return m_fd += x;}

private:
    int m_fd;
};


int main()
{
    //testfunc1();
    /* int x = testfunc2();
    std::cout << x << std::endl; */
    //testfunc3();
    testfunc4();

    return 0;
}


int testfunc1()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
    std::cout << std::endl;

    return 0;
}

int testfunc2()
{
    using namespace boost::lambda;
    TestClass tc;
    int bl = 5;
    std::cout << bl << std::endl;
    int x = boost::bind<int>(tc, bl)(bl);
//    boost::bind(boost::ref(tc), _1)(bl);
//    int x = boost::bind(boost::type<int>(), tc, _1)(bl);
    std::cout << bl << std::endl;


    return x;
//    return 0;
}


void testfunc3()
{
    using namespace boost::lambda;
    typedef boost::function<void (int)> func;

    func f = PrintSomething;

    f(1);

    int x = 5;

    f = boost::bind(PrintSomething, _1);
    f(x);

    TestClass tc;
    int y = 2;
    f = boost::bind(&TestClass::print, tc, _1);
    f(y);

}

void PrintSomething(int i)
{
    std::cout << "print something: " << i << std::endl;
}

void printfunc(int i, const char *str)
{
    std::cout << str << i << std::endl;
}
void testfunc4()
{
    using namespace boost::lambda;

    typedef boost::function< void (int)> bfunc;

    bfunc f = boost::bind(printfunc, _1, "the int is: ");

    //f(5);

    ilrd::Reactor r;

    //r.Add(0, 0, f);
    r.Start();
}

