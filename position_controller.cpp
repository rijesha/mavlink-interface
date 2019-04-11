#include "position_controller.h"

int system_id = 1;
int autopilot_id = 1;
int companion_id = 0;

float Position_Controller::bind_max_value(float val, float max_val, float min_val){
    if (val > max_val)
        return max_val;
    else if (val < min_val)
        return min_val;
    return val;
}

Position_Controller::Position_Controller(Multithreaded_Interface *mti)
{
	this->mti = mti;

	desired_position.type_mask = MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_POSITION;
	desired_position.coordinate_frame = MAV_FRAME_LOCAL_NED;

	//desired_position_periodic = new Periodic_Message(mti, desired_position_message, 10);

	update_current_position(0, 0, 0, 0);
	update_desired_position(0, 0, 0, 0);
}

void Position_Controller::update_current_position(float x, float y, float z, float yaw)
{
	current_position.x = x;
	current_position.y = y;
	current_position.z = z;
	current_position.yaw = yaw;

	mavlink_msg_vision_position_estimate_encode(system_id, companion_id, &current_position_message, &current_position);
	mti->write_message(current_position_message);
}

void Position_Controller::update_desired_position(float x, float y, float z, float yaw)
{
	desired_position.x = x;
	desired_position.y = y;
	desired_position.z = z;
	desired_position.yaw = yaw;
	desired_position.target_system = 1;
	desired_position.target_component = 0;

	mavlink_msg_set_position_target_local_ned_encode(system_id, companion_id, &desired_position_message, &desired_position);
	desired_position_periodic->update_message(desired_position_message);
}

void Position_Controller::update_attitude_target(float pitch_target, float roll_target, float yaw_target, float vel_z)
{
	float cr2 = cosf(roll_target*M_PI/180.0f*0.5f);
	float cp2 = cosf(pitch_target*M_PI/180.0f*0.5f);
	float cy2 = cosf(yaw_target*M_PI/180.0f*0.5f);
	float sr2 = sinf(roll_target*M_PI/180.0f*0.5f);
	float sp2 = sinf(pitch_target*M_PI/180.0f*0.5f);
	float sy2 = sinf(yaw_target*M_PI/180.0f*0.5f);

	attitude_target.q[0] = cr2*cp2*cy2 + sr2*sp2*sy2;
	attitude_target.q[1] = sr2*cp2*cy2 - cr2*sp2*sy2;
	attitude_target.q[2] = cr2*sp2*cy2 + sr2*cp2*sy2;
	attitude_target.q[3] = cr2*cp2*sy2 - sr2*sp2*cy2;

	float thrust = (vel_z*100)/(2.0*DEFAULT_SPEED_UP) + 0.5;
	float thrust = bind_max_value(thrust,1,0);

	attitude_target.thrust = thrust;

	attitude_target.target_system = 1;
	attitude_target.target_component = 0;

	attitude_target.type_mask = 0x7;

	mavlink_msg_set_attitude_target_encode(system_id, companion_id, &attitude_target_message, &attitude_target);
	mti->write_message(attitude_target_message);
}

void Position_Controller::toggle_offboard_control(bool flag)
{
	// Prepare command for off-board mode
	mavlink_command_long_t com = {0};
	com.target_system = system_id;
	com.target_component = autopilot_id;
	com.command = MAV_CMD_NAV_GUIDED_ENABLE;
	com.confirmation = true;
	com.param1 = (float)flag; // flag >0.5 => start, <0.5 => stop

	// Encode
	mavlink_message_t message;
	mavlink_msg_command_long_encode(system_id, companion_id, &message, &com);

	// Send the message
	mti->write_message(message);
}

float Position_Controller::getLastAttitudeYaw()
{
	auto search = mti->last_messages.find(MAVLINK_MSG_ID_ATTITUDE);
    if (search != mti->last_messages.end())
    {
        mavlink_attitude_t att;
        mavlink_msg_attitude_decode(&(search->second), &att);
        //printf("[Roll Pitch Yaw] = [%f %f %f] \n", att.roll, att.pitch, att.yaw);
		return att.yaw;
    }
    else
    {
        std::cout << "Attitude Message Not found\n";
		return 0;
    }
}

void Position_Controller::shutdown()
{
	mti->shutdown();
}
