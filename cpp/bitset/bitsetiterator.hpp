#ifndef ILRD_BITSETITERATOR_HPP
#define ILRD_BITSETITERATOR_HPP

#include <iterator>


namespace ilrd
{
template<typename T>
class BitSetIterator : public std::iterator<std::random_access_iterator_tag,
                                        T,
                                        ptrdiff_t,
                                        T*,
                                        T&>
{
public:
    BitSetIterator(T * ptr = NULL) : m_ptr(ptr) {}
    //BitSetIterator(const BitSetIterator<T>& other) {}
    ~BitSetIterator() {}

    BitSetIterator<T>& operator++() {++m_ptr; return *this;}
    BitSetIterator<T>& operator--() {--m_ptr; return *this;}
    BitSetIterator<T>& operator+(size_t n) {m_ptr += n; return *this;}
    
    T&                 operator*()  {return *m_ptr;}
    T*                 operator->() {return m_ptr;}
    
    bool               operator==(const BitSetIterator& other)
                       {return *m_ptr == *other.m_ptr;}
    bool               operator!=(const BitSetIterator& other)
                       {return !(*m_ptr == *other.m_ptr);}
    
private:
    T *m_ptr;
};

} // end namespace

#endif //BITSETITERATOR
