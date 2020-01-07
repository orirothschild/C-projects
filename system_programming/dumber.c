#include <stdio.h>


int main()
{
    int *num = NULL;
    FILE *fp = fopen("blerg", "r");
/*    int *check = NULL;*/
    
    fscanf(fp, "%p", (void **)&num);
/*    check = num;*/

    fclose(fp);
    
    printf("The number is %d\n", *num);
    
    return 0;
}
