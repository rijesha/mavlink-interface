#include "multithreaded_interface.h"

long int get_curent_time()
{
    auto now_ms = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    long int ms = chrono::duration_cast<chrono::milliseconds>(now_ms.time_since_epoch()).count();
    return ms;
}

Multithreaded_Interface::Multithreaded_Interface()
{
}

bool Multithreaded_Interface::add_periodic_message(Periodic_Message *pm)
{
    if (running == false)
        return false;
    pm_container.push_back(pm);
    pm->start_message();
    return true;
}

void Multithreaded_Interface::start(const char *port, int baud)
{
    serial_port.uart_name = port;
    serial_port.baudrate = baud;
    serial_port.start();
    running = true;

    start_writer_thread();
    start_reader_thread();
}

void Multithreaded_Interface::write_message(mavlink_message_t msg)
{
    msg_queue.push(msg);
}

void Multithreaded_Interface::start_writer_thread()
{
    running = true;
    write_th = thread([=]() {
        while (running)
        {
            serial_port.write_message(msg_queue.pop(200));
        }
    });
}

void Multithreaded_Interface::start_reader_thread()
{
    read_th = thread([=]() {
        reader_thread();
    });
}

void Multithreaded_Interface::shutdown()
{
    running = false;
    cout << "SHUTTING DOWN" << endl;
    if (read_th.joinable())
        read_th.join();
    if (write_th.joinable())
        write_th.join();
    while (!pm_container.empty())
    {
        pm_container.back()->stop_message();
        pm_container.pop_back();
    }
    serial_port.stop();
}

void Multithreaded_Interface::reader_thread()
{
    bool success;
    while (running)
    {
        mavlink_message_t message;
        success = serial_port.read_message(message);

        if (success)
        {
            last_messages[message.msgid] = message;
            if (callback_registered)
            {
                _cb(message);
            }
        }
    }
}

void Multithreaded_Interface::bind_new_msg_callback(std::function<void(mavlink_message_t)> cb)
{
    _cb = cb;
    callback_registered = true;
}

Periodic_Message::Periodic_Message() {}

Periodic_Message::Periodic_Message(Multithreaded_Interface *mti, mavlink_message_t msg, float frequency) : mti(mti), msg(msg)
{
    interval = (1.0 / frequency) * 1000.0; // in miliseconds
    mti->add_periodic_message(this);
}

void Periodic_Message::update_message(mavlink_message_t msg1)
{
    mtx.lock();
    msg = msg1;
    mtx.unlock();
}

void Periodic_Message::pause()
{
    mtx.lock();
}

void Periodic_Message::resume()
{
    mtx.unlock();
}

void Periodic_Message::start_message()
{
    running = true;
    th = thread([=]() {
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

void Periodic_Message::change_frequency(int frequency)
{
    interval = (1 / frequency) * 1000; // in miliseconds
    stop_message();
    start_message();
}

void Periodic_Message::stop_message()
{
    running = false;
    th.join();
}

Mavlink_Message::Mavlink_Message()
{
}

Mavlink_Message::Mavlink_Message(mavlink_message_t msg) : msg(msg)
{
    update(msg);
}

void Mavlink_Message::update(mavlink_message_t msg)
{
    timestamp = get_curent_time();
    newData = true;
    msg = msg;
}