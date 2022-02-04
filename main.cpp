

#include <stdio.h> // Standard input/output definitions
#include "include/multithreaded_interface.h"

void new_msg_callback(mavlink_message_t message)
{
    if (message.msgid == 0)
    {
        cout << "Received HB" << endl;
        mavlink_heartbeat_t heartbeat_msg;
        mavlink_msg_heartbeat_decode(&message, &heartbeat_msg);
        //printf("[compid sysid] = [%d %d] \n", message.compid, message.sysid);
    }
    else if (message.msgid == 32)
    {
        //cout << "Got Local Position Ned" << endl;
        mavlink_local_position_ned_t local_position_ned_msg;
        mavlink_msg_local_position_ned_decode(&message, &local_position_ned_msg);
    }
    else if (message.msgid == 30)
    {
        //cout << "Got Attitude msg" << endl;
        mavlink_attitude_t attitude_msg;
        mavlink_msg_attitude_decode(&message, &attitude_msg);
    }
}

void decode_last_attitude_msg(MultithreadedInterface *mti)
{
    auto search = mti->last_messages.find(MAVLINK_MSG_ID_ATTITUDE);
    if (search != mti->last_messages.end())
    {
        mavlink_attitude_t att;
        mavlink_msg_attitude_decode(&(search->second), &att);
        printf("[Roll Pitch Yaw] = [%f %f %f] \n", att.roll, att.pitch, att.yaw);
    }
    else
    {
        std::cout << "Attitude Message Not found\n";
    }
}

int main()
{
    SerialPort serial_port("/dev/ttyUSB0", 115200);
    MultithreadedInterface mti(serial_port);

    //UdpDevice udp_device("127.0.0.1", 14560);
    //to connect to mavproxy do the following
    //mavproxy.py --master=udpout:127.0.0.1:14560 --out=udpout:127.0.0.1:14561 
    //MultithreadedInterface mti(udp_device);

    mti.bind_new_msg_callback(new_msg_callback);
    cout << "Bound Message CallBack" << endl;

    this_thread::sleep_for(chrono::milliseconds(10000));

    mti.shutdown();
    return 0;
}
