#include <iostream>
#include <exception>
#include <cstdlib>

using namespace std;

struct BadDog: public runtime_error
{
    BadDog(const string& s_="This is a bad dog")
    : runtime_error(s_){}
    ~BadDog() {}
};

class X
{
public:
    X() : m_a(1) { cout << "X Ctor" << endl; }
    ~X() { cout << "X Dtor" << endl; }

private:
    int m_a;
};

/* void Fifi() throw (X) */
void Fifi()
{
    //throw BadDog("bad pup\n");
    //throw __throw_bad_function_call;
    //throw length_error("blerg\n");
    //throw overflow_error("blerg\n");
    throw bad_alloc();
    cerr << "Fifi() after throw" << endl;
}
void Foo()
{
    cerr << "Foo() after Fifi()" << endl;
    X x;

    Fifi();
    
}
void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

int main()
{
    //Bar();
    try
    {
        Bar();
    }
    catch(bad_alloc)
    {
        cerr << "Out of memory! exiting."; exit(2);
    }
    catch(BadDog& b)
    {
        cerr << "Bad dog exception1: " << b.what(); exit(3);
    }
    catch(exception& r)
    {
        cerr << "Bad dog exception2: " << r.what(); exit(3);
    }
    /* catch(...)
    {
        cerr << "Bad dog exception3: " << endl; exit(4);
    } */

    return 0;
}
