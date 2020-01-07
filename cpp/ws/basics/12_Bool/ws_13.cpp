#include <cstdio>

void Foo(int arg1, int arg2  = 3, float arg3 = 4)
{
    printf("arg1 %d\n", arg1);
    printf("arg2 %d\n", arg2);
    printf("arg3 %f\n", arg3);
}


int main()
{
/*     Foo(3);
    Foo(6, 5);
    Foo(4, 7, 8.7); */
    Foo(3,5.5);
}
