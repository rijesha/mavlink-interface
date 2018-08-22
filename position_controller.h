#ifndef POSITION_CONTROLLER_H
#define POSITION_CONTROLLER_H

#include "multithreaded_interface.h"
#include <mavlink.h>

#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_POSITION 0b0000101111111000

class Position_Controller
{
public:
  Position_Controller(Multithreaded_Interface *mti);
  Multithreaded_Interface *mti;

  mavlink_vision_position_estimate_t current_position;
  mavlink_set_position_target_local_ned_t desired_position;

  mavlink_message_t current_position_message;
  mavlink_message_t desired_position_message;

  Periodic_Message *desired_position_periodic;

  void update_current_position(float x, float y, float z, float yaw);
  void update_desired_position(float x, float y, float z, float yaw);
  
  void toggle_offboard_control(bool flag);

  float getLastAttitudeYaw();

  void shutdown();
};

#endif //POSITION_CONTROLLER_H