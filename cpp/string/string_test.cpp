#include <cstring>
#include <iostream>

#include "string.hpp"

#include "./../utils.h"

using namespace ilrd;


int TESTBuildString();
int TESTBuildStringCCtor();
int TESTBuildStringStrLen();
int TESTBuildStringAssignOper();
int TESTBuildStringPlusEqual();
int TESTBuildStringEqualsEquals();
int TESTBuildStringReturnCharAt2();


int main()
{
    RUN_TEST(TESTBuildString());
    RUN_TEST(TESTBuildStringCCtor());
    RUN_TEST(TESTBuildStringStrLen());
    RUN_TEST(TESTBuildStringAssignOper());
    RUN_TEST(TESTBuildStringEqualsEquals());
    RUN_TEST(TESTBuildStringPlusEqual());
    RUN_TEST(TESTBuildStringReturnCharAt2());

    return 0;
}



int TESTBuildString()
{
    String str("hello");

    //std::cout << str.c_str() << std::endl;

    if (!std::strcmp("hello", str.c_str()))
    {
        return PASS;
    }

    return FAIL;
}


int TESTBuildStringCCtor()
{
    String str1("hello");

    String str2(str1);

    if (!std::strcmp(str1.c_str(), str2.c_str()))
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringAssignOper()
{
    String str1("hello");
    String str2;
    String str3("hi");

    str2 = str1 = str3;

    if (!std::strcmp(str3.c_str(), str2.c_str()))
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringEqualsEquals()
{
    String str1("hello");
    String str2;

    str2 = str1;

    if (str1 == str2)
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringPlusEqual()
{
    String str1("hello");
    String str2(" there");

    str1 += str1;
    //str1 += str2;

    //if (!std::strcmp("hello there", str1.c_str()))
    if (!std::strcmp("hellohello", str1.c_str()))
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringStrLen()
{
    String str("hello");

    if (5 == str.Length())
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringReturnCharAt2()
{
    String str1("hello");

    str1[2] = 't';

    if (str1[2] == 't')
    {
        return PASS;
    }

    return FAIL;
}