#ifndef CLIENT_H
#define CLIENT_H

#include "../../common/include/motion_system_messages.h" //message structure def in here...
#include "../../common/include/UDP.h"
#include "../../common/include/process_message.h"

#define TO_BufferSize sizeof(MessageToMotionSystem)
#define FROM_BufferSize sizeof(MessageFromMotionSystem)

int UDPClient(MessageToMotionSystem *message, int port, char* ip);
int initializeBuffer(MessageToMotionSystem *message);

#endif // CLIENT_H