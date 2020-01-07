//
// Created by student on 4/29/19.
//


#include <dlfcn.h>
#include <iostream>
#include "API.hpp"

//using namespace ilrd;

int main()
{

    void *foo_handler = dlopen("liblibfoo.so", RTLD_LAZY);
    if (!foo_handler)
    {
        return false;
    }

    API *table = static_cast<API *>(dlsym(foo_handler, "api_table"));

    table->api2();
    table->api1();

    return 0;
}