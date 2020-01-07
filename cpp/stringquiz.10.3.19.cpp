#include <iostream>
#include <cstring>

class String
{
public:
    String(char *const str);
    String(const String& str = '\0');

    const char *c_str() const;
    friend std::ostream& operator<<(std::ostream& os_, const String& str);
    char *CtorHelper(const char *str);

private:
    //String(const String& str = '\0');
    char *m_str;
    String& operator=(const String& other);
};


char *String::CtorHelper(const char * str)
{
    size_t len = std::strlen(str) + 1;
    char *new_str = new char[len];
    memcpy(new_str, str, len);

    std::cout << "ctorhelper" << std::endl;
    return new_str;
}

String::String(char *const str)
: m_str(CtorHelper(str))
{
    std::cout << "ctor" << std::endl;
}

String::String(const String& str)
: m_str(CtorHelper(str.c_str()))
{
    std::cout << "cctor" << std::endl;
}

const char *String::c_str() const
{
    std::cout << "c_str" << std::endl;
    return m_str;
}

std::ostream& operator<<(std::ostream& os_, String& str)
{
    std::cout << "fwend" << std::endl;
    return os_ << str.c_str();
}


int main()
{
    String str = "Hello";
    std::cout << str.c_str() << std::endl;

    return 0;
}