#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "a.h"

typedef void (*lib_func)();

int main()
{
    void *lib_handler = NULL;
    lib_func lib_func_handler = NULL;
    foo();
    bar1();
    
    lib_handler = dlopen("libso2.so" ,RTLD_LAZY);
    if (NULL == lib_handler)
    {
        fprintf(stderr, "There was an error during dlopen(): %s\n", dlerror());
        exit(1);
    }

    lib_func_handler = dlsym(lib_handler, "bar2");

    (*lib_func_handler)();

    dlclose(lib_handler);

    return 0;
}