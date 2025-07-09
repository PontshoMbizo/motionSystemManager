#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Link Winsock library

#define PORT 5000
#define MAXLINE 1000
#define LOCAL "127.0.0.1"

int main()
{
    WSADATA wsa;
    SOCKET clientSocketfd;
    struct sockaddr_in serveraddr;
    char buffer[MAXLINE];
    const char *message = "client connected; from client";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    clientSocketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocketfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    inet_pton(AF_INET, LOCAL, &serveraddr.sin_addr);

    printf("Connecting...\n");
    if (connect(clientSocketfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        printf("Connection failed. Error: %d\n", WSAGetLastError());
        closesocket(clientSocketfd);
        WSACleanup();
        return 1;
    }

    printf("Connected. Sending message...\n");

    // Send message
    int sent = send(clientSocketfd, message, (int)strlen(message), 0);
    if (sent == SOCKET_ERROR) {
        printf("Send failed. Error: %d\n", WSAGetLastError());
        closesocket(clientSocketfd);
        WSACleanup();
        return 1;
    }

    // Receive response
    printf("Waiting for response...\n");
    int received = recv(clientSocketfd, buffer, MAXLINE, 0);
    if (received == SOCKET_ERROR) {
        printf("Receive failed. Error: %d\n", WSAGetLastError());
    } else {
        buffer[received] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    // Clean up
    closesocket(clientSocketfd);
    WSACleanup();

    return 0;
}
