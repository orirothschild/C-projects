//
// Created by student on 4/29/19.
//

#include <iostream>
#include "libfoo.hpp"
#include "API.hpp"



void libfoo::foo1()
{
    std::cout << "foo1" << std::endl;
}

void libfoo::foo2()
{
    std::cout << "foo2" << std::endl;
}

API api_table = {libfoo::foo1, libfoo::foo2};
