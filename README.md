# mavlink-interface
The purpose of this repository is to provide a better interface than the c_uart_example that mavlink provides. 
This interface allows for multithreaded message writing to the interface. 

Also included is a position controller class. 
This is a really simple class that can be used to send both `vision_position_estimate` and `set_position_target_local_ned` messages to fully control the desired and current position of the UAV.


## Setting Up Repo
```
git clone https://github.com/rijesha/mavlink-interface
cd mavlink-interface
git submodule init
git submodule update
```
## Setting up the PX4 Compatible Board

Using px4 v1.8.0 the steps to send position data are as follows.

Build the regular release of px4. (https://dev.px4.io/en/setup/building_px4.html) and upload it. Or try to install the latest version available on QGroundControl.

```
make px4fmu-v2_default
make px4fmu-v2_default upload
```

* Select a multirotor airframe.
* Change EKF2_AID_MASK to accept vision information. (set value to 24 to completely disable GPS and only use vision)
* Change EKFS_HGT_MODE to Vision.
* Change SYS_COMPANION to 921600.

Power the px4 via battery. I have experienced issues with the local_position_target message when powered via usb.

## Making And Running the Example
Set up the serial port name in main.cpp
```
#define PORT "/dev/ttyUSB0"
#define BAUD 921600
```

Then build and run the program.

```
make
./position_controller
```

## Integration of the Mavlink Multithreaded Interface

### Setting up the Multithreaded Interface

```
Multithreaded_Interface mti;
mti.start(PORT, BAUD);
```

### Reading Messages from Mavlink Interface

#### Reading Last Message received (Polling Mode)
Example for how to read last available message.
```
auto search = mti.last_messages.find(MAVLINK_MSG_ID_ATTITUDE);
if(search != mti.last_messages.end()) {
    mavlink_attitude_t att;
    mavlink_msg_attitude_decode(&(search->second), &att);
    printf("[Roll Pitch Yaw] = [%f %f %f] \n",att.roll, att.pitch, att.yaw);
}
else {
    std::cout << "Attitude Message not yet Received\n";
}
```

#### Binding a message callback function (Interrupt Mode)
The purpose of this mode is to allow a received message to trigger an action.

Create function with the following signature 
```
std::function<void(mavlink_message_t)> // functions returns void and takes in mavlink_message_t
```

Example callback function with proper signature.
```
void new_msg_callback(mavlink_message_t message) {
    if (message.msgid == 0){
        cout << "Received HB" << endl;
        mavlink_heartbeat_t heartbeat_msg;
        mavlink_msg_heartbeat_decode(&message, &heartbeat_msg);
    }
}
```

Binding the callback
```
mti.bind_new_msg_callback(new_msg_callback);
```

### Writing Messages to Mavlink Interface
Encode and send a mavlink message. See position_controller.cpp for an example.
```
mavlink_message_t message;
mavlink_msg_command_long_encode(system_id, companion_id, &message, &com);

//Send the message
mti.write_message(message);
```

#### Setting Up Periodic Messages
A periodic message class has been made to allow for periodic messages to be sent. positional_controller.cpp has a great example of how to use it.

Setting up Periodic_Message object.
```
mavlink_message_t current_position_message;
int frequency = 10; // frequency in Hz
Periodic_Message current_position_periodic(*mti, current_position_message, frequency);
```

Updating the message
```
current_position_periodic.update_message(current_position_message);
```
## Integration of Position Controller Class
Setup the mti as previously and the setup of position_controller.
```
Position_Controller p(&mti);
```

Update current and desired positions
```
p.update_current_position(x, y, z, yaw);
p.update_desired_position(x, y, z, yaw);
```
After 100 desired position messages, offboard mode can be enabled.
```
p.toggle_offboard_control(true); // enable offboard mode
p.toggle_offboard_control(false); // disable offboard mode
```
