
#include "position_controller.h"


int system_id = 1;
int autopilot_id = 1;
int companion_id = 0;

Position_Controller::Position_Controller(Multithreaded_Interface *mti)
{
	this->mti = mti;

	desired_position.type_mask = MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_POSITION;
	desired_position.coordinate_frame = MAV_FRAME_LOCAL_NED;

	current_position_periodic = new Periodic_Message(mti, current_position_message, 10);
	desired_position_periodic = new Periodic_Message(mti, desired_position_message, 15);

	update_current_position(0, 0, 0, 0);
	update_desired_position(0, 0, 0, 0);
}

void Position_Controller::update_current_position(float x, float y, float z, float yaw)
{
	current_position.x = x;
	current_position.y = y;
	current_position.z = z;

	toQuaternion(0, 0, yaw, &current_position.q[0], &current_position.q[1], &current_position.q[2], &current_position.q[3]);
	cout << current_position.q[0] << " " << current_position.q[1]<< " " << current_position.q[2]<< " " << current_position.q[3] << endl;
	//current_position.q[0] = 1;
	//current_position.q[1] = 0;
	//current_position.q[2] = 0;
	//current_position.q[3] = 0;

	mavlink_msg_att_pos_mocap_encode(system_id, companion_id, &current_position_message, &current_position);
	current_position_periodic->update_message(current_position_message);
}

void Position_Controller::update_desired_position(float x, float y, float z, float yaw)
{
	desired_position.x = x;
	desired_position.y = y;
	desired_position.z = z;

	mavlink_msg_set_position_target_local_ned_encode(system_id, companion_id, &desired_position_message, &desired_position);
	desired_position_periodic->update_message(desired_position_message);
}

void Position_Controller::toQuaternion(float ai, float aj, float ak, float *q0, float *q1, float *q2, float *q3)
{
	/*
	double cy = cos(yaw*3.14/180 * 0.5);
	double sy = sin(yaw*3.14/180 * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);

	*w = cy * cr * cp + sy * sr * sp;
	*x = cy * sr * cp - sy * cr * sp;
	*y = cy * cr * sp + sy * sr * cp;
	*z = sy * cr * cp - cy * sr * sp;
*/
cout << "yaw" << ak << endl; 
ai = ai * 0.5 ;
aj = aj * 0.5 ;
ak = ak * 0.5 ;

float ci = cos(ai);
float si = sin(ai);
float cj = cos(aj);
float sj = sin(aj);
float ck = cos(ak);
float sk = sin(ak);

float cc = ci*ck;
float cs = ci*sk;
float sc = si*ck;
float ss = si*sk;

*q1 = cj*sc - sj*cs;
*q2 = cj*ss + sj*cc;
*q3 = cj*cs - sj*sc;
*q0 = cj*cc + sj*ss;

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

void Position_Controller::shutdown()
{
	mti->shutdown();
}
