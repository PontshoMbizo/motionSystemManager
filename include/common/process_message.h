#ifndef PROCESS_MESSAGE_H
#define PROCESS_MESSAGE_H

#include "./motion_system_messages.h"

#define TO_NUM_ELEMENTS 10
#define FROM_NUM_ELEMENTS 19

void printMessageT(MessageToMotionSystem *messageToMS);
void printMessageF(MessageFromMotionSystem *messageFromMS);
int checkSum(unsigned char *data, int nElements); //return a checksum of the message
#endif // PROCESS_MESSAGE_H