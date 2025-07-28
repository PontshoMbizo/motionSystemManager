#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../include/manager/msm.h"

#define send_IP "127.0.0.1" //what the client will use to connect to the server
#define send_PORT 5000 //what the client will use to connect to the server
#define listen_IP "127.0.0.1" //what the server will use to listen for connections
#define listen_PORT 5000 //what the server will use to listen for connections

int main(){
    pthread_t client;
    MessageToMotionSystem message;
    initializeBuffer(&message);
    ClientThreadArgs clientArg;
    clientArg.messageToMS = &message;
    clientArg.ip = send_IP;
    clientArg.port = send_PORT;

    pthread_t server;
    MessageFromMotionSystem messageFromMS;
    ServerThreadArgs serverArg;
    serverArg.messageFromMS = &messageFromMS;
    serverArg.ip = listen_IP;
    serverArg.port = listen_PORT;

    pthread_create(&client, NULL, client_thread, &clientArg);
    pthread_create(&server, NULL, server_thread, &serverArg);
    pthread_join(client, NULL);
    pthread_join(server, NULL);
    return 0;
}

