#ifndef MSM_H
#define MSM_H
#pragma once
#include <pthread.h>
#include "../../client/include/client.h"
#include "../../server/include/server.h"

typedef struct {
    MessageToMotionSystem *message;
    int port;
    char *ip;
} ClientThreadArgs;

typedef struct {
    MessageToMotionSystem *messageFromClient;
    int port;
    char *ip;
} ServerThreadArgs;

void *client_thread(void *arg){
    ClientThreadArgs *data = (ClientThreadArgs*)arg;
    UDPClient(data->message, data->port, data->ip);
    pthread_exit(NULL);
};

void *server_thread(void *arg){
    ServerThreadArgs *data = (ServerThreadArgs*) arg;
    UDPServer(data->messageFromClient,data->port, data->ip);
    pthread_exit(NULL);
}

#endif // MSM_H