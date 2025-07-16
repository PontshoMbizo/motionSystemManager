#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../include/server.h"

#define PORT 5000
#define TO_BufferSize sizeof(MessageToMotionSystem)
#define FROM_BufferSize sizeof(MessageFromMotionSystem)

int main()
{
    MessageToMotionSystem messageFromClient;
    UDPServer(&messageFromClient, PORT, server_IP);
    return 0;
}