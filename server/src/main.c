#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#define PORT 5000
#define MAXLINE 1000

int startServer(WSADATA*, SOCKET*, struct sockaddr_in*);
int communicateWithClient(SOCKET*, char[], const char*, struct sockaddr_in*);

int main()
{
    WSADATA wsa;
    SOCKET serverSocketfd;
    struct sockaddr_in serveraddr, clientaddr;
    int clientaddrLen;
    char buffer[MAXLINE];
    const char *message = "server connected; from server";

    //start server
    if(startServer(&wsa, &serverSocketfd, &serveraddr) != 0){
        return 1;
    };

    //communicate with client
    while(1){
        if(communicateWithClient(&serverSocketfd, buffer, message, &clientaddr)!=0) return 1; //stop if there are any errors
    };

    // Clean up
    closesocket(serverSocketfd);
    WSACleanup();
    return 0;
}

int startServer(WSADATA *wsa, SOCKET *serverSocketfd, struct sockaddr_in *serveraddr){
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
    serveraddr->sin_addr.s_addr = INADDR_ANY;
    serveraddr->sin_port = htons(PORT);

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

int communicateWithClient(SOCKET *serverSocketfd, char buffer[MAXLINE], const char *message, struct sockaddr_in *clientaddr){
    // Receive datagram
    int clientaddrLen = sizeof(*clientaddr);
    int n = recvfrom(*serverSocketfd, buffer, MAXLINE, 0, (struct sockaddr*)clientaddr, &clientaddrLen);
    if (n == SOCKET_ERROR) {
        printf("recvfrom() failed. Error Code : %d\n", WSAGetLastError());
    } else {
        buffer[n] = '\0';
        printf("Received from client: %s\n", buffer);

        // Send response
        sendto(*serverSocketfd, message, (int)strlen(message), 0,
               (struct sockaddr*)clientaddr, clientaddrLen);
    }
    return 0;
}
