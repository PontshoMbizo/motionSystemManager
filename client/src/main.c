#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "../../include/motion_system_messages.h" //message structure def in here...

#pragma comment(lib, "ws2_32.lib")

#define PORT 5000
#define MAXLINE 1000
#define IP "127.0.0.1"

int startClient(WSADATA*, SOCKET*, struct sockaddr_in*);
int connectToServer(SOCKET*, struct sockaddr_in*, MessageToMotionSystem, MessageFromMotionSystem);
int userInput(MessageToMotionSystem*);
void printMessageFromMotionSystem(MessageFromMotionSystem*); //will write...

int main()
{
    WSADATA wsa;
    SOCKET clientSocketfd;
    struct sockaddr_in serveraddr;
    MessageFromMotionSystem messageFromMotionSystem;
    MessageToMotionSystem message;

    if (startClient(&wsa, &clientSocketfd, &serveraddr) != 0) return 1;

// can send a kill session message via useInput, remember to implement that... 👍🏾
    while(1){
        userInput(&message);
        if (connectToServer(&clientSocketfd, &serveraddr, message, messageFromMotionSystem) != 0) return 1; //stop if there are any errors
    };

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

int connectToServer(SOCKET *clientSocketfd, struct sockaddr_in *serveraddr,MessageToMotionSystem message, MessageFromMotionSystem messageFromMotionSystem)
{
    printf("Connecting...\n");

    //connect to be on its own thread...
    if (connect(*clientSocketfd, (struct sockaddr*)serveraddr, sizeof(*serveraddr)) == -1) {
        printf("Connection failed. Error: %d\n", WSAGetLastError());
        closesocket(*clientSocketfd);
        WSACleanup();
        return 1;
    }

    
    //send messages on its own thread...
    // send the message struct as a byte messageFromMotionSystem
    int sent = send(*clientSocketfd, (char*) &message, (int)sizeof(message), 0);
    if (sent == -1) {
        printf("Send failed. Error: %d\n", WSAGetLastError());
        closesocket(*clientSocketfd);
        WSACleanup();
        return 1;
    }

    //read messages on its own thread...

    // Receive response
    printf("Waiting for response...\n");
    int received = recv(*clientSocketfd, (char*)&messageFromMotionSystem, sizeof(messageFromMotionSystem), 0);
    if (received == -1) {
        printf("Receive failed. Error: %d\n", WSAGetLastError());
    } else {
        printf("Received from server: %s\n", messageFromMotionSystem);
    }

    return 0;
}

int userInput(MessageToMotionSystem *message){
        printf("set control_state: ");
        scanf("%d", &(message->data.control_state));
        printf("set x: ");
        scanf("%d", &(message->data.x));
        printf("set x_lim1: ");
        scanf("%d", &(message->data.x_lim1));
        printf("set x_lim2: ");
        scanf("%d", &(message->data.x_lim2));
        printf("set x_cycle_time: ");
        scanf("%d", &(message->data.x_cycle_time));
        printf("set y: ");
        scanf("%d", &(message->data.y));
        printf("set y_lim1: ");
        scanf("%d", &(message->data.y_lim1));
        printf("set y_lim2: ");
        scanf("%d", &(message->data.y_lim2));
        printf("set y_cycle_time: ");
        scanf("%d", &(message->data.y_cycle_time));
        printf("set life_counter: ");
        scanf("%d", &(message->data.life_counter));
        printf("end of current input...");
}