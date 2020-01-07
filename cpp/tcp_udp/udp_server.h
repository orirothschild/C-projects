#ifndef ILRD_UDPSERVER_H
#define ILRD_UDPSERVER_H

const char *g_UDP_PORT = "8080";
const int g_UDP_BACKLOG = 20;
const char *g_UDP_ADDRESS = NULL;
#define g_MAX_DATA_SIZE (100)

int RunUDPServer();
void InitAddrinfo(struct addrinfo *hints);


#endif /* ILRD_UDPSERVER_H */