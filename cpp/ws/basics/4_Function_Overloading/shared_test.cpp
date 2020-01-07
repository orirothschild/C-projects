#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

extern "C"
{
    #include "ws_3_c.h"
}
    
typedef void (*lib_func_t)(void);

int main()
{
    
    void *lib_handler = NULL;
    lib_func_t lib_func_handler = NULL;

    Foo();
    
    lib_handler = dlopen("ws_3.so", RTLD_LAZY);
    if(NULL == lib_handler)
    {
        fprintf(stderr, "There was a problem during call to dlopen: %s\n",
                dlerror());
        abort();
    }
    
    lib_func_handler = (lib_func_t)dlsym(lib_handler, "Foo");
    
    lib_func_handler();
    
    dlclose(lib_handler);
    
    return 0;
}