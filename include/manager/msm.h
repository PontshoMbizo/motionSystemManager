#ifndef MSM_H
#define MSM_H
#pragma once
#include <pthread.h>
#include "../client/client.h"
#include "../server/server.h"

typedef struct {
    MessageToMotionSystem *messageToMS;
    int port;
    char *ip;
} ClientThreadArgs;

typedef struct {
    MessageFromMotionSystem *messageFromMS;
    int port;
    char *ip;
} ServerThreadArgs;

void *client_thread(void *arg);
void *server_thread(void *arg);

#endif // MSM_H