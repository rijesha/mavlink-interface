#ifdef STANDALONE

#include <stdio.h> // Standard input/output definitions
#include "position_controller.h"

#define PORT "/dev/ttyS1"
#define BAUD 57600

void new_msg_callback(mavlink_message_t message)
{
    if (message.msgid == 0)
    {
        cout << "Received HB" << endl;
        mavlink_heartbeat_t heartbeat_msg;
        mavlink_msg_heartbeat_decode(&message, &heartbeat_msg);
    }
}

void decode_last_attitude_msg(Multithreaded_Interface *mti)
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
    Multithreaded_Interface mti;
    mti.start(PORT, BAUD);

    Position_Controller p(&mti);

    cout << "Streaming 100 Position Messages before continuing" << endl;
    for (int ind = 0; ind < 10; ind++)
    {
        chrono::milliseconds k(1000);
        this_thread::sleep_for(k);
        cout << "." << flush;
    }

    p.toggle_offboard_control(true);

    int i = 0;

    int x = 25;
    int y = 125;
    int z = 250;

    mti.bind_new_msg_callback(new_msg_callback);
    cout << "Bound Message CallBack" << endl;

    while (i < 5)
    {
        i++;
        decode_last_attitude_msg(&mti);
        p.update_current_position(x + i * 10, y + i * 10, z + i * 10, 0);
        p.update_desired_position(x + i * 5, y + i * 5, z + i * 5, 0);
        cout << "Updated Current and Desired Position " << endl;
        chrono::milliseconds j(5000);
        this_thread::sleep_for(j);
    }

    p.toggle_offboard_control(false);
    p.shutdown();
    return 0;
}

#endif
