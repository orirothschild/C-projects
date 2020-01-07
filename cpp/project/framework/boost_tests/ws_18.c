#include <stdio.h>
#include <stdlib.h>

int main()
{
    float f = 12.6;
    float *keeper = (float *)malloc(sizeof(float));
    float *fp = keeper;
    *keeper = f;

    printf("f is %f\n", *fp);
    *fp = 6.17;
    free(fp);

    printf("f is %f\n", *fp);
    *fp = 6.17;



    return 0;
}