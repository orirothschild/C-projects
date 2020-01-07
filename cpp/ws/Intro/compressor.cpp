
#include "compressor.hpp"   /* compressor */

namespace ilrd
{

namespace compressor
{

int compress(char *dest, size_t *destLen, char *src, size_t *srcLen)
{
    uLong ucompSize = *srcLen;
    uLong compSize = compressBound(ucompSize);

    int retval = compress2(reinterpret_cast<Bytef *>(dest), &compSize,
                           reinterpret_cast<Bytef *>(src),
                           ucompSize, Z_BEST_COMPRESSION);

    *destLen = compSize;

    return retval;
}

int uncompress(char *dest, size_t *destLen, char *src, size_t *srcLen)
{
    int retval = uncompress2(reinterpret_cast<Bytef *>(dest),
                             reinterpret_cast<uLong *>(destLen),
                             reinterpret_cast<Bytef *>(src),
                             reinterpret_cast<uLong *>(srcLen));

    return retval;
}



} // compresor

} // ilrd
