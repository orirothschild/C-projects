#ifndef ILRD_RCSTRING_HPP
#define ILRD_RCSTRING_HPP

#include <cstddef>  /* size_t */


namespace ilrd
{

class RcString
{
private:
    class CharProxy;
public:
    RcString(const char *str = "\0");
    RcString(const RcString& other_);
    ~RcString();

    RcString& operator=(const RcString& other);
    RcString& operator=(const char *str);
    RcString& operator+=(const RcString& other);
    
    friend std::ostream& operator<<(std::ostream& os, const RcString& str);
    friend std::istream& operator>>(std::istream& os, RcString& str);
    CharProxy operator[](size_t i);
    const char& operator[](size_t i) const;
    
    size_t Length() const;
    const char *c_str() const;

private:
    char *m_str;
    
    void SetMStr(char *str);
    char *CtorHelper(const char *str);
    char *CCtorHelper(char *str);
    void CleanUp();
    void IncMetaData(char *str);
    void DecMetaData(char *str);
    void SetMetaData(size_t new_val);
    size_t GetMetaData() const;

    class CharProxy
    {
    public:
        CharProxy(RcString& str, size_t index);
        ~CharProxy();
        char operator=(char c);
        operator char();

    private:
        RcString& m_str;
        size_t m_index;
    };
};

bool operator==(const RcString& self, const RcString& other);
bool operator!=(const RcString& self, const RcString& other);
RcString operator+(const RcString& self, const RcString& other);
char *CreateNewStr(const RcString& self, const RcString& other);

} //end namespace

#endif //ILRD_STRING_HPP
