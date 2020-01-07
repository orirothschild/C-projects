#include <stdio.h>

#include <stdlib.h>

int g_i = 18;
static int g_i2 = 19;
const int G_I_JOE = 20;
int i_bss;
short s_bss;

int Foo(int x)
{
    int y = 5;
    printf("location of   : %p\n", (void*) &y);

    return (x + y);
}

static int Bar(int x)
{
    int z = 10;
    printf("location of   : %p\n", (void*) &z);
    return (x + z);
}


struct hardy
{
    int laurel;
};

union bob
{
    char *kane;
};


int main() 
{

struct hardy funnyman = {0};
union bob batman = {0};

char c = 'a';
short s = 2;
int i = 3;
float f = 6;
double d = 7;
size_t st = 8;

char char_array[5] = {0};
short short_array[5] = {0};
int int_array[5] = {0};
float float_array[5] = {0};
double dbl_array[5] = {0};
size_t size_t_array[5] = {0};

char *str = "b";
short *s_p = &s;
int *i_p = &i;
float *f_p = &f;
double *d_p = &d;
size_t *st_p = &st;

static char c2 = 'c';
const short s2 = 14;
volatile float f2 = 15.0;
extern double d2;
size_t st2_bss[100000];

volatile int *v_i_p = NULL;
register short rs = 4;





printf("location of code                        : %p\n", (void*) main);

printf("location of heap                        : %p\n", (void*) malloc(1));

printf("location of stack                       : %p\n", (void*) &i);


printf("location of global int                  : %p\n", (void*) &g_i);
printf("location of static global int           : %p\n", (void*) &g_i2);
printf("location of const global int            : %p\n", (void*) &G_I_JOE);
printf("location of global func pointer         : %p\n", (void*) Foo);
printf("location of global static func pointer  : %p\n", (void*) Bar);
printf("location of struct                      : %p\n", (void*) &funnyman);
printf("location of union                       : %p\n", (void*) &batman);
printf("location of char                        : %p\n", (void*) &c);
printf("location of short                       : %p\n", (void*) &s);
printf("location of int                         : %p\n", (void*) &i);
printf("location of float                       : %p\n", (void*) &f);
printf("location of double                      : %p\n", (void*) &d);
printf("location of size_t                      : %p\n", (void*) &st);
printf("location of char array                  : %p\n", (void*) char_array);
printf("location of short array                 : %p\n", (void*) short_array);
printf("location of int array                   : %p\n", (void*) int_array);
printf("location of float array                 : %p\n", (void*) float_array);
printf("location of double array                : %p\n", (void*) dbl_array);
printf("location of size_t array                : %p\n", (void*) size_t_array);
printf("location of string                      : %p\n", (void*) str);
printf("location of short pointer               : %p\n", (void*) &s_p);
printf("location of int pointer                 : %p\n", (void*) &i_p);
printf("location of float pointer               : %p\n", (void*) &f_p);
printf("location of double pointer              : %p\n", (void*) &d_p);
printf("location of size_t pointer              : %p\n", (void*) &st_p);
printf("location of static char                 : %p\n", (void*) &c2);
printf("location of const short                 : %p\n", (void*) &s2);
printf("location of volatile float              : %p\n", (void*) &f2);
printf("location of extern double               : %p\n", (void*) &d2);
printf("location of bss size_t                  : %p\n", (void*) st2_bss);
printf("location of volatile int pointer        : %p\n", (void*) v_i_p);
/*printf("location of   : %p\n", (void*) &rs);*/
printf("location of short (unitialized)         : %p\n", (void*) &s_bss);
printf("location of int (unitialized)           : %p\n", (void*) &i_bss);



return 0;

}
