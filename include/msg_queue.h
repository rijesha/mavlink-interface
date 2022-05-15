#pragma once

#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <string>

using namespace std;
using namespace std::literals::chrono_literals;

template <class T>
class MessageQueue {
 private:
  queue<T> elements;
  mutex emptyQueueMtx;
  mutex queueLockMtx;
  condition_variable newDataInQueue;

 public:
  MessageQueue();
  void push(T const &, int timeout = 0);
  T pop(int timeout = 0);
  void shutdown();
};

template <class T>
MessageQueue<T>::MessageQueue() {}

template <class T>
T MessageQueue<T>::pop(int timeout) {
  queueLockMtx.lock();
  if (elements.empty()) {
    queueLockMtx.unlock();
    std::unique_lock<std::mutex> lk(emptyQueueMtx);
    if (timeout == 0) {
      newDataInQueue.wait(lk);
    } else {
      if (newDataInQueue.wait_for(lk, timeout * 1ms) == cv_status::timeout) {
        return T();
      }
    }
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
