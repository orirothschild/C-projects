//
// Created by student on 4/29/19.
//

#ifndef ILRD_SOLOADERAPI_HPP
#define ILRD_SOLOADERAPI_HPP

#include "actionator_header.hpp"

struct SoLoaderAPI
{
    char (*GetKey)();
    CreateObjectFunction (*GetCreatorFunc)();
};


#endif //HADAR_KLEIN_SOLOADERAPI_HPP
