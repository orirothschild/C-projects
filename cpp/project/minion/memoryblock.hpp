#ifndef ILRD_MEMORYBLOCK_HPP
#define ILRD_MEMORYBLOCK_HPP

#include "utils.hpp"

namespace ilrd
{

class MemoryBlock : private Uncopyable
{
public:
    MemoryBlock();
    ~MemoryBlock();

    char *GetMemoryBlock() const noexcept;
    int GetReads() const noexcept;
    int GetWrites() const noexcept;
    void IncrementReads();
    void IncrementWrites();
    
private:
    char *m_memoryBlock;
    int m_reads;
    int m_writes;
    
};

} // ilrd

#endif // ILRD_MEMORYBLOCK_HPP