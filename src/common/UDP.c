#include "../../include/common/UDP.h"

int startUDPServer(WSADATA *wsa, SOCKET *serverSocketfd, struct sockaddr_in *serveraddr, int port, char* ip){
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code : %d\n", WSAGetLastError());
        return 1;
    }

    // Create UDP socket
    *serverSocketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*serverSocketfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address structure
    memset(serveraddr, 0, sizeof(*serveraddr));
    serveraddr->sin_family = AF_INET;
    serveraddr->sin_port = htons(port);
    inet_pton(AF_INET, ip, &serveraddr->sin_addr);

    // Bind socket
    if (bind(*serverSocketfd, (struct sockaddr *)serveraddr, sizeof(*serveraddr)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code : %d\n", WSAGetLastError());
        closesocket(*serverSocketfd);
        WSACleanup();
        return 1;
    }
    printf("Server is running...\n");
    return 0;
}

int startUDPClient(WSADATA *wsa, SOCKET *clientSocketfd, struct sockaddr_in *serveraddr, int port, char* ip){
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), wsa) != 0) {
        printf("WSAStartup failed. Error: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket (UDP)
    *clientSocketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*clientSocketfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address
    memset(serveraddr, 0, sizeof(*serveraddr));
    serveraddr->sin_family = AF_INET;
    serveraddr->sin_port = htons(port);
    inet_pton(AF_INET, ip, &serveraddr->sin_addr);

    return 0;
}


int connectUDP(SOCKET *clientSocketfd, struct sockaddr_in *serveraddr){
    if (connect(*clientSocketfd, (struct sockaddr*)serveraddr, sizeof(*serveraddr)) == -1) {
        printf("Connection failed. Error: %d\n", WSAGetLastError());
        closesocket(*clientSocketfd);
        WSACleanup();
        return 1;
    }
    return 0;
}

int sendUDPMessage(SOCKET *socketfd, struct sockaddr_in *addr,char* buffer, int bufferSize){
    if (sendto(*socketfd, buffer, bufferSize, 0, (struct sockaddr*)addr, sizeof(*addr)) == SOCKET_ERROR) {
        printf("Send failed. Error: %d\n", WSAGetLastError());
        closesocket(*socketfd);
        WSACleanup();
        return 1;
    }
    return 0;   
}
int receiveUDPMessage(SOCKET *socketfd, char* buffer, int bufferSize){

    if (recv(*socketfd, buffer, bufferSize, 0) == SOCKET_ERROR) {
        printf("Receive failed. Error: %d\n", WSAGetLastError());  return 1;
    }
    return 0;
}

int receiveUDPMessageWithAddr(SOCKET *socketfd, char* buffer, int bufferSize, struct sockaddr_in *addr, int* addrLen){
    // Receive datagram
    *addrLen = sizeof(*addr);
    int received = recvfrom(*socketfd, buffer, bufferSize, 0, (struct sockaddr*)addr, addrLen);
    if (received == SOCKET_ERROR) {
        printf("recvfrom() failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    return 0;
}