

#include "bitset.hpp"       /* API */
#include "./../utils.hpp"   /* utils */

using namespace ilrd;

int TESTBitSet_Build1Long();
int TESTBitSet_Build3Longs();
int TESTBitSet_SetBitsAndCompare1LongTRUE();
int TESTBitSet_SetBitsAndCompare1LongFALSE();
int TESTBitSet_SetBitsAndCompare3LongTRUE();
int TESTBitSet_SetBitsAndCompare3LongFALSE();
int TESTBitSet_ShiftLeft1Long();
int TESTBitSet_ShiftLeft3Long();
int TESTBitSet_ShiftRight1Long();
int TESTBitSet_ShiftRight3Long();
int TESTBitSet_AND1LongTRUE();
int TESTBitSet_AND1LongFALSE();
int TESTBitSet_OR1LongTRUE();
/* int TESTBitSet_OR1LongFALSE();*/
int TESTBitSet_XOR1Long();
int TESTBitSet_AND3Long();
int TESTBitSet_OR3Long();
int TESTBitSet_XOR3Long();
int TESTBitSet_ANDEquals();
int TESTBitSet_OREqual();
int TESTBitSet_XOREqual();
int TESTBitSet_BitProxyAssignmentOperPASS();
int TESTBitSet_BitProxyAssignmentOperFAIL();
int TESTBitSet_BitProxyAssignmentOperTwoProxiesPASS();
int TESTBitSet_BitProxyAssignmentOperSelfProxiesPASS();
int TESTBitSet_TestIterator1Long();
int TESTBitSet_TestIterator3Long();
int TESTBitSet_TestIterator3LongFromSecondLong();
int TESTBitSet_TestBitIter1Long();


static unsigned long g_sum = 0;

int main()
{
    RUN_TEST(TESTBitSet_Build1Long());
    RUN_TEST(TESTBitSet_Build3Longs());
    RUN_TEST(TESTBitSet_SetBitsAndCompare1LongTRUE());
    RUN_TEST(TESTBitSet_SetBitsAndCompare1LongFALSE());
    RUN_TEST(TESTBitSet_SetBitsAndCompare3LongTRUE());
    RUN_TEST(TESTBitSet_SetBitsAndCompare3LongFALSE());
    RUN_TEST(TESTBitSet_ShiftLeft1Long());
    RUN_TEST(TESTBitSet_ShiftLeft3Long());
    RUN_TEST(TESTBitSet_ShiftRight1Long());
    RUN_TEST(TESTBitSet_ShiftRight3Long());
    RUN_TEST(TESTBitSet_AND1LongTRUE());
    RUN_TEST(TESTBitSet_AND1LongFALSE());
    RUN_TEST(TESTBitSet_OR1LongTRUE());
    RUN_TEST(TESTBitSet_XOR1Long());
    RUN_TEST(TESTBitSet_AND3Long());
    RUN_TEST(TESTBitSet_OR3Long());
    RUN_TEST(TESTBitSet_XOR3Long());
    RUN_TEST(TESTBitSet_ANDEquals());
    RUN_TEST(TESTBitSet_OREqual());
    RUN_TEST(TESTBitSet_XOREqual());
    RUN_TEST(TESTBitSet_BitProxyAssignmentOperPASS());
    RUN_TEST(TESTBitSet_BitProxyAssignmentOperFAIL());
    RUN_TEST(TESTBitSet_BitProxyAssignmentOperTwoProxiesPASS());
    RUN_TEST(TESTBitSet_BitProxyAssignmentOperSelfProxiesPASS());
    RUN_TEST(TESTBitSet_TestIterator1Long());
    RUN_TEST(TESTBitSet_TestIterator3Long());
    RUN_TEST(TESTBitSet_TestIterator3LongFromSecondLong());
    std::cout << std::endl;
    RUN_TEST(TESTBitSet_TestBitIter1Long());

    return 0;
}


int TESTBitSet_Build1Long()
{
    BitSet<10> s;

    s.setBit(3,1);

    if (1 == s.countSetBits() && 
       (1 == s[3] && 0 == s[2]))
    {
        return PASS;
    }

    return FAIL;
}

int TESTBitSet_Build3Longs()
{
    BitSet<140> s;

    s.setBit(138,1);
    s.setBit(5,1);

    if (2 == s.countSetBits())
    {
        return PASS;
    }

    return FAIL;
}

int TESTBitSet_SetBitsAndCompare1LongTRUE()
{
    BitSet<5> s;
    BitSet<5> t;

    s.setBit(2,1);
    s.setBit(1,1);

    t.setBit(2,1);
    t.setBit(1,1);

    if (s == t)
    {
        return PASS;
    }

    return FAIL;
}

int TESTBitSet_SetBitsAndCompare1LongFALSE()
{
    BitSet<5> s;
    BitSet<5> t;

    s.setBit(2,1);

    t.setBit(2,1);
    t.setBit(1,1);

    if (s != t)
    {
        return PASS;
    }

    return FAIL;
}


int TESTBitSet_SetBitsAndCompare3LongTRUE()
{
    BitSet<140> s;
    BitSet<140> t;

    s.setBit(2,1);
    s.setBit(100,1);

    t.setBit(2,1);
    t.setBit(100,1);

    if (s == t)
    {
        return PASS;
    }

    return FAIL;
}

int TESTBitSet_SetBitsAndCompare3LongFALSE()
{
    BitSet<140> s;
    BitSet<140> t;

    s.setBit(100,1);

    t.setBit(2,1);
    t.setBit(100,1);

    if (s != t) 
    {
        return PASS;
    }

    return FAIL;
}

int TESTBitSet_ShiftLeft1Long()
{
    BitSet<5> s;

    
    s.setBit(1,1);

    s = s << 2;

    if (1 == s[3])
    {
        if ((0 == s[2] && 0 == s[1]))
        {
            if (1 == s.countSetBits())
            {
                return PASS;
            }
        }
    }

    return FAIL;
}

int TESTBitSet_ShiftLeft3Long()
{
    BitSet<140> s;

    s.setBit(2, 1);

    s = s << 126;

    if (1 == s[128])
    {
        //if ((0 == s[126] && 0 == s[127] && 0 == s[128]))
        if (0 == s[126])
        {
            if (1 == s.countSetBits())
            {
                return PASS;
            }
        }
    }

    return FAIL;
}

int TESTBitSet_ShiftRight1Long()
{
    BitSet<5> s;

    s.setBit(3,1);

    s = s >> 2;

    if (1 == s[1])
    {
        if ((0 == s[3] && 0 == s[2]))
        {
            if (1 == s.countSetBits())
            {
                return PASS;
            }
        }
    }

    return FAIL;
}

int TESTBitSet_ShiftRight3Long()
{
    BitSet<140> s;

    s.setBit(129,1);

    s = s >> 65;

    if (1 == s[64])
    {
        if ((0 == s[129] && 0 == s[128] && 0 == s[127]))
        {
            if (1 == s.countSetBits())
            {
                return PASS;
            }
        }
    }

    return FAIL;
}

int TESTBitSet_AND1LongTRUE()
{
    BitSet<5> s;
    BitSet<5> t;

    s.setBit(1,1);
    t.setBit(1,1);

    s = s & t;

    if (1 == s.countSetBits())
    {
        if (1 == s[1])
        {
            return PASS;
        }
    }

    return FAIL;
}

int TESTBitSet_AND1LongFALSE()
{
    BitSet<5> s;
    BitSet<5> t;

    s.setBit(1,1);
    t.setBit(2,1);

    s = s & t;

    if (0 == s.countSetBits())
    {
        if (0 == s[1])
        {
            if (0 == s[2])
            {
                return PASS;
            }
        }
    }

    return FAIL;
}

int TESTBitSet_OR1LongTRUE()
{
    BitSet<5> s;
    BitSet<5> t;
    BitSet<5> st;

    st.setBit(1,1);
    st.setBit(2,1);

    s.setBit(1,1);
    t.setBit(2,1);

    s = s | t;

    if (2 == s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
}

/* int TESTBitSet_OR1LongFALSE()
{
    BitSet<5> s;
    BitSet<5> t;
    BitSet<5> st;

    st.setBit(1);
    st.setBit(2);

    s.setBit(1);
    t.setBit(2);

    s = s | t;

    if (2 != s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
} */

int TESTBitSet_XOR1Long()
{
    BitSet<5> s;
    BitSet<5> t;
    BitSet<5> st;

    st.setBit(1,1);
    st.setBit(2,1);

    s.setBit(1,1);
    t.setBit(2,1);

    s = s ^ t;

    if (2 == s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
}

int TESTBitSet_AND3Long()
{
    BitSet<140> s;
    BitSet<140> t;
    BitSet<140> st;

    st.setBit(75,1);

    s.setBit(75,1);
    t.setBit(75,1);
    t.setBit(135,1);

    s = s & t;

    if (1 == s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
}

int TESTBitSet_OR3Long()
{
    BitSet<140> s;
    BitSet<140> t;
    BitSet<140> st;

    st.setBit(75,1);
    st.setBit(135,1);

    s.setBit(75,1);
    t.setBit(135,1);

    s = s | t;

    if (2 == s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
}

int TESTBitSet_XOR3Long()
{
    BitSet<140> s;
    BitSet<140> t;
    BitSet<140> st;

    st.setBit(125,1);
    st.setBit(135,1);

    s.setBit(75,1);
    t.setBit(75,1);
    t.setBit(135,1);
    t.setBit(125,1);

    s = s ^ t;

    if (2 == s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
}

int TESTBitSet_ANDEquals()
{
    BitSet<140> s;
    BitSet<140> t;
    BitSet<140> st;

    st.setBit(75,1);

    s.setBit(75,1);
    t.setBit(75,1);
    t.setBit(135,1);

    s &= t;

    if (1 == s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
}

int TESTBitSet_OREqual()
{
    BitSet<140> s;
    BitSet<140> t;
    BitSet<140> st;

    st.setBit(75,1);
    st.setBit(135,1);

    s.setBit(75,1);
    t.setBit(135,1);

    s |= t;

    if (2 == s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
}

int TESTBitSet_XOREqual()
{
    BitSet<140> s;
    BitSet<140> t;
    BitSet<140> st;

    st.setBit(125,1);
    st.setBit(135,1);

    s.setBit(75,1);
    t.setBit(75,1);
    t.setBit(135,1);
    t.setBit(125,1);

    s ^= t;

    if (2 == s.countSetBits())
    {
        if (s == st)
        {
            return PASS;
        }
    }

    return FAIL;
}

int TESTBitSet_BitProxyAssignmentOperPASS()
{
    BitSet<10> s;
    BitSet<10> t;

    s.setBit(3,1);
    t.setBit(2,1);
    t.setBit(3,1);

    s[2] = 1;

    if (s == t)
    {
        return PASS;
    }

    return FAIL;
}

int TESTBitSet_BitProxyAssignmentOperFAIL()
{
    BitSet<10> s;
    BitSet<10> t;

    s.setBit(3,1);

    t.setBit(2,1);
    t.setBit(3,1);

    s[2] = 1;

    if (0 != s[2])
    {
        return PASS;
    }

    return FAIL;
}

int TESTBitSet_BitProxyAssignmentOperTwoProxiesPASS()
{
    BitSet<10> s;
    BitSet<10> t;

    s.setBit(3,1);

    t.setBit(2,1);
    t.setBit(3,1);

    s[2] = 1;

    if (t[2] == s[2])
    {
        return PASS;
    }

    return FAIL;
}

int TESTBitSet_BitProxyAssignmentOperSelfProxiesPASS()
{
    BitSet<10> s;
    BitSet<10> t;

    t[2] = 1;
    t[3] = 1;

    s[3] = 1;
    s[2] = s[3];
    s[2] = s[2];

    if (t[2] == s[2])
    {
        return PASS;
    }

    return FAIL;
}

void Sum(unsigned long l)
{
    g_sum += l;
}

int TESTBitSet_TestIterator1Long()
{
    BitSet<10> s;

    g_sum = 0;

    s[1] = 1;
    s[3] = 1;

    std::for_each(s.begin(), s.end(), Sum);


    if (2 == s.countSetBits() && 10 == g_sum)
    {
        return PASS;
    }

    return FAIL;
}


int TESTBitSet_TestIterator3Long()
{
    BitSet<140> s;

    g_sum = 0;

    s[1] = 1;
    s[3] = 1;

    s[65] = 1;
    s[67] = 1;

    s[129] = 1;
    s[131] = 1;


    std::for_each(s.begin(), s.end(), Sum);


    if (6 == s.countSetBits())
    {
        if (30 == g_sum)
        {
            return PASS;
        }
        
    }

    return FAIL;
}

int TESTBitSet_TestIterator3LongFromSecondLong()
{
    BitSet<140> s;

    g_sum = 0;

    s[1] = 1;
    s[3] = 1;

    s[65] = 1;
    s[67] = 1;

    s[129] = 1;
    s[131] = 1;


    std::for_each(s.begin() + 1, s.end(), Sum);


    if (6 == s.countSetBits())
    {
        if (20 == g_sum)
        {
            return PASS;
        }
        
    }

    return FAIL;
}

void Sum_Bits(bool i)
{
    g_sum += i;
}

int TESTBitSet_TestBitIter1Long()
{
    g_sum = 0;

    BitSet<5> s;
    BitSet<5>::BitSetIter bsi(s, 0);

    //s[1] = 1;
    //s[3] = 1;

    s.begin_iter()++;


    *(s.begin_iter() + 2) = 1;
    *(s.end_iter()  -  1) = 1;
    //*(bsi = 3 + s.begin_iter()) = 1;

    //*(s.begin_iter()) = 1;

    size_t blerg = std::count(s.begin_iter(), s.end_iter(), true);
    //std::cout << blerg << std::endl;

    std::for_each(s.begin_iter(), s.end_iter(), Sum_Bits);

    if (2 == g_sum && 2 == blerg)
    {
        return PASS;
    }

    return FAIL;
}
