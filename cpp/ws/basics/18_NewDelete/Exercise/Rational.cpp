#include <iostream>
#include <cstdio>
#include <cassert>
#include <cmath>

#include "Rational.hpp"
#include "./../../../../utils.h"

size_t Rational::s_RationalCntr = -4;

const Rational Rational::ZERO(0);
const Rational Rational::HALF(1, 2);
const Rational Rational::QUARTER(1, 4);
const Rational Rational::ONE(1);

size_t Rational::GetNumOfRationals()
{
    return s_RationalCntr;
}

unsigned int CalcNumerator(int numerator1, unsigned int denominator1,
                       int numerator2, unsigned int denominator2,
                       enum mathOperator oper)
{
    int numer1 = numerator1 * (int)denominator2;
    int numer2 = numerator2 * (int)denominator1;

    if (Addition == oper)
    {
        return numer1 + numer2;
    }

    return numer1 - numer2;
}

unsigned int CalcNumerator(int num, unsigned int denominator, enum mathOperator oper)
{
    return oper * num * denominator;
}

Rational::Rational()
: m_wholeValue(0)
, m_fractionPartNumerator(0)
, m_fractionPartDenominator(1)
{
    ++s_RationalCntr;
}

Rational::Rational(int wholeValue)
: m_wholeValue(wholeValue)
, m_fractionPartNumerator(0)
, m_fractionPartDenominator(1)
{
    ++s_RationalCntr;
}

Rational::Rational(int fractionNumerator,
                   unsigned int fractionDenominator) 
: m_wholeValue(fractionNumerator / (int)fractionDenominator)
, m_fractionPartNumerator(fractionNumerator % (int)fractionDenominator)
, m_fractionPartDenominator(fractionDenominator)
{
    assert(0 != fractionDenominator);
    ++s_RationalCntr;
}

Rational::Rational(const Rational& other_)
: m_wholeValue(other_.m_wholeValue)
, m_fractionPartNumerator(other_.m_fractionPartNumerator)
, m_fractionPartDenominator(other_.m_fractionPartDenominator)
{
    ++s_RationalCntr;
}

Rational::~Rational()
{
    --s_RationalCntr;
}

int GCD(int numerator, unsigned int denominator)
{
    int gcd = 1;
    for (int i = 1; i <= numerator && (unsigned int)i <= denominator; ++i)
    {
        if ((0 == numerator % i) && (0 == denominator % i))
        {
            gcd = i;
        }
    }

    return gcd;
}

void Rational::UpdateAndFractionParts()
{
    int negative_flag(1);
    if (0 > m_fractionPartNumerator)
    {
        negative_flag = -1;
    }
    
    m_fractionPartNumerator %= m_fractionPartDenominator;
    m_fractionPartNumerator *= negative_flag;

    int gcd = GCD(m_fractionPartNumerator, m_fractionPartDenominator);
    m_fractionPartNumerator /= gcd;
    m_fractionPartDenominator /= gcd;
}

void Rational::WholeNumAdditionSubtractionIMP(int num, enum mathOperator oper)
{
    m_fractionPartNumerator += m_wholeValue * m_fractionPartDenominator;
    m_fractionPartNumerator += CalcNumerator(num,
                                             m_fractionPartDenominator,
                                             oper);
    m_wholeValue = m_fractionPartNumerator / (int)m_fractionPartDenominator;

    UpdateAndFractionParts();
}

void Rational::AddToSelf(int num)
{
    WholeNumAdditionSubtractionIMP(num, Addition);
}

Rational& Rational::operator+(int num)
{
    WholeNumAdditionSubtractionIMP(num, Addition);

    return *this;
}

void Rational::SubtractFromSelf(int num)
{
    WholeNumAdditionSubtractionIMP(num, Subtraction);
}

Rational& Rational::operator-(int num)
{
    WholeNumAdditionSubtractionIMP(num, Subtraction);

    return *this;
}

void Rational::RationalCalculeIMP(Rational& other_,
                                 enum mathOperator oper)
{
    m_fractionPartNumerator += m_wholeValue * m_fractionPartDenominator;
    other_.m_fractionPartNumerator += other_.m_wholeValue * 
                                      other_.m_fractionPartDenominator;

    if (Multiplication == oper)
    {
        m_fractionPartNumerator *= other_.m_fractionPartNumerator; 
    }
    else
    {
        m_fractionPartNumerator = CalcNumerator(m_fractionPartNumerator,
                                            m_fractionPartDenominator,
                                            other_.m_fractionPartNumerator,
                                            other_.m_fractionPartDenominator,
                                            oper);
    }
    
    m_fractionPartDenominator *= other_.m_fractionPartDenominator;
    m_wholeValue = m_fractionPartNumerator / (int)m_fractionPartDenominator;

    UpdateAndFractionParts();
}

Rational& Rational::operator+(Rational& other_)
{
    RationalCalculeIMP(other_, Addition);

    return *this;
}

Rational& Rational::operator-(Rational& other_)
{
    RationalCalculeIMP(other_, Subtraction);

    return *this;
}

void Rational::Print()
{
    m_wholeValue += m_fractionPartNumerator / (int)m_fractionPartDenominator;
    UpdateAndFractionParts();

    printf("%d %d/%u\n", m_wholeValue, m_fractionPartNumerator,
                         m_fractionPartDenominator);
}

bool Rational::operator==(Rational& other_) const
{
    return (m_wholeValue == other_.m_wholeValue &&
            m_fractionPartNumerator == other_.m_fractionPartNumerator &&
            m_fractionPartDenominator == other_.m_fractionPartDenominator);
}


bool Rational::IsEqual(int num) const
{
    return (m_wholeValue == num && 0 == m_fractionPartNumerator);
}

const Rational Rational::operator++(int ) //increment by 1.
{
    Rational temp(*this);

    ++m_wholeValue;
    
    return temp;
}

const Rational& Rational::operator++() //increment by 1.
{
    ++m_wholeValue;

    return *this;
}

const Rational Rational::operator--(int ) //increment by 1.
{
    Rational temp(*this);

    --m_wholeValue;
    
    return temp;
}

const Rational& Rational::operator--() //increment by 1.
{
    --m_wholeValue;

    return *this;
}

Rational& Rational::operator*(Rational& other_)
{
    RationalCalculeIMP(other_, Multiplication);

    return *this;
}

void Rational::Dec() //decrement by 1.
{
    SubtractFromSelf(1);
}

int Rational::GetWholeValue() const
{
    return m_wholeValue;
}

int Rational::GetNumerator() const
{
    return m_fractionPartNumerator;
}

unsigned int Rational::GetDenominator() const
{
    return m_fractionPartDenominator;
}

void Rational::SetWholeValue(int wholeValue)
{
    m_wholeValue = wholeValue;
}

void Rational::SetNumerator(int numerator)
{
    m_fractionPartNumerator = numerator;
}

void Rational::SetDenominator(unsigned int denominator)
{
    assert(0 != denominator);

    m_fractionPartDenominator = denominator;
}

std::ostream& operator<<(std::ostream& os_, const Rational& rational_)
{
    return os_ << rational_.GetWholeValue() << " " << rational_.GetNumerator()\
           << "/" << rational_.GetDenominator() << std::endl;
}

Rational::operator int()
{
    return m_wholeValue;
}

Rational::operator float()
{
    return static_cast<float>(m_wholeValue) +
          (static_cast<float>(m_fractionPartNumerator) /
           static_cast<float>(m_fractionPartDenominator));
}

Rational operator+(int num, Rational& rational_)
{
    rational_ + num;
    return rational_;
}
Rational operator-(int num, Rational& rational_)
{
    rational_ + -num;
    -rational_;
    return rational_;
}