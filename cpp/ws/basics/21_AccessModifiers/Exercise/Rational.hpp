#ifndef ILRD_RATIONAL_H
#define ILRD_RATIONAL_H

#include <iostream>
#include <cstdio>

#include "./../../../../utils.h"

enum mathOperator
{
    Subtraction = -1,
    Multiplication,
    Addition
};

class Rational
{
private:
    static size_t s_RationalCntr;
public:
    explicit Rational();
    Rational(int wholeValue);
    explicit Rational(int fractionNumerator,
                  unsigned int fractionDenominator);
    Rational(const Rational& other_);
    ~Rational();
    operator int();
    operator float();    
    
    static size_t GetNumOfRationals();
    static const Rational ZERO;
    static const Rational HALF;
    static const Rational QUARTER;
    static const Rational ONE;

    void AddToSelf(int num);
    void SubtractFromSelf(int num);
    Rational& operator+(Rational& other_);
    Rational& operator-(Rational& other_);
    Rational& operator+(int num);
    Rational& operator-(int num);
    Rational& operator*(Rational& other_);
    bool operator==(Rational& other_) const;
    const Rational operator++(int );
    const Rational& operator++();
    const Rational operator--(int );
    const Rational& operator--();

    void Print();    
    bool IsEqual(int) const;
    void Inc(); //increment by 1.
    void Dec(); //decrement by 1.
    
    int GetWholeValue()const;
    int GetNumerator()const;
    unsigned int GetDenominator()const;
    void SetWholeValue(int wholeValue);
    void SetNumerator(int numerator);
    void SetDenominator(unsigned int denominator);

    friend std::ostream& operator<<(std::ostream& os_, const Rational& rational_);
    friend Rational operator+(int, Rational& rational_);
    friend Rational operator-(int, Rational& rational_);

private:
    int m_wholeValue;
    int m_fractionPartNumerator;
    unsigned int m_fractionPartDenominator;

    void RationalCalculeIMP(Rational& other_, enum mathOperator oper);
    void WholeNumAdditionSubtractionIMP(int wholeValue, enum mathOperator oper);
    void UpdateAndFractionParts();
};

//inline void operator+(Rational& rational);
//inline void operator-(Rational& rational);

inline void operator+(Rational& rational)
{
    rational.SetWholeValue(ABS(rational.GetWholeValue()));
    rational.SetNumerator(ABS(rational.GetNumerator()));
}

inline void operator-(Rational& rational)
{
    rational.SetWholeValue(-1 * rational.GetWholeValue());
    rational.SetNumerator(-1 * rational.GetNumerator());
}



#endif //RATIONAL_H



