#ifndef ILRD_PACKETS_HPP
#define ILRD_PACKETS_HPP

static const int UID_SIZE = 8;
static const int COMPRESSED_SIZE = 8;
static const int BLOCK_IDX_SIZE = 8;
static const int BLOCK_SIZE = 4096;
static const size_t ReadReturnPacketSizeParameters = sizeof(char) + UID_SIZE + sizeof(char) + COMPRESSED_SIZE;

namespace ilrd
{

struct ReadRequestPacket
{
    char m_type;
    char m_uid[UID_SIZE];
    char m_blockIdx[BLOCK_IDX_SIZE];
};

struct ReadReturnPacket
{
    char m_type;
    char m_uid[UID_SIZE];
    char m_status;
    char m_compressedSize[COMPRESSED_SIZE];
    char m_data[BLOCK_SIZE];
    char m_packetSize[COMPRESSED_SIZE];
};

struct WriteRequestPacket
{
    char m_type;
    char m_uid[UID_SIZE];
    char m_blockIdx[BLOCK_IDX_SIZE];
    char m_compressedSize[COMPRESSED_SIZE];
    char m_data[BLOCK_SIZE];
};

struct WriteReturnPacket
{
    char m_type;
    char m_uid[UID_SIZE];
    char m_status;
};

struct StatisticsRequestPacket
{
    char m_type;
    char m_request;
};

struct StatisticsReturnPacket
{
    /* char m_type;
    char m_request; */
    char m_data[20];
};

} // ilrd

#endif //ILRD_RETURNPACKET_HPP
