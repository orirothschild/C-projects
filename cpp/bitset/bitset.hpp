#ifndef ILRD_BITSET_HPP
#define ILRD_BITSET_HPP

#include <cstring>      /* memset */
#include <cstddef>      /* size_t */
#include <climits>      /* CHAR_BIT */
#include <iostream>     /* debug */
#include <algorithm>    /* for_each */
#include <cassert>      /* assert */

#include "bitsetiterator.hpp"   /* bitset iterator class */


static const unsigned long ULONG_BITS = sizeof(unsigned long) * CHAR_BIT;
static const unsigned long ULONG_BYTES = sizeof(unsigned long);

namespace ilrd
{
unsigned long countSetBitsInLong(unsigned long i);
unsigned long ShiftLeft(unsigned long i);
unsigned long ShiftRight(unsigned long i);
unsigned long BinaryAND(unsigned long l1, unsigned long l2);
unsigned long BinaryXOR(unsigned long l1, unsigned long l2);
unsigned long BinaryOR(unsigned long l1, unsigned long l2);


size_t g_counter = 0;

template <size_t SIZE>
class BitSet
{
private:
    class BitProxy;
    
public:
    class BitSetIter;
    /* not explicit */BitSet();
    /* for debug */BitSet(size_t index);
    
    void setBit(size_t idx, bool b);
    bool getBit(size_t idx) const;
    unsigned long countSetBits();
    
    bool operator==(const BitSet& other);
    bool operator!=(const BitSet& other);
    BitSet operator&(const BitSet& other) const;
    BitSet operator|(const BitSet& other) const;
    BitSet operator^(const BitSet& other) const;
    BitSet& operator&=(const BitSet& other);
    BitSet& operator|=(const BitSet& other);
    BitSet& operator^=(const BitSet& other);
    
    BitSet operator<<(size_t i);
    BitSet operator>>(size_t i);

    void printBitSet() const;

    bool operator[](size_t idx) const;
    BitProxy operator[](size_t idx);

    typedef BitSetIterator<unsigned long> iterator;
    iterator begin() {return iterator(&m_arr[0]);}
    iterator end()   {return iterator(&m_arr[ARR_SIZE]);}

    typedef BitSetIter iter;
    iter begin_iter() {return iter(*this, 0);}
    iter end_iter()   {return iter(*this, SIZE);}


    class BitSetIter
    {
    public:
        typedef unsigned long iterator_category; 
        typedef size_t value_type;
        typedef long difference_type;
        typedef unsigned long pointer;
        typedef unsigned long reference;

        explicit BitSetIter(BitSet& bs, size_t index)
        : m_bp(bs, index)
        {}

        BitSetIter(const BitSetIter& other) :m_bp(other.m_bp) {}
        ~BitSetIter() {}

        BitProxy  operator*()  {return m_bp.GetRef()[m_bp.GetIndex()];}
        
        BitSetIter& operator++() {m_bp.IncIndex(); return *this;}
        BitSetIter operator++(int) {BitSetIter temp(*this); m_bp.IncIndex();
                                    return temp;}
        
        BitSetIter& operator--() {m_bp.DecIndex(); return *this;}
        BitSetIter operator--(int) {BitSetIter temp(*this); m_bp.DecIndex();
                                    return temp;}
        
        BitSetIter& operator+(size_t i) {m_bp.IncIndex(i); return *this;}
        BitSetIter& operator-(size_t i) {m_bp.DecIndex(i); return *this;}
        
        bool operator!=(const BitSetIter& other) 
        {return m_bp != other.m_bp || m_bp.GetIndex() != other.m_bp.GetIndex();}

    private:
        BitProxy m_bp;
        BitProxy& BitSetIterCtorHelper(BitSet<SIZE>& bs, size_t index);
    };

private:
    static const size_t ARR_SIZE = (((SIZE - 1)/ ULONG_BITS) + 1);
    unsigned long m_arr[ARR_SIZE];
    void SetGetHelper(size_t idx, size_t *arr_idx, unsigned long *mask) const;
    
    class BitProxy
    {
    public:
        BitProxy(BitSet& bs, size_t idx);
        ~BitProxy() {}

        bool operator==(const BitProxy& other) {return m_ref == other.m_ref;}
        bool operator!=(const BitProxy& other) {return m_ref != other.m_ref;}
        bool operator=(const BitProxy& other);
        bool operator=(bool b);
        operator bool() const;
        
        void IncIndex(size_t i = 1) {m_index += i;}
        void DecIndex(size_t i = 1) {m_index -= i;}

        size_t GetIndex() const {return m_index;}
        BitSet& GetRef() const {return m_ref;}

    private:
        BitSet& m_ref;
        size_t m_index;
    };

    class Sum
    {
    public:
        Sum() : m_sum(0) {}
        void operator() (unsigned long l) {m_sum += countSetBitsInLong(l);}
        unsigned long m_sum;
    private:

    };

    class BitShift
    {
    public:
        BitShift(unsigned long shift_length = 0, unsigned long direction = 0)
        : m_mask(0)
        , m_direction(direction)
        , m_shift_length(shift_length)
        , m_adjusted_shift_length(ULONG_BITS - shift_length)
        {}
        unsigned long operator()(unsigned long l);
    private:
        unsigned long m_mask;
        unsigned long m_direction;
        unsigned long m_shift_length;
        unsigned long m_adjusted_shift_length;
        
        unsigned long leftShift(unsigned long l);
        unsigned long rightShift(unsigned long l);
    };

    
};


template<size_t SIZE>
typename BitSet<SIZE>::BitSetIter& operator+(int i,
                                    typename BitSet<SIZE>::BitSetIter& bsIter)
{
    return bsIter + i;
}


template<size_t SIZE>
unsigned long BitSet<SIZE>::BitShift::leftShift(unsigned long l)
{
    unsigned long retLong = 0;

    retLong = l << m_shift_length;

    retLong |= (m_mask >> m_adjusted_shift_length);

    m_mask = l;

    return retLong;
}

template<size_t SIZE>
unsigned long BitSet<SIZE>::BitShift::rightShift(unsigned long l)
{
    unsigned long retLong = 0;

    retLong = l >> m_shift_length;
    
    retLong |= (m_mask << m_adjusted_shift_length);

    m_mask = l;

    return retLong;
}

template<size_t SIZE>
BitSet<SIZE>::BitSet()
: m_arr()
{
    std::fill(m_arr, &m_arr[ARR_SIZE], 0);
}

template<size_t SIZE>
BitSet<SIZE>::BitSet(size_t index)
{
    memset(&m_arr, 0, ARR_SIZE * sizeof(unsigned long));

    setBit(index);
}

template<size_t SIZE>
void BitSet<SIZE>::printBitSet() const
{
    for (size_t i = 0; i < ARR_SIZE; ++i)
    {
        std::cout << m_arr[i] << std::endl;
    }
}

template<size_t SIZE>
unsigned long BitSet<SIZE>::countSetBits()
{
    Sum s = std::for_each(m_arr, &m_arr[ARR_SIZE], Sum());
    
    return s.m_sum;
}


template<size_t SIZE>
void BitSet<SIZE>::SetGetHelper(size_t idx, size_t *arr_idx, unsigned long *mask) const
{
    *arr_idx = idx / ULONG_BITS;
    *arr_idx = ARR_SIZE - 1 - *arr_idx;
    
    *mask <<= idx % ULONG_BITS;
}

template<size_t SIZE>
bool BitSet<SIZE>::getBit(size_t idx) const
{
    assert(SIZE > idx);

    size_t arr_idx;
    unsigned long mask = 1ul;

    SetGetHelper(idx, &arr_idx, &mask);

    return m_arr[arr_idx] & mask;
}

template<size_t SIZE>
void BitSet<SIZE>::setBit(size_t idx, bool b)
{
    assert(SIZE > idx);

    size_t arr_idx;
    unsigned long mask = 1ul;

    SetGetHelper(idx, &arr_idx, &mask);

    if (b == false)
    {
        m_arr[arr_idx] &= ~mask;
    }
    m_arr[arr_idx] |= mask;
}

template<size_t SIZE>
bool BitSet<SIZE>::operator==(const BitSet& other)
{
    return !memcmp(m_arr, other.m_arr, ARR_SIZE * sizeof(unsigned long));
}

template<size_t SIZE>
bool BitSet<SIZE>::operator!=(const BitSet& other)
{
    return !(*this == other);
}

template<size_t SIZE>
BitSet<SIZE> BitSet<SIZE>::operator&(const BitSet& other) const
{
    BitSet<SIZE> ret_set;

    std::transform(m_arr, &m_arr[ARR_SIZE], other.m_arr, ret_set.m_arr,
                   BinaryAND);

    return ret_set;
}

template<size_t SIZE>
BitSet<SIZE> BitSet<SIZE>::operator|(const BitSet& other) const
{
    BitSet<SIZE> ret_set;

    std::transform(m_arr, &m_arr[ARR_SIZE], other.m_arr, ret_set.m_arr,
                   BinaryOR);

    return ret_set;
}

template<size_t SIZE>
BitSet<SIZE> BitSet<SIZE>::operator^(const BitSet& other) const
{
    BitSet<SIZE> ret_set;

    std::transform(m_arr, &m_arr[ARR_SIZE], other.m_arr, ret_set.m_arr,
                   BinaryXOR);

    return ret_set;
}


template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator&=(const BitSet& other)
{
    std::transform(m_arr, &m_arr[ARR_SIZE], other.m_arr, m_arr,
                   BinaryAND);

    return *this;
}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator|=(const BitSet& other)
{
    std::transform(m_arr, &m_arr[ARR_SIZE], other.m_arr, m_arr,
                   BinaryOR);

    return *this;
}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator^=(const BitSet& other)
{
    std::transform(m_arr, &m_arr[ARR_SIZE], other.m_arr, m_arr,
                   BinaryXOR);

    return *this;
}

template<size_t SIZE>
bool BitSet<SIZE>::operator[](size_t idx) const
{
    return getBit(idx);
}

template<size_t SIZE>
BitSet<SIZE>::BitProxy::operator bool() const
{
    return m_ref.getBit(m_index);
}

template<size_t SIZE>
BitSet<SIZE> BitSet<SIZE>::operator<<(size_t num)
{
    BitSet<SIZE> retSet;
    BitShift bsm(num, 0);
    
    size_t numToShift = (num / ULONG_BITS);
    
    std::transform(std::reverse_iterator<unsigned long *>(&m_arr[ARR_SIZE]),
                   std::reverse_iterator<unsigned long *>(&m_arr[numToShift]),
                   std::reverse_iterator<unsigned long *>(&retSet.m_arr[ARR_SIZE - numToShift]),
                   BitShift(num % ULONG_BITS, 0));

    return retSet;
}

template<size_t SIZE>
BitSet<SIZE> BitSet<SIZE>::operator>>(size_t num)
{
    BitSet<SIZE> retSet;
    BitShift bsm(num, 1);

    size_t numToShift = (num / ULONG_BITS);

    std::transform(&m_arr[0], &m_arr[ARR_SIZE - numToShift],
                   &retSet.m_arr[numToShift], BitShift(num % ULONG_BITS, 1));

    return retSet;
}





template<size_t SIZE>
unsigned long BitSet<SIZE>::BitShift::operator()(unsigned long l)
{
    if (0 == m_direction)
    {
        return leftShift(l);
    }
    
    return rightShift(l);
}

template<size_t SIZE>
typename BitSet<SIZE>::BitProxy BitSet<SIZE>::operator[](size_t idx)
{
    BitProxy bp(*this, idx);
    return bp;
}

template<size_t SIZE>
BitSet<SIZE>::BitProxy::BitProxy(BitSet<SIZE>& bs, size_t idx)
: m_ref(bs), m_index(idx)
{}

template<size_t SIZE>
bool BitSet<SIZE>::BitProxy::operator=(bool b)
{
    m_ref.setBit(m_index, b);

    return m_ref.getBit(m_index);
}

template<size_t SIZE>
bool BitSet<SIZE>::BitProxy::operator=(const BitProxy& other)
{
    m_ref.setBit(m_index, other.m_ref.getBit(other.m_index));

    return m_ref.getBit(m_index);
}



unsigned long countSetBitsInLong(unsigned long i)
{
    i = i - ((i >> 1) & 0x5555555555555555);
    i = (i & 0x3333333333333333) + ((i >> 2) & 0x3333333333333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F0F0F0F0F) * 0x0101010101010101) >> 56;
}

unsigned long ShiftLeft(unsigned long i)
{
    i <<= 1;

    return i;
}

unsigned long ShiftRight(unsigned long i)
{
    i >>= 1;

    return i;
}

unsigned long BinaryXOR(unsigned long l1, unsigned long l2)
{
    return l1 ^ l2;
}
unsigned long BinaryOR(unsigned long l1, unsigned long l2)
{
    return l1 | l2;
}
unsigned long BinaryAND(unsigned long l1, unsigned long l2)
{
    return l1 & l2;
}

} //namespace ilrd


#endif //BITSET

