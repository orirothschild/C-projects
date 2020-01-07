#include <cstring>
#include <iostream>

#include "string.hpp"

#include "./../utils.h"

namespace ilrd
{

String::String(const char *str)
: m_str(new char[std::strlen(str) + 1])
{
    std::strcpy(m_str, str);
}

String::String(const String& other_)
: m_str(new char[other_.Length() + 1])
{
    std::strcpy(m_str, other_.c_str());
}

String& String::operator=(const String& other_)
{
    size_t other_len = other_.Length();
    char *new_m_str = new char[other_len + 1];
    std::memcpy(new_m_str, other_.c_str(), other_len + 1);
    //strcpy(new_m_str, other_.c_str());
    
    delete[] m_str;
    m_str = new_m_str;

    return *this;
}

String::~String()
{
    delete[] m_str;
    m_str = nullptr;
}

const char * String::c_str() const
{
    return m_str;
}

size_t String::Length() const
{
    return std::strlen(m_str);
}

bool String::operator==(const String& other_) const
{
    return !std::strcmp(m_str, other_.c_str());
}

String& String::operator+=(const String& other_)
{
    size_t this_len = Length();
    size_t other_len = other_.Length();

    char *new_m_str = new char[this_len + other_len + 1];

    std::memcpy(new_m_str, m_str, this_len);
    std::memcpy(new_m_str + this_len, other_.c_str(), other_len);

    delete[] m_str;
    m_str = new_m_str;
    
    return *this;
}

char& String::operator[](size_t i)
{
    return m_str[i];
}

const char& String::operator[](size_t i) const
{
    return m_str[i];
}


} //end namespace
