#include "multithreaded_interface.h"

long int get_curent_time(){
  auto now_ms = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
  long int ms = chrono::duration_cast<chrono::milliseconds>(now_ms.time_since_epoch()).count();
  return ms;
}

Multithreaded_Interface::Multithreaded_Interface(){

}

void Multithreaded_Interface::start(const char* port, int baud){
    serial_port.uart_name = port;
	serial_port.baudrate = baud;
    serial_port.start();
    running = true;
    
    start_writer_thread();
    //start_reader_thread();
}

void Multithreaded_Interface::write_message(mavlink_message_t msg){
    msg_queue.push(msg);
}

void Multithreaded_Interface::start_writer_thread(){
    running = true;
    write_th = thread([=]() {
        while (running){
            mavlink_message_t msg;
            msg = msg_queue.pop();
            //mavlink_att_pos_mocap_t att_pos_mocap;
            //mavlink_msg_att_pos_mocap_decode(&msg, &att_pos_mocap);
            //cout << "sending with x of " << att_pos_mocap.x << endl;
            serial_port.write_message(msg);
        }   
    });
}

void Multithreaded_Interface::start_reader_thread(){
    running = true;

    read_th = thread([=]() {
        reader_thread();
    });
}

void Multithreaded_Interface::shutdown(){
    running = false;
    read_th.join();
    write_th.join();
    serial_port.stop();
}

void Multithreaded_Interface::reader_thread(){
    
    bool success;
    bool time_to_exit = false;

	while ( !time_to_exit )
	{
		mavlink_message_t message;
		success = serial_port.read_message(message);

		if( success )
		{
            my_map[message.msgid].update(message);
		}
	}
}

Periodic_Message::Periodic_Message(Multithreaded_Interface * mti, mavlink_message_t msg, float frequency):mti(mti), msg(msg) {
    interval = (1.0/frequency) * 1000.0; // in miliseconds 
}
void Periodic_Message::update_message(mavlink_message_t msg1){
    mtx.lock();
    msg = msg1;
    mtx.unlock();
}

void Periodic_Message::start_message(){
    running = true;
    th = thread([=]() {
        chrono::milliseconds i(interval);
        while (running && mti->running){
            this_thread::sleep_for(i);
            mtx.lock();
            mti->write_message(msg);
            mtx.unlock();
        }   
    });
}

void Periodic_Message::change_frequency(int frequency){
    interval = (1/frequency) * 1000; // in miliseconds
    stop_message();
    start_message();
}

void Periodic_Message::stop_message(){
    running = false;
    th.join();
}

Mavlink_Message::Mavlink_Message(){

}

Mavlink_Message::Mavlink_Message(mavlink_message_t msg): msg(msg){
    update(msg);
}

void Mavlink_Message::update(mavlink_message_t msg){
    timestamp = get_curent_time();
    newData = true;
    msg = msg;
}