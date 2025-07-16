#ifndef SERVER_H
#define SERVER_H

#include "../../common/include/motion_system_messages.h"
#include "../../common/include/UDP.h"
#include "../../common/include/process_message.h"

#define TO_BufferSize sizeof(MessageToMotionSystem)
#define FROM_BufferSize sizeof(MessageFromMotionSystem)

int UDPServer(MessageToMotionSystem *messageFromClient, int port, char* ip);

#endif // SERVER_H