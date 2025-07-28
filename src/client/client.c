#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/client/client.h"

int UDPClient(MessageToMotionSystem *message, int port, char* ip){
    WSADATA wsa;
    SOCKET clientSocketfd;
    struct sockaddr_in serveraddr;

    if (startUDPClient(&wsa, &clientSocketfd, &serveraddr, port, ip) != 0) return 1;

    while(1){
        if(connectUDP(&clientSocketfd, &serveraddr)) continue;
        setCheckSum(message); // set checksum before sending
        if (sendUDPMessage(&clientSocketfd, &serveraddr, (char*)message, TO_BufferSize) != 0) continue; //retry if there are any errors
    }

    closesocket(clientSocketfd);
    WSACleanup();
    return 0;
}

int setCheckSum(MessageToMotionSystem *message){
    message->footer.checksum = checkSum((unsigned char *)&message->data, TO_NUM_ELEMENTS);
    return 0;
}

int initializeBuffer(MessageToMotionSystem *message){ //test message
    message->data.y1=2;
    message->data.y2=0; // reset life counter
    message->data.y3=2;
    message->data.y4=2;
    message->data.y5=2;
    message->data.y6=2;
    message->data.y7=2;
    message->data.y8=2;
    message->data.y9=2;
    message->data.y10=2;
    return 0;
}