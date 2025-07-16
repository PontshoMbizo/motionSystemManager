#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../include/msm.h"

#define client_IP "127.0.0.1"
#define client_PORT 5000
#define server_IP INADDR_ANY
#define server_PORT 5000

int main(){
    pthread_t client;
    MessageToMotionSystem message;
    initializeBuffer(&message);
    ClientThreadArgs clientArg;
    clientArg.message = &message;
    clientArg.ip = client_IP;
    clientArg.port = client_PORT;

    pthread_t server;
    MessageToMotionSystem messageFromClient;
    ServerThreadArgs serverArg;
    serverArg.messageFromClient = &message;
    serverArg.ip = server_IP;
    serverArg.port = server_PORT;

    pthread_create(&client, NULL, client_thread, &clientArg);
    pthread_create(&server, NULL, server_thread, &serverArg);
    pthread_join(client, NULL);
    pthread_join(server, NULL);
    return 0;
}

