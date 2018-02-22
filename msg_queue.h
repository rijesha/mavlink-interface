#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <iostream>
#include <queue>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <cmath>
#include <mutex>              
#include <condition_variable> 

using namespace std;

template <class T>
class MessageQueue
{
  private:
    queue<T> elements;
    mutex emptyQueueMtx;
    mutex queueLockMtx;
    condition_variable newDataInQueue;

  public:
    MessageQueue<T>();
    void push(T const &, int timeout = 0);
    T pop(int timeout = 0);
    void shutdown();
};

template <class T>
MessageQueue<T>::MessageQueue() {

}

template <class T>
T MessageQueue<T>::pop(int timeout) {
    queueLockMtx.lock();
    if (elements.empty()){
        queueLockMtx.unlock();
        std::unique_lock<std::mutex> lk(emptyQueueMtx);
        newDataInQueue.wait(lk);
        queueLockMtx.lock();
    }

    
    T e = elements.front();
    elements.pop();
    queueLockMtx.unlock();
    return e;
}

template <class T>
void MessageQueue<T>::push(T const &elem, int timeout) {
    queueLockMtx.lock();
    elements.push(elem);
    newDataInQueue.notify_all();
    queueLockMtx.unlock();
}

template <class T>
void MessageQueue<T>::shutdown() {
    elements.push(T());
    newDataInQueue.notify_all();
    queueLockMtx.unlock();
}

#endif