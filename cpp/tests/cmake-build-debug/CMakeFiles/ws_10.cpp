#include <cstdio>

enum E1 { AA, BB, CC, DD };
enum E2 { TT, YY };


int main()
{
    int i;
    E1 e = BB;
    E1 b = BB;
    printf("%d\n",e);
    e = CC;
    printf("%d\n",e);
    printf("%d\n",b);
    /* ++e; */
    i = e;
    printf("%d\n",i);
}
