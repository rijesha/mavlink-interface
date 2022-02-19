#pragma once

#include <mavlink.h>
#include <chrono>
#include <ctime>
#include <functional>
#include <map>
#include <thread>
#include <vector>
#include "msg_queue.h"
#include "serial_port.h"
#include "udp_device.h"

using namespace std;

long int get_curent_time();

class MavlinkMessage {
 public:
  MavlinkMessage();
  MavlinkMessage(mavlink_message_t msg);
  void update(mavlink_message_t msg);

  mavlink_message_t msg;
  bool newData = false;
  long int timestamp = 0;
};

typedef std::function<void(const mavlink_message_t &msg)> mavlink_msg_callback;

class MultithreadedInterface {
 private:
  SerialPort *serial_interface_{};
  UdpDevice *udp_interface_{};

  map<int, mavlink_message_t> last_messages;
  MessageQueue<mavlink_message_t> msg_queue;

  vector<mavlink_msg_callback> new_msg_callbacks;

  thread write_th;
  thread read_th;

  void start();

  void start_reader_thread();
  void start_writer_thread();

  void reader_thread();

 public:
  MultithreadedInterface(SerialPort &interface);
  MultithreadedInterface(UdpDevice &interface);

  void shutdown();

  void write_message(const mavlink_message_t &message);

  bool running = false;

  void bind_new_msg_callback(mavlink_msg_callback);
};
