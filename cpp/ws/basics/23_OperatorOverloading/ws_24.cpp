namespace nsa
{
void Foo() {}
namespace nsa_a
{
void Foo() {}    
} //namespace nsa_a
} //namespace nsa

namespace nsb
{
void Foo() {}
void Bar() {}
void Fishi() {}
} //namespace nsb

namespace nsa
{
void AnotherFunc() {}
}

void A()
{
    nsa::Foo();
    using nsb::Foo;
    Foo();
}

using namespace nsa;
using namespace nsb;
namespace nsaaa=nsa::nsa_a;

void B()
{
    nsaaa::Foo();
    //Foo();
    Bar();
}

int main()
{
    return 0;
}