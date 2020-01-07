#include <iostream>
#include <cstdio>
#include <cassert>

#include "Rational.hpp"
#include "./../../../../utils.h"

int TESTBuildOneRational();
int TESTBuildIncrementTwice();
int TESTBuildAddSubRational();
int TESTBuildAddSubNum();
int TESTIsEqualRational();
int TESTIsEqualNum();
int TESTAssignmentOper();
int TESTCopyCtor();
int TESTUnaryOperators();
int TESTMultiply();
int TESTSwitchOperators();
int TESTOperPlus();
int TESTOperMinus();
int TESTCheckStatics();


int main()
{
    RUN_TEST(TESTBuildOneRational());
    RUN_TEST(TESTBuildIncrementTwice());
    RUN_TEST(TESTBuildAddSubRational());
    RUN_TEST(TESTBuildAddSubNum());
    RUN_TEST(TESTIsEqualRational());
    RUN_TEST(TESTIsEqualNum());
    RUN_TEST(TESTAssignmentOper());
    RUN_TEST(TESTCopyCtor());
    RUN_TEST(TESTUnaryOperators());
    RUN_TEST(TESTMultiply());
    RUN_TEST(TESTSwitchOperators());
    RUN_TEST(TESTOperPlus());
    RUN_TEST(TESTOperMinus());
    RUN_TEST(TESTCheckStatics());

    return 0;
}

int TESTBuildOneRational()
{
    Rational rational;
    
    /* rational.Print(); */

    if (1 == rational.GetDenominator() &&
        0 == rational.GetWholeValue() &&
        0 == rational.GetNumerator())
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildIncrementTwice()
{
    Rational rational;

    ++rational;
    ++rational;
    --rational;
    
    /* rational.Print(); */

    if (1 == rational.GetDenominator() &&
        1 == rational.GetWholeValue() &&
        0 == rational.GetNumerator())
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildAddSubRational()
{
    Rational rational1(3,2);

    Rational rational2;

    rational2.SetWholeValue(2);
    rational2.SetNumerator(4);
    rational2.SetDenominator(5);
    //rational2.Print();

    rational1 + rational2;
    //rational1.Print();

    Rational rational3;

    rational3.SetWholeValue(1);
    rational3.SetNumerator(2);
    rational3.SetDenominator(5);
    //rational3.Print(); 

    rational1-rational3;
    //rational1.Print();
    /* rational2.Print();  */

    if (2 == rational1.GetWholeValue() &&
        9 == rational1.GetNumerator() &&
        10 == rational1.GetDenominator())
    {
        return PASS;
    }

    return FAIL;
}

int TESTBuildAddSubNum()
{
    Rational rational1;

    rational1.SetWholeValue(1);
    rational1.SetNumerator(1);
    rational1.SetDenominator(2);

    rational1.AddToSelf(-2);

    /* rational1.Print(); */
    rational1.SubtractFromSelf(1);
    /* rational1.Print(); */
    

    if (-1 == rational1.GetWholeValue() &&
        -1 == rational1.GetNumerator() &&
        2 == rational1.GetDenominator())
    {
        return PASS;
    }

    return FAIL;
}

int TESTIsEqualRational()
{
    Rational rational1;

    rational1.SetWholeValue(1);
    rational1.SetNumerator(1);
    rational1.SetDenominator(2);

    Rational rational2;

    rational2.SetWholeValue(1);
    rational2.SetNumerator(1);
    rational2.SetDenominator(2);

    if (rational1==rational2)
    {
        return PASS;
    }

    return FAIL;
}

int TESTIsEqualNum()
{
    Rational rational1;

    rational1.SetWholeValue(1);
    rational1.SetNumerator(0);
    rational1.SetDenominator(2);

    if (rational1.IsEqual(1))
    {
        return PASS;
    }

    return FAIL;
}

int TESTAssignmentOper()
{
    Rational rational1(3);

    Rational rational2;

    rational2 = rational1;

    if (rational1==rational2)
    {
        return PASS;
    }

    return FAIL;
}

int TESTCopyCtor()
{
    Rational rational1(3);

    Rational rational2(rational1);
    
    if (rational1==rational2)
    {
        return PASS;
    }

    return FAIL;
}

int TESTUnaryOperators()
{
    Rational rational1(3);

    -(rational1);
    
    Rational rational2;
    rational2.SetWholeValue(-3);
    rational2.SetNumerator(0);
    rational2.SetDenominator(1);

    if (rational1==rational2)
    {
        return PASS;
    }

    return FAIL;
}

int TESTMultiply()
{   
    Rational rational1;
    
    rational1.SetWholeValue(1);
    rational1.SetNumerator(2);
    rational1.SetDenominator(3);

    //std::cout << rational1 << std::endl;

    Rational rational2;

    rational2.SetWholeValue(2);
    rational2.SetNumerator(1);
    rational2.SetDenominator(3);

    rational1*rational2;

    Rational rational3;

    rational3.SetWholeValue(3);
    rational3.SetNumerator(8);
    rational3.SetDenominator(9);

    if (rational1==rational3)
    {
        return PASS;
    }

    return FAIL;
}

int TESTIntOperator(int rational)
{   
    UNUSED(rational);
    return 1;
}

int TESTFloatOperator(float rational)
{   
    UNUSED(rational);
    return 1;
}

int TESTImplicitIntToRational(Rational rational)
{
    UNUSED(rational);
    return 1;
}

int TESTSwitchOperators()
{
    int retval = 0;
    Rational rational1;

    rational1.SetWholeValue(1);
    rational1.SetNumerator(2);
    rational1.SetDenominator(3);

    retval += TESTImplicitIntToRational(3);
    retval += TESTIntOperator(rational1);
    retval += TESTFloatOperator(rational1);

    if (3 == retval)
    {
        return PASS;
    }

    return FAIL;
}

int TESTOperPlus()
{
    Rational r1(1,2), r2(3);
    r1 + r2;
    r1 + 3;
    3 + r1;

    Rational r3;

    r3.SetWholeValue(9); 
    r3.SetNumerator(1);
    r3.SetDenominator(2);

    if (r1 == r3)
    {
        return PASS;    
    }

    return FAIL;
}

int TESTOperMinus()
{
    Rational r1(1,2), r2(3);
    r1 - r2;
    r1 - 3;
    3 - r1;
    
    Rational r3;

    r3.SetWholeValue(8); 
    r3.SetNumerator(1);
    r3.SetDenominator(2);

    if (r1 == r3)
    {
        return PASS;
    }

    return FAIL;
}

int TESTCheckStatics()
{
    Rational r1(1,2);
    Rational r2(3);
    Rational r3(r2);
    Rational r4(6,4);

    r1.~Rational();

    if (true)
    {
        Rational r5(1);
    }
    
    if (3 == Rational::GetNumOfRationals())
    {
        return PASS;
    }

    return FAIL;
}
