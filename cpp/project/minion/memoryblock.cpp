#include "memoryblock.hpp"      /* memblock */
#include "slogger_header.hpp"    /* logger */

static size_t g_BLOCK_SIZE = 4096;
#define g_NUM_OF_BLOCKS (100)

namespace ilrd
{

MemoryBlock::MemoryBlock()
: m_memoryBlock(new char[g_NUM_OF_BLOCKS * g_BLOCK_SIZE])
, m_reads(0)
, m_writes(0)
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: Ctor" << std::endl;
}

MemoryBlock::~MemoryBlock()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: Dtor" << std::endl;

    delete[] m_memoryBlock;
}

char *MemoryBlock::GetMemoryBlock() const noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: GetMemoryBlock" << std::endl;

    return m_memoryBlock;
}

int MemoryBlock::GetReads() const noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: GetReads" << std::endl;

    return m_reads;
}

int MemoryBlock::GetWrites() const noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: GetWrites" << std::endl;

    return m_writes;
}

void MemoryBlock::IncrementReads()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: IncrementReads" << std::endl;

    ++m_reads;
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: Reads: " << m_reads << std::endl;
}

void MemoryBlock::IncrementWrites()
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: IncrementWrites" << std::endl;

    ++m_writes;
    Slogger::GetInstance().Log(Logger::DEBUG) << "MemoryBlock: Writes: " << m_writes << std::endl;
}


} // ilrd