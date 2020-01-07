#ifndef ILRD_TCPSERVER_H
#define ILRD_TCPSERVER_H

const char *g_TCP_PORT = "8080";
const int g_TCP_BACKLOG = 20;
const char *g_TCP_ADDRESS = NULL;
#define g_MAX_DATA_SIZE (100)

int RunTCPServer();
void InitAddrinfo(struct addrinfo *hints);
int GetSocketFD();
int Handshake(int sockfd);

#endif /* ILRD_TCPSERVER_H */