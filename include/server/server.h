#ifndef SERVER_H
#define SERVER_H

#include "../common/motion_system_messages.h"
#include "../common/UDP.h"
#include "../common/process_message.h"

#define TO_BufferSize sizeof(MessageToMotionSystem)
#define FROM_BufferSize sizeof(MessageFromMotionSystem)

int UDPServer(MessageFromMotionSystem *messageFromMS, int port, char* ip);
int initializeMessageT(MessageFromMotionSystem *messageFromMS, MessageFromMotionSystem *messageToClient);
int compareLifeCounter(MessageFromMotionSystem *messageFromMS); //complete later
int validateCheckSum(MessageFromMotionSystem *messageFromMS);
#endif // SERVER_H