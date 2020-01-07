#include <cstring>
#include <iostream>
#include <cmath>

#include "rcstringcounter.hpp"
#include "./../utils.h"

using namespace ilrd;

int TESTBuildString();
int TESTBuildStringCCtor();
int TESTBuildStringStrLen();
int TESTBuildStringAssignOper();
int TESTBuildStringSelfAssignOper();
int TESTBuildStringPlusEqual();
int TESTBuildStringPlusEqualSelf();
int TESTBuildStringEqualsEquals();
int TESTBuildStringReturnCharAt2();
int TESTPlusOperator();
int TESTCoutOper();
int TESTCinOper();


int main()
{
    RUN_TEST(TESTBuildString());
    RUN_TEST(TESTBuildStringCCtor());
    RUN_TEST(TESTBuildStringStrLen());
    RUN_TEST(TESTBuildStringAssignOper());
    RUN_TEST(TESTBuildStringSelfAssignOper());
    RUN_TEST(TESTBuildStringEqualsEquals());
    RUN_TEST(TESTBuildStringPlusEqual());
    RUN_TEST(TESTBuildStringPlusEqualSelf());
    RUN_TEST(TESTBuildStringReturnCharAt2());
    RUN_TEST(TESTPlusOperator());
    RUN_TEST(TESTCoutOper());
    RUN_TEST(TESTCinOper());

    return 0;
}



int TESTBuildString()
{
    RcString str("hello");

    //std::cout << str.c_str() << std::endl;

    if (!std::strcmp("hello", str.c_str()))
    {
        return PASS;
    }

    return FAIL;
}


int TESTBuildStringCCtor()
{
    RcString str1("hello");

    RcString str2(str1);

    if (!std::strcmp(str1.c_str(), str2.c_str()))
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringAssignOper()
{
    RcString str1("hello");
    RcString str2;
    RcString str3("hi");

    str2 = str1 = str3;

    //str1 = str1;

    if (!std::strcmp(str3.c_str(), str2.c_str()))
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringSelfAssignOper()
{
    RcString str1("hello");
    
    str1 = str1;

    if (!std::strcmp(str1.c_str(), str1.c_str()))
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringEqualsEquals()
{
    RcString str1("hello");
    RcString str2;

    str2 = str1;

    if (str1 == str2)
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringPlusEqual()
{
    RcString str1("hello");
    RcString str2(" there");

    str1 += str2;

    if (!std::strcmp("hello there", str1.c_str()))
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringPlusEqualSelf()
{
    RcString str1("hello");

    str1 += str1;

    if (!std::strcmp("hellohello", str1.c_str()))
    {
        return PASS;
    }

    return FAIL;
}


int TESTBuildStringStrLen()
{
    RcString str("hello");

    if (5 == str.Length())
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildStringReturnCharAt2()
{
    RcString str1("hello");
    RcString str2("there");

    str1[2] = 't';
    str1[1] = str2[1];

    std::cout << str1[2] << std::endl;

    if (str1[2] == 't' && !std::strcmp("hhtlo", str1.c_str()))
    {
        return PASS;
    }

    return FAIL;
}


int TESTPlusOperator()
{
    RcString str1("hello");
    RcString str2(" there");
    RcString str3;

    str3 = str1 + str2;

    if (!std::strcmp("hello there", str3.c_str()))
    {
        return PASS;
    }

    return FAIL;
}


int TESTCoutOper()
{
    RcString str1("hello");

    std::cout << str1 << std::endl;

    return PASS;
}


int TESTCinOper()
{
    RcString str1("Hello");
    std::cout << "please enter a word" << std::endl;
    
    std::cin >> str1;
    std::cout << str1 << std::endl;
    std::cout << "again" << std::endl;
    
    std::cin >> str1;
    std::cout << str1 << std::endl;

    if (!std::strcmp("hi", str1.c_str()))
    {
        return PASS;
    }

    return FAIL;
}
