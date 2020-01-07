#include <string.h>                 /* memcpy */
#include <iostream>

#include "compressor_header.hpp"    /* compressor */
#include "ioreader.hpp"             /* ioreader */
#include "slogger_header.hpp"       /* logger */


namespace ilrd
{

IOReader::IOReader() noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "IOReader: Ctor" << std::endl;
}

IOReader::~IOReader() noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "IOReader: Dtor" << std::endl;
}

void IOReader::Read(ReadReturnPacket *returnPacket, int blockIdx, char *memBlock) const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "IOReader: Read" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "IOReader: blockIdx: " << blockIdx << std::endl;

    size_t compSize = 0;
    size_t blockSize = BLOCK_SIZE;

    int retval = compressor::compress(returnPacket->m_data,
                                      &compSize, 
                                      &memBlock[blockIdx * BLOCK_SIZE],
                                      &blockSize);

    if (SUCCESS == retval)
    {
        Slogger::GetInstance().Log(Logger::DEBUG) << "IOReader: Read: data compressed" << returnPacket->m_data << std::endl;
        sprintf(returnPacket->m_packetSize, "%lu", compSize + ReadReturnPacketSizeParameters);
        sprintf(returnPacket->m_compressedSize, "%lu", compSize);
    }
    else
    {
        memcpy(&returnPacket->m_data, &memBlock[blockIdx * BLOCK_SIZE], BLOCK_SIZE);
        Slogger::GetInstance().Log(Logger::DEBUG) << "IOReader: Read: data uncompressed" << returnPacket->m_data << std::endl;
        sprintf(returnPacket->m_packetSize, "%lu", BLOCK_SIZE + ReadReturnPacketSizeParameters);
        sprintf(returnPacket->m_compressedSize, "%d", 0);
    }
}

} // ilrd
