#ifndef ILRD_FDPROXY_HPP
#define ILRD_FDPROXY_HPP


namespace ilrd
{

class FD
{
public:
    FD(const char *address, const char *port);
    ~FD();

    int GetFD() const;
    bool GetStatus() const;
    void CloseFD();

private:
    bool m_status;
    int m_fdproxy_fd;

    int InitFD(const char *address, const char *port);

    void UDPInitAddrinfo(struct addrinfo *hints);
    int UDPGetSocketFD(struct sockaddr *send_to_addr, const char *address,
                       const char *port);
};

} // ilrd


#endif // ILRD_FDPROXY_HPP