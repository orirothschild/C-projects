#include <iostream>
#include <cstdio>
#include <cstdlib>

int main()
{
    float *new_fp = new float(12.3);
    float new_f = *new_fp;
    float old_f = 12.3;

    delete new_fp;
    

    int *ptr = (int *)malloc(1000 * sizeof(int));
    delete ptr;
    int *ptr2 = new int[1000];
    free(ptr);


    return 0;
}