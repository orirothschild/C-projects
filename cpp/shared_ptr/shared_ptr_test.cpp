#include <iostream>

#include "shared_ptr.hpp"
#include "./../utils.h"
using namespace ilrd;


int TESTCtorsAssignAndDereferencePASS();
int TESTCtorsAssignAndDereferenceFAIL();
int TESTCCtorAndArrowPASS();
int TESTCCtorAndArrowFAIL();
int TESTIntToConstInt();


int main()
{
    RUN_TEST(TESTCtorsAssignAndDereferencePASS());
    RUN_TEST(TESTCtorsAssignAndDereferenceFAIL());
    RUN_TEST(TESTCCtorAndArrowPASS());
    RUN_TEST(TESTCCtorAndArrowFAIL());
    RUN_TEST(TESTIntToConstInt());

    return 0;
}

int TESTCtorsAssignAndDereferencePASS()
{
    int *five = new int(5);
    SharedPtr<int> sp1;
    SharedPtr<int> sp2(five);

    sp1 = sp2;
    
    if (5 == *sp1 && 5 == *sp2)
    {
        return PASS;
    }

    return FAIL;
}

int TESTCtorsAssignAndDereferenceFAIL()
{
    int *five = new int(5);
    SharedPtr<int> sp1;
    SharedPtr<int> sp2(five);

    sp1 = sp2;

    if (*sp1 != *sp2)
    {
        return FAIL;
    }

    return PASS;
}

struct X
{
    int x;
};

int TESTCCtorAndArrowPASS()
{
    struct X *sPtr = new struct X;
    sPtr->x = 17;

    SharedPtr<struct X> sp1(sPtr);
    SharedPtr<struct X> sp2(sp1);

    if (17 == sp1->x && 17 == sp2->x)
    {
        return PASS;
    }

    return FAIL;
}

int TESTCCtorAndArrowFAIL()
{
    struct X *sPtr = new struct X;
    sPtr->x = 17;

    SharedPtr<struct X> sp1(sPtr);
    SharedPtr<struct X> sp2(sp1);

    if (sp1->x != sp2->x)
    {
        return FAIL;
    }

    return PASS;
}

int TESTSelfAssignment()
{
    struct X *sPtr = new struct X;
    sPtr->x = 17;

    SharedPtr<struct X> sp1(sPtr);
    SharedPtr<struct X> sp2(sp1);

    if (sp1->x != sp2->x)
    {
        return FAIL;
    }

    return PASS;
}

int TESTIntToConstInt()
{
    int *iPtr = new int(42);
    const int *ciPtr = new const int(5);
    SharedPtr<int> sp1(iPtr);
    SharedPtr<const int> sp2(ciPtr);
    SharedPtr<const int> sp3;

    sp3 = sp2 = sp1;

    if (42 == *sp2 && 42 == *sp1 && 42 == *sp3)
    {
        return PASS;
    }

    return FAIL;
}