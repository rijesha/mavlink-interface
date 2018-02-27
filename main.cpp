#ifdef STANDALONE

#include <stdio.h>   // Standard input/output definitions
#include "multithreaded_interface.h"
#include <common/mavlink.h>

#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_POSITION     0b0000110111111000

int system_id = 1;
int autopilot_id = 1;
int companion_id = 0;

void toggle_offboard_control(Multithreaded_Interface * mti, bool flag )
{
	// Prepare command for off-board mode
	mavlink_command_long_t com = { 0 };
	com.target_system    = system_id;
	com.target_component = autopilot_id;
	com.command          = MAV_CMD_NAV_GUIDED_ENABLE;
	com.confirmation     = true;
	com.param1           = (float) flag; // flag >0.5 => start, <0.5 => stop

	// Encode
	mavlink_message_t message;
	mavlink_msg_command_long_encode(system_id, companion_id, &message, &com);

	// Send the message
	mti->write_message(message);
}

int main(){
    Multithreaded_Interface mti;
    mti.start("/dev/ttyUSB0", 921600);

    mavlink_att_pos_mocap_t cp;
    mavlink_message_t att_pos_message;

    mavlink_set_position_target_local_ned_t sp;
    sp.type_mask = MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_POSITION;
	sp.coordinate_frame = MAV_FRAME_LOCAL_NED;
    mavlink_message_t set_target_message;

    Periodic_Message att_per_msg(&mti, att_pos_message,10);
    Periodic_Message set_target_per_msg(&mti, set_target_message, 15);

    mti.add_periodic_message(&att_per_msg);
    mti.add_periodic_message(&set_target_per_msg);

	cp.x = 17;
	cp.y = 435;
	cp.z = 0;
	cp.q[0] = 1; cp.q[1] = 0; cp.q[2] = 0; cp.q[3] = 0;
	mavlink_msg_att_pos_mocap_encode(system_id, companion_id, &att_pos_message, &cp);

	sp.x   = 1;
	sp.y   = 0;
	sp.z   = 0;
    mavlink_msg_set_position_target_local_ned_encode(system_id, companion_id, &set_target_message, &sp);
    set_target_per_msg.update_message(set_target_message);

    chrono::milliseconds i(2000);
    this_thread::sleep_for(i);
    
    toggle_offboard_control(&mti, true);

    int count = 0;
    while (count < 10){
        count++;
        cp.x = cp.x + 1;
        cout <<  cp.x << endl;
        mavlink_msg_att_pos_mocap_encode(system_id, companion_id, &att_pos_message, &cp);
        att_per_msg.update_message(att_pos_message);
        sp.x++;
        mavlink_msg_set_position_target_local_ned_encode(system_id, companion_id, &set_target_message, &sp);
        set_target_per_msg.update_message(set_target_message);
        chrono::milliseconds i(1000);
        this_thread::sleep_for(i);
    }

    toggle_offboard_control(&mti, false);

    mti.shutdown();
    return 0;
}

#endif