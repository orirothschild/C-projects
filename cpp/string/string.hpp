#ifndef ILRD_STRING_HPP
#define ILRD_STRING_HPP

#include <cstddef>

namespace ilrd
{

class String
{
public:
    String(const char *str = ""); //not explicit on purpose
    String(const String& other_); //CCtor
    ~String();

    String& operator=(const String& other_);
    String& operator+=(const String& other_);
    bool operator==(const String& other_) const;
    char& operator[](size_t i);
    const char& operator[](size_t i) const;

    size_t Length() const;
    const char *c_str() const;

private:
    char *m_str;
};


} //end namespace

#endif //ILRD_STRING_HPP