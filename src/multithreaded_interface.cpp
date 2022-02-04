#include "../include/multithreaded_interface.h"

long int get_curent_time()
{
    auto now_ms = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    long int ms = chrono::duration_cast<chrono::milliseconds>(now_ms.time_since_epoch()).count();
    return ms;
}

bool MultithreadedInterface::add_periodic_message(PeriodicMessage *pm)
{
    if (running == false)
        return false;
    pm_container.push_back(pm);
    pm->start_message();
    return true;
}

MultithreadedInterface::MultithreadedInterface(SerialPort &interface)
{
    serial_interface_ = &interface;
    start();
}

MultithreadedInterface::MultithreadedInterface(UdpDevice &interface)
{
    udp_interface_ = &interface;
    start();
}

void MultithreadedInterface::start()
{
    running = true;
    start_writer_thread();
    start_reader_thread();
}

void MultithreadedInterface::write_message(const mavlink_message_t &msg)
{
    msg_queue.push(msg);
}

void MultithreadedInterface::start_writer_thread()
{
    write_th = thread([=]()
                      {
                          if (serial_interface_)
                          {
                              while (running)
                              {
                                  serial_interface_->write_message(msg_queue.pop(200));
                              }
                          }
                          else
                          {
                              while (running)
                              {
                                  udp_interface_->write_message(msg_queue.pop(200));
                              }
                          }
                      });
}

void MultithreadedInterface::start_reader_thread()
{
    read_th = thread([=]()
                     { reader_thread(); });
}

void MultithreadedInterface::shutdown()
{
    running = false;
    cout << "SHUTTING DOWN" << endl;
    if (serial_interface_)
    {
        serial_interface_->close_serial();
    }
    if (read_th.joinable())
        read_th.join();
    if (write_th.joinable())
        write_th.join();
    while (!pm_container.empty())
    {
        pm_container.back()->stop_message();
        pm_container.pop_back();
    }
}

void MultithreadedInterface::reader_thread()
{
    bool success;
    while (running)
    {
        mavlink_message_t message;
        if (serial_interface_)
        {
            success = serial_interface_->read_message(message);
        }
        else
        {
            success = udp_interface_->read_message(message);
        }

        if (success)
        {
            last_messages[message.msgid] = message;
            for (const auto &cb : new_msg_callbacks)
            {
                cb(message);
            }
        }
    }
}

void MultithreadedInterface::bind_new_msg_callback(mavlink_msg_callback cb)
{
    new_msg_callbacks.push_back(cb);
}

PeriodicMessage::PeriodicMessage() {}

PeriodicMessage::PeriodicMessage(MultithreadedInterface *mti, mavlink_message_t msg, float frequency) : mti(mti), msg(msg)
{
    interval = (1.0 / frequency) * 1000.0; // in miliseconds
    mti->add_periodic_message(this);
}

void PeriodicMessage::update_message(mavlink_message_t msg1)
{
    mtx.lock();
    msg = msg1;
    mtx.unlock();
}

void PeriodicMessage::pause()
{
    mtx.lock();
}

void PeriodicMessage::resume()
{
    mtx.unlock();
}

void PeriodicMessage::start_message()
{
    running = true;
    th = thread([=]()
                {
                    chrono::milliseconds i(interval);
                    while (running)
                    {
                        this_thread::sleep_for(i);
                        mtx.lock();
                        mti->write_message(msg);
                        mtx.unlock();
                    }
                });
}

void PeriodicMessage::change_frequency(int frequency)
{
    interval = (1 / frequency) * 1000; // in miliseconds
    stop_message();
    start_message();
}

void PeriodicMessage::stop_message()
{
    running = false;
    th.join();
}

MavlinkMessage::MavlinkMessage()
{
}

MavlinkMessage::MavlinkMessage(mavlink_message_t msg) : msg(msg)
{
    update(msg);
}

void MavlinkMessage::update(mavlink_message_t msg)
{
    timestamp = get_curent_time();
    newData = true;
    msg = msg;
}