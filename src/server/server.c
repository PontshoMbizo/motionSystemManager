#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../../include/server/server.h"

int UDPServer(MessageFromMotionSystem *messageFromMS, int port, char* ip){
    WSADATA wsa;
    SOCKET serverSocketfd;
    struct sockaddr_in serveraddr, clientaddr;
    int clientaddrLen;

    if (startUDPServer(&wsa, &serverSocketfd, &serveraddr, port, ip) != 0) return 1;

    while(1){
        if(receiveUDPMessageWithAddr(&serverSocketfd, (char*)messageFromMS, FROM_BufferSize, &clientaddr, &clientaddrLen)!=0) return 1; //stop if there are any errors
        validateCheckSum(messageFromMS); // Checksum validation
        printf("receiving: "); printMessageF(messageFromMS);
    };

    // Clean up
    closesocket(serverSocketfd);
    WSACleanup();
    return 0;
}

int validateCheckSum(MessageFromMotionSystem *messageFromMS){
    if (messageFromMS->footer.checksum == checkSum((unsigned char *)&messageFromMS->data, FROM_NUM_ELEMENTS)) {
        return 0;
    } else {
        printf("Checksum mismatch");
        return 1;
    }
    return 1;
}