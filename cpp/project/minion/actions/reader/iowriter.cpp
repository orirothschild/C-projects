

#include <string.h>         /* memcpy */
#include <iostream>
#include <sstream>

#include "compressor_header.hpp"
#include "iowriter.hpp"     /* ioreader */
#include "slogger_header.hpp"/* logger */


namespace ilrd
{

IOWriter::IOWriter() noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "IOWriter: Ctor" << std::endl;
}

IOWriter::~IOWriter() noexcept
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "IOWriter: Dtor" << std::endl;
}

int IOWriter::Write(WriteRequestPacket *requestPacket, int blockIdx, char *memBlock) const
{
    Slogger::GetInstance().Log(Logger::DEBUG) << "IOWriter: Write" << std::endl;
    Slogger::GetInstance().Log(Logger::DEBUG) << "IOWriter: blockIdx: " << blockIdx << std::endl;

    std::stringstream strstream(requestPacket->m_compressedSize);
    size_t packSize = 0;

    strstream >> packSize;

    if (0 != packSize)
    {
        size_t destSize = 5000;
        char buffer[5000];

        Slogger::GetInstance().Log(Logger::DEBUG) << "IOWriter: Write: requestPack->m_data: " << std::endl;
        /* for (int i = 0; i < BLOCK_SIZE; ++i)
        {
            std::cout << buffer[i];
        }
        std::cout << std::endl; */

        int retval = ilrd::compressor::uncompress(buffer, &destSize,
                                                  requestPacket->m_data,
                                                  &packSize);

        Slogger::GetInstance().Log(Logger::DEBUG) << "IOWriter: Write: compressed size " << packSize << std::endl;
        Slogger::GetInstance().Log(Logger::DEBUG) << "IOWriter: Write: retval " << retval << std::endl;

        if (SUCCESS != retval)
        {
            return FAILURE;
        }
        
        memcpy(&memBlock[blockIdx * BLOCK_SIZE], buffer, BLOCK_SIZE);
        return SUCCESS;
    }
    
    memcpy(&memBlock[blockIdx * BLOCK_SIZE], &requestPacket->m_data, BLOCK_SIZE);
    return SUCCESS;
}

} // ilrd
