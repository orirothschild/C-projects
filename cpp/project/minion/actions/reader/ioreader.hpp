#ifndef ILRD_IOREADER_HPP
#define ILRD_IOREADER_HPP

#include <unistd.h>     /* size_t */

#include "packets.hpp"  /* return packet */
#include "utils.hpp"    /* utils */

namespace ilrd
{

class IOReader
{
public:
    explicit IOReader() noexcept;
    ~IOReader() noexcept;

    void Read(ReadReturnPacket *returnPacket, int blockIdx, char *memBlock) const;

private:
    // nothing
};

} // ilrd

#endif // ILRD_IOREADER_HPP
