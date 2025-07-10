#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Link Winsock library

#define PORT 5000
#define MAXLINE 1000
#define IP "127.0.0.1"

int startClient(WSADATA*, SOCKET*, struct sockaddr_in*);
int connectToServer(SOCKET*, struct sockaddr_in*, const char*, char[]);

int main()
{
    WSADATA wsa;
    SOCKET clientSocketfd;
    struct sockaddr_in serveraddr;
    char buffer[MAXLINE];
    const char *message = "client connected; from client";

    if (startClient(&wsa, &clientSocketfd, &serveraddr) != 0) {
        return 1;
    }

    if (connectToServer(&clientSocketfd, &serveraddr, message, buffer) != 0) {
        return 1;
    }

    closesocket(clientSocketfd);
    WSACleanup();

    return 0;
}

int startClient(WSADATA *wsa, SOCKET *clientSocketfd, struct sockaddr_in *serveraddr)
{
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
    serveraddr->sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &serveraddr->sin_addr);

    return 0;
}

int connectToServer(SOCKET *clientSocketfd, struct sockaddr_in *serveraddr, const char *message, char buffer[MAXLINE])
{
    printf("Connecting...\n");

    if (connect(*clientSocketfd, (struct sockaddr*)serveraddr, sizeof(*serveraddr)) == -1) {
        printf("Connection failed. Error: %d\n", WSAGetLastError());
        closesocket(*clientSocketfd);
        WSACleanup();
        return 1;
    }

    printf("Connected. Sending message...\n");

    // Send message
    int sent = send(*clientSocketfd, message, (int)strlen(message), 0);
    if (sent == -1) {
        printf("Send failed. Error: %d\n", WSAGetLastError());
        closesocket(*clientSocketfd);
        WSACleanup();
        return 1;
    }

    // Receive response
    printf("Waiting for response...\n");
    int received = recv(*clientSocketfd, buffer, MAXLINE - 1, 0);
    if (received == -1) {
        printf("Receive failed. Error: %d\n", WSAGetLastError());
    } else {
        buffer[received] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    return 0;
}

