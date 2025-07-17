#ifndef PROCESS_MESSAGE_H
#define PROCESS_MESSAGE_H

#include "./motion_system_messages.h"

void printMessageT(MessageToMotionSystem *messageFromClient);
void printMessageF(MessageFromMotionSystem *messageFromMotionSystem);

#endif // PROCESS_MESSAGE_H