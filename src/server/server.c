#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../../include/server/server.h"

int UDPServer(MessageToMotionSystem *messageFromClient, int port, char* ip){
    WSADATA wsa;
    SOCKET serverSocketfd;
    struct sockaddr_in serveraddr, clientaddr;
    int clientaddrLen;

    if (startUDPServer(&wsa, &serverSocketfd, &serveraddr, port, ip) != 0) return 1;

    while(1){
        if(receiveUDPMessageWithAddr(&serverSocketfd, (char*)messageFromClient, FROM_BufferSize, &clientaddr, &clientaddrLen)!=0) return 1; //stop if there are any errors
        printf("Received message from client: \t");
        printMessageT(messageFromClient);
    };

    // Clean up
    closesocket(serverSocketfd);
    WSACleanup();
    return 0;
}