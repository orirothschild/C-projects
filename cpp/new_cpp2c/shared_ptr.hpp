#ifndef ILRD_SHAREDPTR_HPP
#define ILRD_SHAREDPTR_HPP

#include <cstddef>  /* size_t */
namespace ilrd
{
template<typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T *ptr = NULL);
    SharedPtr(const SharedPtr& ptr);
    ~SharedPtr();
    
    template<typename U>
    friend class SharedPtr;
    template<typename U>
    SharedPtr(const SharedPtr<U>& ptr);
    
    SharedPtr operator=(const SharedPtr& other);

    T* operator->() const;
    T& operator*() const;

private:
    T *m_ptr;
    size_t *m_counter;
    void CleanUp();
};


template<typename T>
void SharedPtr<T>::CleanUp()
{
    if(0 == --*m_counter)
    {
        delete m_ptr;
        delete m_counter;
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(T *ptr)
: m_ptr(ptr)
, m_counter(new size_t(1))
{}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other)
: m_ptr(other.m_ptr)
, m_counter(other.m_counter)
{
    ++*m_counter;
}

template<typename T>
template<typename U>
SharedPtr<T>::SharedPtr(const SharedPtr<U>& other)
: m_ptr(other.m_ptr)
, m_counter(other.m_counter)
{
    ++*m_counter;
}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
    CleanUp();
}

template<typename T>
SharedPtr<T> SharedPtr<T>::operator=(const SharedPtr& other)
{
    ++*other.m_counter;

    CleanUp();

    m_ptr = other.m_ptr;
    m_counter = other.m_counter;

    return *this;
}

template<typename T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

template<typename T>
T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

} //namespace
#endif // ILRD_SHAREDPTR_HPP
