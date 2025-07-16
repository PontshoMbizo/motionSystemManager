#ifndef PROCESS_MESSAGE_H
#define PROCESS_MESSAGE_H

#include "./motion_system_messages.h"

void printMessageT(MessageToMotionSystem *messageFromClient){
    printf("%d",messageFromClient->data.control_state);
    printf("%d",messageFromClient->data.x);
    printf("%d",messageFromClient->data.x_lim1);
    printf("%d",messageFromClient->data.x_lim2);
    printf("%d",messageFromClient->data.x_cycle_time);
    printf("%d",messageFromClient->data.y);
    printf("%d",messageFromClient->data.y_lim1);
    printf("%d",messageFromClient->data.y_lim2);
    printf("%d",messageFromClient->data.y_cycle_time);
    printf("%d\n",messageFromClient->data.life_counter);
}

void printMessageF(MessageFromMotionSystem *messageFromMotionSystem){
    printf("%d",messageFromMotionSystem->data.error_indram_x1);
    printf("%d",messageFromMotionSystem->data.error_indram_x2);
    printf("%d",messageFromMotionSystem->data.error_indram_y1);
    printf("%d",messageFromMotionSystem->data.error_indram_y2);
    printf("%d",messageFromMotionSystem->data.error_interlock);
    printf("%d",messageFromMotionSystem->data.error_msg1);
    printf("%d",messageFromMotionSystem->data.error_msg2);
    printf("%d",messageFromMotionSystem->data.life_counter);
    printf("%d",messageFromMotionSystem->data.motion_control);
    printf("%d",messageFromMotionSystem->data.motion_status);
    printf("%d",messageFromMotionSystem->data.spare);
    printf("%d",messageFromMotionSystem->data.washout_x);
    printf("%d",messageFromMotionSystem->data.washout_y);
    printf("%d",messageFromMotionSystem->data.x);
    printf("%d",messageFromMotionSystem->data.x_ddot);
    printf("%d",messageFromMotionSystem->data.x_dot);
    printf("%d",messageFromMotionSystem->data.y);
    printf("%d",messageFromMotionSystem->data.y_ddot);
    printf("%d\n",messageFromMotionSystem->data.y_dot);
}

#endif // PROCESS_MESSAGE_H