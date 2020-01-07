#ifndef ILRD_IOWRITER_HPP
#define ILRD_IOWRITER_HPP

#include <unistd.h>     /* size_t */

#include "packets.hpp"  /* return packet */
#include "utils.hpp"    /* utils */

namespace ilrd
{

class IOWriter
{
public:
    explicit IOWriter() noexcept;
    ~IOWriter() noexcept;

    int Write(WriteRequestPacket *returnPacket, int blockIdx, char *memBlock) const;

private:
    // nothing
};

} // ilrd

#endif // ILRD_IOWRITER_HPP
