#include <cstdio>


extern "C" void Foo();

void Foo()
{
    printf("nada\n");
}

void Foo(int i)
{
    (void)i;
    printf("int\n");
}

void Foo(char c)
{
    (void)c;
    printf("char\n");
}





/* int main()
{
    int i = 0;
    char c = '0';
    
    Foo();
    Foo(i);
    Foo(c);

    return 0;
} */