#ifndef SERVER_H
#define SERVER_H
#pragma comment(lib, "ws2_32.lib")
#include "../../common/motion_system_messages.h"
#include "../../common/UDP.h"
#include "../../common/process_message.h"

#define TO_BufferSize sizeof(MessageToMotionSystem)
#define FROM_BufferSize sizeof(MessageFromMotionSystem)
#define server_IP INADDR_ANY

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

#endif // SERVER_H