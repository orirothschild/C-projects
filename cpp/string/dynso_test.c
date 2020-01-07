#include <stdio.h>  /* fprintf */
#include <dlfcn.h>  /* dlopen, dlclose, dlerror */
#include <stdlib.h> /* dlopen, dlclose, dlerror */

typedef void (*lib_func)(void);
/* void (*ptr)(void); */

int main(int argc, char **argv)
{
    char *run_func = argv[2];
    void *lib_handler = NULL;
    lib_func lib_func_handler = NULL;

    (void)argc;

    lib_handler = dlopen("so1.so", RTLD_LAZY);
    if(NULL == lib_handler)
    {
        fprintf(stderr, "There was a problem during call to dlopen: %s\n",
                dlerror());
        abort();
    }

    
    *(void **)&lib_func_handler = dlsym(lib_handler, run_func);
    lib_func_handler();

    dlclose(lib_handler);

    return 0;
}