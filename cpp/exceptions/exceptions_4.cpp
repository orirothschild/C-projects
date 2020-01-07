#include <iostream>
#include <typeinfo>
using namespace std;

struct ThrowAtDefCtor
{
    ThrowAtDefCtor()
    {
        cout << "ThrowAtDefCtor DefCtor" << endl;
        throw bad_cast();
    }
    ThrowAtDefCtor(int) { cout << "ThrowAtDefCtor Ctor (int)" << endl;}
    ~ThrowAtDefCtor() { cout << "ThrowAtDefCtor Dtor " << endl;}
};

struct NoThrow
{
    NoThrow() {cout << "NoThrow Ctor" << endl;}
    ~NoThrow() {cout << "NoThrow Dtor" << endl;}
};

class X
{
public:
    X() : m_tdc(2) {cout << "X Ctor" << endl;}
    ~X() {cout << "X Dtor" << endl;}
private:
    NoThrow m_nt;
    ThrowAtDefCtor m_tdc;
};

class Y
{
public:
    Y() {cout << "Y Ctor" << endl;}
    ~Y() {cout << "Y Dtor" << endl;}
private:
    ThrowAtDefCtor m_dtc;
    NoThrow m_nt;
};

class Z
{
public:
    Z() {cout << "Z Ctor" << endl;}
    ~Z() {cout << "Z Dtor" << endl;}
private:
    NoThrow m_nt;
    ThrowAtDefCtor m_dtc;
};


class YPtrs
{
public:
    YPtrs()
    : m_dtc(new ThrowAtDefCtor)
    , m_nt(new NoThrow)
    {
        cout << "YPtrs Ctor" << endl;
    }
    ~YPtrs()
    {
        cout << "YPtrs Dtor" << endl;
        delete m_nt;
        delete m_dtc;
    }
private:
    ThrowAtDefCtor *m_dtc;
    NoThrow *m_nt;
};

class ZPtrs
{
public:
    ZPtrs()
    {
        cout << "ZPtrs Ctor" << endl;
        m_nt = new NoThrow;
        m_dtc = new ThrowAtDefCtor;
    }
    ~ZPtrs()
    {
        cout << "ZPtrs Dtor" << endl;
        delete m_dtc;
        delete m_nt;
        
    }
private:
    NoThrow *m_nt;
    ThrowAtDefCtor *m_dtc;
};


int main()
{
    try
    {
        X var1;
        //Y var1;
        //Z var1;
        //YPtrs var1;
        //ZPtrs var1;
    }
    catch(exception& e)
    {
        cout << "exceptiin cout. what:" << e.what() << endl;
    }

    return 0;
}