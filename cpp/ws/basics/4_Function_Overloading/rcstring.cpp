#include <cstddef>          /* size_t */
#include <cstring>          /* memcpy, strlen */
#include <iostream>         /* cout, cin */

#include "rcstring.hpp"     /* API */
#include "./../utils.hpp"   /* utils */


namespace ilrd
{

RcString::RcString(const char *str)
: m_str(CtorHelper(str))
{}

RcString::RcString(const RcString& other_)
: m_str(CCtorHelper(other_.m_str))
{}

RcString::~RcString()
{
    CleanUp();
}

RcString::CharProxy::CharProxy(RcString& str, size_t index)
: m_str(str), m_index(index)
{}

RcString::CharProxy::~CharProxy()
{}

RcString::CharProxy::operator char()
{
    return m_str.c_str()[m_index];
}

char RcString::CharProxy::operator=(char c)
{
    if(m_str.c_str()[m_index] != c)
    {
        char *temp = m_str.CtorHelper(m_str.c_str());
        m_str.CleanUp();

        temp[m_index] = c;
        m_str.SetMStr(temp);
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
    return m_str[i];
}

size_t RcString::Length() const
{
    return strlen(m_str);
}

const char *RcString::c_str() const
{
    return m_str;
}

void RcString::SetMStr(char *str)
{
    m_str = str;
}

char *RcString::CtorHelper(const char *str)
{
    size_t len = strlen(str) + 1;
    char *new_str = new char[len + sizeof(size_t)];
    *(size_t *)new_str = 1;
    new_str = (char *)((size_t *)new_str + 1);

    memcpy(new_str, str, len);

    return new_str;
}

char *RcString::CCtorHelper(char *str)
{
    IncMetaData(str);
    return str;
}

char *CreateNewStr(const RcString& self, const RcString& other)
{
    size_t thisLen = self.Length();
    size_t otherLen = other.Length();
    size_t combinedLen = otherLen + thisLen;

    char *new_str = new char[combinedLen + sizeof(size_t) + 1];
    *(size_t*)new_str = 1;
    new_str = (char *)((size_t *)new_str + 1);

    memcpy(new_str, self.c_str(), thisLen);
    memcpy(new_str + thisLen, other.c_str(), otherLen + 1);

    return new_str;
}

RcString& RcString::operator+=(const RcString& other)
{
    char *new_str = CreateNewStr(*this, other);

    CleanUp();

    SetMStr(new_str);

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
    IncMetaData(other.m_str);

    CleanUp();

    m_str = other.m_str;
    SetMetaData(other.GetMetaData());

    return *this;
}

void RcString::CleanUp()
{
    DecMetaData(m_str);
    
    if (0 == (*((size_t *)m_str - 1)))
    {
        m_str = (char *)((size_t *)m_str - 1);
        delete[] m_str;
        m_str = nullptr;
    }
}

void RcString::IncMetaData(char *str)
{
    str = (char *)((size_t *)str - 1);
    ++*(size_t *)str;
    str = (char *)((size_t *)str + 1);
}

void RcString::DecMetaData(char *str)
{
    str = (char *)((size_t *)str - 1);
    --*(size_t *)str;
    str = (char *)((size_t *)str + 1);
}

void RcString::SetMetaData(size_t new_val)
{
    m_str = (char *)((size_t *)m_str - 1);
    *(size_t *)m_str = new_val;
    m_str = (char *)((size_t *)m_str + 1);
}

size_t RcString::GetMetaData() const
{
    return *((size_t *)m_str - 1);
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
    *(size_t*)newStr = 1;
    newStr = (char *)((size_t *)newStr + 1);

    str.CleanUp();

    is >> newStr;


    str.m_str = newStr;

    //newStr = (char *)((size_t *)newStr - 1); //need to ask alex
    //delete[] newStr;                                  //need to ask alex

    return is;
}



} //end namespace
