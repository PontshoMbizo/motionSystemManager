#include <stdio.h>
#include "../../include/common/motion_system_messages.h"

// messageSize is the size of the message structure
//MessageFromMotionSystem has a messageSize of 19 (19 elements)
//MessageToMotionSystem has a messageSize of 10 (10 elements)

//message is a pointer to the message data structure (i.e., MessageFromMotionSystem.data or MessageToMotionSystem.data)
int checkSum(unsigned char *data, int nElements) {
    unsigned int sum = 0;
    for (int i = 0; i < nElements; i++) {
        sum += *(data+i) & 0x00FF;
    }
    return sum;
}

void printMessageT(MessageToMotionSystem *messageFromClient){
    printf("%d",messageFromClient->data.y1);
    printf("%d",messageFromClient->data.y2);
    printf("%d",messageFromClient->data.y3);
    printf("%d",messageFromClient->data.y4);
    printf("%d",messageFromClient->data.y5);
    printf("%d",messageFromClient->data.y6);
    printf("%d",messageFromClient->data.y7);
    printf("%d",messageFromClient->data.y8);
    printf("%d\t\t",messageFromClient->data.y9);
}

void printMessageF(MessageFromMotionSystem *messageFromMotionSystem){
    printf("%d",messageFromMotionSystem->data.x1);
    printf("%d",messageFromMotionSystem->data.x2);
    printf("%d",messageFromMotionSystem->data.x3);
    printf("%d",messageFromMotionSystem->data.x4);
    printf("%d",messageFromMotionSystem->data.x5);
    printf("%d",messageFromMotionSystem->data.x6);
    printf("%d",messageFromMotionSystem->data.x7);
    printf("%d",messageFromMotionSystem->data.x8);
    printf("%d",messageFromMotionSystem->data.x9);
    printf("%d",messageFromMotionSystem->data.x10);
    printf("%d",messageFromMotionSystem->data.x11);
    printf("%d",messageFromMotionSystem->data.x12);
    printf("%d",messageFromMotionSystem->data.x13);
    printf("%d",messageFromMotionSystem->data.x14);
    printf("%d",messageFromMotionSystem->data.x15);
    printf("%d",messageFromMotionSystem->data.x16);
    printf("%d",messageFromMotionSystem->data.x17);
    printf("%d\t\t",messageFromMotionSystem->data.x18);
}