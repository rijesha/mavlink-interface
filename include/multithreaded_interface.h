#ifndef MULTITHREADED_INTERFACE_H
#define MULTITHREADED_INTERFACE_H

#include "msg_queue.h"
#include "serial_port.h"
#include "udp_device.h"
#include <mavlink.h>
#include <map>
#include <thread>
#include <chrono>
#include <ctime>
#include <functional>

using namespace std;

long int get_curent_time();

class PeriodicMessage;

class MavlinkMessage
{
public:
  MavlinkMessage();
  MavlinkMessage(mavlink_message_t msg);
  void update(mavlink_message_t msg);

  mavlink_message_t msg;
  bool newData = false;
  long int timestamp = 0;
};

class MultithreadedInterface
{
private:
  SerialPort* serial_interface_{};
  UdpDevice* udp_interface_{};

  void start();

public:
  MultithreadedInterface(SerialPort& interface);
  MultithreadedInterface(UdpDevice& interface);

  void shutdown();

  map<int, mavlink_message_t> last_messages;
  MessageQueue<mavlink_message_t> msg_queue;

  thread write_th;
  thread read_th;

  void write_message(mavlink_message_t message);

  void start_reader_thread();
  void start_writer_thread();

  void reader_thread();
  bool add_periodic_message(PeriodicMessage *pm);
  bool running = false;

  vector<PeriodicMessage *> pm_container;
  void bind_new_msg_callback(std::function<void(mavlink_message_t)>);

  std::function<void(mavlink_message_t)> _cb;
  bool callback_registered = false;

};

class PeriodicMessage
{
public:
  PeriodicMessage();
  PeriodicMessage(MultithreadedInterface *mti, mavlink_message_t msg, float frequency);
  void start_message();
  void stop_message();
  void change_frequency(int frequency);
  void update_message(mavlink_message_t msg);

  void pause();
  void resume();

  int interval;

  MultithreadedInterface *mti;
  mavlink_message_t msg;
  mutex mtx;

  thread th;
  bool running = false;
};

#endif // MULTITHREADED_INTERFACE_H