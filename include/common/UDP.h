#ifndef UDP_H
#define UDP_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

extern int startUDPServer(WSADATA *wsa, SOCKET *serverSocketfd, struct sockaddr_in *serveraddr, int port, char* ip);
extern int startUDPClient(WSADATA *wsa, SOCKET *clientSocketfd, struct sockaddr_in *serveraddr, int port, char* ip);
extern int connectUDP(SOCKET *clientSocketfd, struct sockaddr_in *serveraddr);
extern int sendUDPMessage(SOCKET *socketfd, struct sockaddr_in *addr,char* buffer, int bufferSize);
extern int receiveUDPMessage(SOCKET *socketfd, char* buffer, int bufferSize);
extern int receiveUDPMessageWithAddr(SOCKET *socketfd, char* buffer, int bufferSize, struct sockaddr_in *addr, int* addrLen);

#endif // UDP_H