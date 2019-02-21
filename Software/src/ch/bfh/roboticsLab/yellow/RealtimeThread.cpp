#line 2 "ch/bfh/roboticsLab/yellow/RealtimeThread.cpp"
/* Copyright (C) BFH roboticsLab
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/RealtimeThread.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

RealtimeThread::Signal::Signal() {

  mutex.lock();

  int32_t n = 0;
  while ((((1 << n) & signals) > 0) && (n < 30))
    n++;
  signal = (1 << n);

  mutex.unlock();
}

RealtimeThread::Signal::~Signal() {

  mutex.lock();
  signals &= ~signal;
  mutex.unlock();
}

RealtimeThread::RealtimeThread(const float period, const osPriority_t priority, const uint32_t stackSize) :
    period(period), priority(priority), stackSize(stackSize), keepRunning(false), thread(0) {

}

RealtimeThread::~RealtimeThread() {
  stop();
}

void RealtimeThread::start() {

  if (isAlive())
    return;

  // Implementation comment: A thread may only be started once so create a thread every time start() is called.
  thread = new Thread(priority, stackSize);

  // start thread and timer interrupt
  keepRunning = true;
  thread->start(callback(&RealtimeThread::staticRun, this));
  ticker.attach(callback(&RealtimeThread::sendSignal, this), period);
}

void RealtimeThread::stop() {
  if (isAlive()) {
    keepRunning = false;
    thread->join();
    ticker.detach();
    delete thread;
    thread = 0;
  }
}

bool RealtimeThread::isAlive() {
  return thread;
}

void RealtimeThread::staticRun(RealtimeThread* realtimeThread) {
  realtimeThread->run();
}

void RealtimeThread::sendSignal(RealtimeThread* realtimeThread) {
    if (realtimeThread->thread)
      realtimeThread->thread->signal_set(realtimeThread->signal);
  }
int32_t RealtimeThread::Signal::signals = 0;

}
}
}
}
