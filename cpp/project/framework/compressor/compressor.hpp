#ifndef ILRD_COMPRESSOR_HPP
#define ILRD_COMPRESSOR_HPP

#include "zlib.h"           /* compress */

namespace ilrd
{

namespace compressor
{

int compress(char *dest, size_t *destLen, char *src, size_t *srcLen);
int uncompress(char *dest, size_t *destLen, char *src, size_t *srcLen);

} // compresor

} // ilrd


#endif // ILRD_COMPRESSOR_HPP