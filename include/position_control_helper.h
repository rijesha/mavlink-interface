#pragma once

#include "multithreaded_interface.h"

inline void send_set_attitude_target(MultithreadedInterface &mti,
                                     float pitch_target, float roll_target,
                                     float yaw_target,
                                     float ratio_of_vel_z_to_default_speed_up,
                                     float yaw_rate, bool use_yaw_rate) {
  float cr2 = cosf(roll_target * M_PI / 180.0f * 0.5f);
  float cp2 = cosf(pitch_target * M_PI / 180.0f * 0.5f);
  float cy2 = cosf(yaw_target * M_PI / 180.0f * 0.5f);
  float sr2 = sinf(roll_target * M_PI / 180.0f * 0.5f);
  float sp2 = sinf(pitch_target * M_PI / 180.0f * 0.5f);
  float sy2 = sinf(yaw_target * M_PI / 180.0f * 0.5f);

  mavlink_set_attitude_target_t attitude_target;
  attitude_target.q[0] = cr2 * cp2 * cy2 + sr2 * sp2 * sy2;
  attitude_target.q[1] = sr2 * cp2 * cy2 - cr2 * sp2 * sy2;
  attitude_target.q[2] = cr2 * sp2 * cy2 + sr2 * cp2 * sy2;
  attitude_target.q[3] = cr2 * cp2 * sy2 - sr2 * sp2 * cy2;

  if (ratio_of_vel_z_to_default_speed_up > 1) {
    ratio_of_vel_z_to_default_speed_up = 1;
  } else if (ratio_of_vel_z_to_default_speed_up < -1) {
    ratio_of_vel_z_to_default_speed_up = -1;
  }

  attitude_target.thrust = (ratio_of_vel_z_to_default_speed_up) / (2.0) + 0.5;

  attitude_target.target_system = 0;
  attitude_target.target_component = 0;

  attitude_target.type_mask = 0x03;
  attitude_target.body_yaw_rate = yaw_rate * M_PI / 180.0f;

  mavlink_message_t attitude_target_message;
  mavlink_msg_set_attitude_target_encode(
      0, 0, &attitude_target_message, &attitude_target);
  mti.write_message(attitude_target_message);
}

inline void enable_offboard_control(MultithreadedInterface &mti,
                                    bool flag = true) {
  // Prepare command for off-board mode
  mavlink_command_long_t com = {0};
  com.target_system = 0;
  com.target_component = 1;
  com.command = MAV_CMD_DO_SET_MODE;
  com.confirmation = true;
  com.param1 =
      MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;  // flag >0.5 => start, <0.5 => stop
  com.param2 = flag ? 4 : 0;

  // Encode
  mavlink_message_t message;
  mavlink_msg_command_long_encode(0, 0, &message, &com);

  // Send the message
  mti.write_message(message);
}

inline void enable_message_stream(MultithreadedInterface &mti, int id,
                                  int period) {
  {
    // Prepare command for off-board mode
    mavlink_command_long_t com = {0};
    com.target_system = 0;
    com.target_component = 1;
    com.command = MAV_CMD_SET_MESSAGE_INTERVAL;
    com.confirmation = true;
    com.param1 = id;  // flag >0.5 => start, <0.5 => stop
    com.param2 = period;
    com.param7 = 0;

    // Encode
    mavlink_message_t message;
    mavlink_msg_command_long_encode(0, 0, &message, &com);

    // Send the message
    mti.write_message(message);
  }
}

inline void enable_attitude_messages(MultithreadedInterface &mti, int period) {
  enable_message_stream(mti, MAVLINK_MSG_ID_ATTITUDE, period);
}

inline void enable_local_position_estimate_messages(MultithreadedInterface &mti,
                                                    int period) {
  enable_message_stream(mti, MAVLINK_MSG_ID_LOCAL_POSITION_NED, period);
}
