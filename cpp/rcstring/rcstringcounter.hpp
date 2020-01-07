#ifndef ILRD_RCSTRINGCOUNTER_HPP
#define ILRD_RCSTRINGCOUNTER_HPP

#include <cstddef>  /* size_t */
#include <iostream> /* istream, ostream */


namespace ilrd
{

class RcString
{
private:
    class CharProxy;
    class StringWithCounter;
public:
    RcString(const char *str = "\0");
    RcString(const RcString& other_);
    ~RcString();

    RcString& operator=(const RcString& other);
    RcString& operator=(const char *str);
    RcString& operator+=(const RcString& other);
    
    friend std::ostream& operator<<(std::ostream& os, const RcString& str);
    friend std::istream& operator>>(std::istream& is, RcString& str);
    CharProxy operator[](size_t i);
    const char& operator[](size_t i) const;
    
    size_t Length() const;
    const char *c_str() const;

private:
    StringWithCounter *m_str;
    
    StringWithCounter *StringWithCtorHelper(const char* str);
    StringWithCounter *StringWithCCtorHelper(const RcString& other);

    void CleanUp();

    class CharProxy
    {
    public:
        CharProxy(RcString& str, size_t index);
        ~CharProxy();

        char operator=(const CharProxy& other);
        char operator=(char c);
        operator char() const;

    private:
        RcString& m_str;
        size_t m_index;
        //CharProxy(const CharProxy& other); //no implementation
    };

    class StringWithCounter
    {
    public:
        StringWithCounter(const char *str = "\0");
        ~StringWithCounter();

        void SetCounter(size_t i);
        size_t GetCounter() const;
        void Increase();
        void Decrease();
        void CleanUp();
        const char *GetStr() const;
        void SetStr(const char *str);

    private:
        size_t m_count;
        char m_str[1];
        StringWithCounter(const StringWithCounter* other); //no implementation
        StringWithCounter& operator=(const StringWithCounter& other); //no implementation
        
    };
};

bool operator==(const RcString& self, const RcString& other);
bool operator!=(const RcString& self, const RcString& other);
RcString operator+(const RcString& self, const RcString& other);
char *CreateNewStr(const RcString& self, const RcString& other);

} //end namespace

#endif //ILRD_STRING_HPP
