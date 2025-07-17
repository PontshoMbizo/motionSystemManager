#include "../../include/manager/msm.h"

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