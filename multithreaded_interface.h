#ifndef MULTITHREADED_INTERFACE_H
#define MULTITHREADED_INTERFACE_H

#include "msg_queue.h"
#include "serial_port.h"
#include <compVisionModule/mavlink.h>
#include <map>
#include <thread>
#include <chrono>
#include <ctime>
#include <functional>

using namespace std;

long int get_curent_time();
class Periodic_Message;
class Multithreaded_Interface;

class Mavlink_Message
{
  public:
    Mavlink_Message();
    Mavlink_Message(mavlink_message_t msg);
    void update(mavlink_message_t msg);

    mavlink_message_t msg;
    bool newData = false;
    long int timestamp = 0;
};

class Multithreaded_Interface
{
  public:
    Multithreaded_Interface();

    void start(const char *port, int baud);
    void shutdown();

    Serial_Port serial_port;
    map<int, mavlink_message_t> last_messages;
    MessageQueue<mavlink_message_t> msg_queue;

    thread write_th;
    thread read_th;

    void write_message(mavlink_message_t message);

    void start_reader_thread();
    void start_writer_thread();

    void reader_thread();
    bool add_periodic_message(Periodic_Message *pm);
    bool running = false;

    vector<Periodic_Message *> pm_container;
    void bind_new_msg_callback(std::function<void(mavlink_message_t)>);

    std::function<void(mavlink_message_t)> _cb;
    bool callback_registered = false;

    //int sysid = 0;
    //int compid = 0;
};

class Periodic_Message
{
  public:
    Periodic_Message();
    Periodic_Message(Multithreaded_Interface *mti, mavlink_message_t msg, float frequency);
    void start_message();
    void stop_message();
    void change_frequency(int frequency);
    void update_message(mavlink_message_t msg);

    void pause();
    void resume();

    int interval;

    Multithreaded_Interface *mti;
    mavlink_message_t msg;
    mutex mtx;

    thread th;
    bool running = false;
};

#endif // MULTITHREADED_INTERFACE_H