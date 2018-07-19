#ifdef STANDALONE

#include <stdio.h> // Standard input/output definitions
#include "position_controller.h"

#define PORT "/dev/ttyUSB0"
#define BAUD 921600

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

    int x = 25;
    int y = 125;
    int z = 250;

    cout << "Streaming 200 Position Messages before continuing" << endl;
    for (int ind = 0; ind < 200; ind++)
    {   
        p.update_current_position(x, y, z, 0);
        chrono::milliseconds k(100);
        this_thread::sleep_for(k);
        cout << "." << flush;
    }

    p.toggle_offboard_control(true);

    mti.bind_new_msg_callback(new_msg_callback);
    cout << "Bound Message CallBack" << endl;

    //This loop allows emulates new vision information being generated at 10 hz and target location updating at 0.5 Hz. It also print the last received attitude msg at 0.5 Hz
    int count = 0;
    int i = 0;

    while (i < 10)
    {
        
        count++;
        
        p.update_current_position(x + i * 10, y + i * 10, z + i * 10, 0);

        if (count == 18)
        {
            count = 0;
            i++;
            cout << "Updated Desired Position " << endl;
            p.update_desired_position(x + i * 5, y + i * 5, z + i * 5, 0);
            decode_last_attitude_msg(&mti);
        }
        
        chrono::milliseconds j(100);
        this_thread::sleep_for(j);
    }

    p.toggle_offboard_control(false);
    p.shutdown();
    return 0;
}

#endif
