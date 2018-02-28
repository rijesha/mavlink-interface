#ifndef POSITION_CONTROLLER_H
#define POSITION_CONTROLLER_H

#include "multithreaded_interface.h"
#include <common/mavlink.h>

#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_POSITION     0b0000110111111000


class Position_Controller
{
public:
    Position_Controller(Multithreaded_Interface * mti);
    Multithreaded_Interface * mti;
    mavlink_att_pos_mocap_t current_position;
    mavlink_set_position_target_local_ned_t desired_position;

    mavlink_message_t current_position_message;
    mavlink_message_t desired_position_message;

    Periodic_Message * current_position_periodic;
    Periodic_Message * desired_position_periodic;
    
    void update_current_position(int x, int y, int z, int yaw);
    void update_desired_position(int x, int y, int z, int yaw);

    void toggle_offboard_control(bool flag );

    void shutdown();
};


#endif //POSITION_CONTROLLER_H