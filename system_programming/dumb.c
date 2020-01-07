#include <stdio.h>


int main()
{
    int num = 5;
    
    FILE *fp = fopen("blerg", "w+");
    fprintf(fp, "%p\n", &num);
    
    fclose(fp);
    
    printf("The address is %p\n",(void*)&num);
    
    return 0;
}
