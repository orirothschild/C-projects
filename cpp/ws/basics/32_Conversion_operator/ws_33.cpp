#include <cstdio>

volatile const int i = 3;
const int i2 = 0;

int j = 5;
int j2;

int main()
{
    
    int *ip = (int *)&i;
    printf("%d %d\n", i, *ip);
    printf("%p %p\n", &i, ip);
    //*ip = 5;

    printf("%d %d\n", i, *ip);
    printf("%p %p\n", &i, ip);

    return 0;
}