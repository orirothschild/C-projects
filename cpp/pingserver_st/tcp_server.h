#ifndef ILRD_TCPSERVER_H
#define ILRD_TCPSERVER_H




int RunTCPServer();
void TCPInitAddrinfo(struct addrinfo *hints);
int TCPGetSocketFD();
int Handshake(int sockfd);

#endif /* ILRD_TCPSERVER_H */