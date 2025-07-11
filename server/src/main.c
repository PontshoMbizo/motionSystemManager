#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <winsock2.h>
#include <ws2tcpip.h>

#include "../../include/motion_system_messages.h" //message structure def in here...

#pragma comment(lib, "ws2_32.lib")
#define PORT 5000
#define MAXLINE 1000

int startServer(WSADATA*, SOCKET*, struct sockaddr_in*);
int communicateWithClient(SOCKET*, MessageToMotionSystem, MessageFromMotionSystem, struct sockaddr_in*);
int updateMotionSystemState(MessageFromMotionSystem*, MessageToMotionSystem*); // uses the data from the client to update its state
int initializeMotionSystem(MessageToMotionSystem*); // just initialize to its default values in start up (will check actual initial values later...)
void printMessageFromClient(MessageToMotionSystem*);


int main()
{
    WSADATA wsa;
    SOCKET serverSocketfd;
    struct sockaddr_in serveraddr, clientaddr;
    int clientaddrLen;
    MessageToMotionSystem messageFromClient;
    MessageFromMotionSystem messageFromMotionSystem;

    //start server
    if(startServer(&wsa, &serverSocketfd, &serveraddr) != 0){
        return 1;
    };


    //initialize client input
    initializeMotionSystem(&messageFromClient);
    //communicate with client
    while(1){
        if(communicateWithClient(&serverSocketfd, messageFromClient, messageFromMotionSystem, &clientaddr)!=0) return 1; //stop if there are any errors
        updateMotionSystemState(&messageFromMotionSystem, &messageFromClient); //catch invalid input error later (if no connection happens)...
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

int communicateWithClient(SOCKET *serverSocketfd, MessageToMotionSystem messageFromClient, MessageFromMotionSystem messageFromMotionSystem, struct sockaddr_in *clientaddr){
    // Receive datagram
    int clientaddrLen = sizeof(*clientaddr);
    int n = recvfrom(*serverSocketfd, (char *)&messageFromClient, sizeof(messageFromClient), 0, (struct sockaddr*)clientaddr, &clientaddrLen);
    if (n == SOCKET_ERROR) {
        printf("recvfrom() failed. Error Code : %d\n", WSAGetLastError());
    } else {
        printf("Received from client: ");
        printMessageFromClient(&messageFromClient);

        // Send response
        sendto(*serverSocketfd, (char *)&messageFromMotionSystem, (int)sizeof(messageFromMotionSystem), 0,
               (struct sockaddr*)clientaddr, clientaddrLen);
    }
    return 0;
}

int initializeMotionSystem(MessageToMotionSystem *messageFromClient){ //message from client needs to be at initial state
    messageFromClient->data.control_state=0;
    messageFromClient->data.life_counter=0;
    messageFromClient->data.x=0;
    messageFromClient->data.x_cycle_time=0;
    messageFromClient->data.x_lim1=0;
    messageFromClient->data.x_lim2=0;
    messageFromClient->data.y=0;
    messageFromClient->data.y_cycle_time=0;
    messageFromClient->data.y_lim1=0;
    messageFromClient->data.y_lim2=0;

    return 0;
}

int updateMotionSystemState(MessageFromMotionSystem *messageFromMotionSystem, MessageToMotionSystem *messageTomMotionSystem){
    //initialize
    messageFromMotionSystem->data.error_indram_x1=0;
    messageFromMotionSystem->data.error_indram_x2=0;
    messageFromMotionSystem->data.error_indram_y1=0;
    messageFromMotionSystem->data.error_indram_y2=0;
    messageFromMotionSystem->data.error_interlock=0;
    messageFromMotionSystem->data.error_msg1=0;
    messageFromMotionSystem->data.error_msg2=0;
    messageFromMotionSystem->data.life_counter=0;
    messageFromMotionSystem->data.motion_control=0;
    messageFromMotionSystem->data.motion_status=0;
    messageFromMotionSystem->data.spare=0;
    messageFromMotionSystem->data.washout_x=0;
    messageFromMotionSystem->data.washout_y=0;
    messageFromMotionSystem->data.x=0;
    messageFromMotionSystem->data.x_ddot=0;
    messageFromMotionSystem->data.x_dot=0;
    messageFromMotionSystem->data.y=0;
    messageFromMotionSystem->data.y_ddot=0;
    messageFromMotionSystem->data.y_dot=0;
    return 0;
}

void printMessageFromClient(MessageToMotionSystem *messageFromClient){
    printf("%d",messageFromClient->data.control_state);
    printf("%d",messageFromClient->data.x);
    printf("%d",messageFromClient->data.x_lim1);
    printf("%d",messageFromClient->data.x_lim2);
    printf("%d",messageFromClient->data.x_cycle_time);
    printf("%d",messageFromClient->data.y);
    printf("%d",messageFromClient->data.y_lim1);
    printf("%d",messageFromClient->data.y_lim2);
    printf("%d",messageFromClient->data.y_cycle_time);
    printf("%d\n",messageFromClient->data.life_counter);
}
