#include <cstddef>              /* size_t */
#include <cstring>              /* memcpy, strlen */
#include <iostream>             /* cout, cin */
#include <stdint.h>             /* INT64_MAX */

#include "rcstringcounter.hpp"  /* API */
#include "./../utils.h"         /* utils */


namespace ilrd
{

RcString::RcString(const char *str)
: m_str(StringWithCtorHelper(str))
{}

RcString::RcString(const RcString& other)
: m_str(StringWithCCtorHelper(other))
{}

RcString::~RcString()
{
    CleanUp();
}

RcString::StringWithCounter::StringWithCounter(const char *str)
: m_count(1)
{
    memcpy(m_str, str, strlen(str) + 1);
}

RcString::StringWithCounter *
RcString::StringWithCtorHelper(const char* str)
{
    char *buff = new char[strlen(str) + 1 + sizeof(StringWithCounter)];

    return new(buff)StringWithCounter(str);
}

RcString::StringWithCounter *
RcString::StringWithCCtorHelper(const RcString& other)
{
    other.m_str->Increase();
    
    return other.m_str;
}

void RcString::StringWithCounter::SetCounter(size_t i)
{
    m_count = i;
}

size_t RcString::StringWithCounter::GetCounter() const
{
    return m_count;
}

RcString::StringWithCounter::~StringWithCounter()
{}

const char *RcString::StringWithCounter::GetStr() const
{
    return m_str;
}

void RcString::StringWithCounter::SetStr(const char *str)
{
    memcpy(m_str, str, strlen(str) + 1);
}

char *CreateNewStr(const RcString& self, const RcString& other)
{
    size_t thisLen = self.Length();
    size_t otherLen = other.Length();
    size_t combinedLen = otherLen + thisLen;

    char *new_str = new char[combinedLen + 1];

    memcpy(new_str, self.c_str(), thisLen);
    memcpy(new_str + thisLen, other.c_str(), otherLen + 1);

    return new_str;
}

RcString& RcString::operator+=(const RcString& other)
{
    char *new_str = CreateNewStr(*this, other);

    CleanUp();

    m_str = StringWithCtorHelper(new_str);

    delete[] new_str;

    return *this;
}

RcString operator+(const RcString& self, const RcString& other)
{
    RcString newStr(self.c_str());
    newStr += other;

    return newStr;
}

RcString& RcString::operator=(const RcString& other)
{
    other.m_str->Increase();

    CleanUp();

    m_str = other.m_str;

    return *this;
}

void RcString::CleanUp()
{
    m_str->Decrease();
    
    if(0 == m_str->GetCounter())
    {
        m_str->~StringWithCounter();
        delete[] reinterpret_cast<char *>(m_str);
        m_str = nullptr;
    }
}

void RcString::StringWithCounter::Increase()
{
    ++m_count;
}

void RcString::StringWithCounter::Decrease()
{
    --m_count;
}

RcString::CharProxy::CharProxy(RcString& str, size_t index)
: m_str(str), m_index(index)
{}

RcString::CharProxy::~CharProxy()
{}

RcString::CharProxy::operator char() const
{
    return m_str.c_str()[m_index];
}

char RcString::CharProxy::operator=(const CharProxy& other)
{   
    char c = other.operator char();
    m_str[m_index] = c;

    return m_str[m_index];
}

char RcString::CharProxy::operator=(char c)
{
    if(m_str.c_str()[m_index] != c)
    {
        size_t len = m_str.Length() + 1;
        char *temp = new char[len];

        memcpy(temp, m_str.c_str(), len);
        temp[m_index] = c;

        m_str.CleanUp();
        m_str.m_str = m_str.StringWithCtorHelper(temp);

        delete[] temp;
    }

    return m_str[m_index];
}

RcString::CharProxy RcString::operator[](size_t i)
{
    CharProxy cp(*this, i);
    return cp;
}

const char& RcString::operator[](size_t i) const
{
    return m_str->GetStr()[i];
}

size_t RcString::Length() const
{
    return strlen(m_str->GetStr());
}

const char *RcString::c_str() const
{
    return m_str->GetStr();
}

bool operator==(const RcString& self, const RcString& other)
{
    return !strcmp(self.c_str(), other.c_str());
}

bool operator!=(const RcString& self, const RcString& other)
{
    return !(self == other);
}

std::ostream& operator<<(std::ostream& os, const RcString& str)
{
    return os << str.c_str();
}

std::istream& operator>>(std::istream& is, RcString& str)
{
    char *newStr = new char[100];
    is >> newStr;

    std::cin.clear();
    std::cin.ignore(INT64_MAX,'\n');

    str.CleanUp();
    str.m_str = str.StringWithCtorHelper(newStr);
    
    delete[] newStr;

    return is;
}


} //end namespace
