#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/client.h"
#define client_PORT 5000
#define client_IP "127.0.0.1"

int main()
{
    MessageToMotionSystem message;
    initializeBuffer(&message); // Initialize the message buffer
    printMessageT(&message); // Print the message for debugging
    UDPClient(&message, client_PORT, client_IP);
    return 0;
}