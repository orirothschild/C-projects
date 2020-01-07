#include <iostream>
#include <cstdio>

int main()
{
    int i = 8;
    char c = 'a';

    printf("%p\n", (void *)&i);
    int& ip = i;
    char & cp = c;

    printf("%d\n", i);
    printf("%c\n", c);

    ip = 9;
    cp = 'b';

    printf("%d\n", i);
    printf("%c\n", c);
    printf("%d\n", ip);
    printf("%c\n", cp);

    printf("%p\n", (void *)&i);
    printf("%p\n", (void *)&ip);

    return 0;
}