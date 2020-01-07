#ifndef ILRD_UDPSERVER_H
#define ILRD_UDPSERVER_H



int RunUDPServer();
void UDPInitAddrinfo(struct addrinfo *hints);
int UDPGetSocketFD(struct sockaddr *send_to_addr);


#endif /* ILRD_UDPSERVER_H */