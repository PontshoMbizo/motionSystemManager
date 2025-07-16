#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/client.h"
#define client_PORT 5000
#define client_IP "127.0.0.1"

int UDPClient(MessageToMotionSystem *message, int port, char* ip){
    WSADATA wsa;
    SOCKET clientSocketfd;
    struct sockaddr_in serveraddr;

    if (startUDPClient(&wsa, &clientSocketfd, &serveraddr, port, ip) != 0) return 1;

    while(1){
        if(connectUDP(&clientSocketfd, &serveraddr)) continue;
        if (sendUDPMessage(&clientSocketfd, &serveraddr, (char*)message, TO_BufferSize) != 0) continue; //retry if there are any errors
    }

    closesocket(clientSocketfd);
    WSACleanup();
    return 0;
}

int initializeBuffer(MessageToMotionSystem *message){ //test message
    message->data.control_state=2;
    message->data.life_counter=2;
    message->data.x=2;
    message->data.x_cycle_time=2;
    message->data.x_lim1=2;
    message->data.x_lim2=2;
    message->data.y=2;
    message->data.y_cycle_time=2;
    message->data.y_lim1=2;
    message->data.y_lim2=2;
    return 0;
}