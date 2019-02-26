#line 2 "ch/bfh/roboticsLab/yellow/RealtimeThread.h"
/* Copyright (C) BFH roboticsLab & ZHAW
 * All rights reserved.
 */

#pragma once

#include <mbed.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/**
 * This abstract class allows to install periodic real-time threads.
 * It must be sub-classed for a specific task.
 * The derived class must implement the RealtimeThread#run() method that contains the code to be executed
 * periodically. The periodic real-time thread can then be executed by instantiating an object
 * of the derived class, setting the execution period and priority, and calling its RealtimeThread#start() method.
 *
 * The following example shows how a specific real-time thread may be implemented:
 *
 * @code
 * class MyThread : public RealtimeThread {
 * public:
 *   MyThread(float period) : RealtimeThread(period) {}
 *   private:
 *     void run() {
 *       while (waitForNextPeriod()) {
 *         ...                    // code to be executed periodically at period
 *       }
 *     }
 * }
 * @endcode
 *
 * This thread can then be created and started with:
 *
 * @code
 * ...
 * // Creates an instance of MyThread with a period of 0.01 seconds, with default priority and stack size.
 * MyThread myThread(0.01);
 * myThread.start();              // starts the thread
 * ...
 * myThread.stop();               // stops the thread
 * ...
 * myThread.start();              // The thread may be restarted, if needed
 * @endcode
 *
 * The RealtimeThread implementation uses a high-priority thread by default and is
 * triggered periodically using a timer interrupt.
 *
 * @author gabriel.gruener@bfh.ch
 */
class RealtimeThread {

private:

  /**
   * This class manages the handling of unique signal flags to trigger rtos threads.
   * @author marcel.honegger@zhaw.ch
   */
  class Signal {

  public:

    /**
     * Creates a signal object and assigns it a unique flag.
     */
    Signal();

    /**
     * Deletes the signal object and releases the assigned flag.
     */
    virtual ~Signal();

    /**
     * Gets the assigned signal flag.
     * @return The assigned signal flag.
     */
    virtual inline int32_t read() {
      return signal;
    }

    /** The empty operator is a shorthand notation of the <code>read()</code> method. */
    inline operator int32_t() {
      return read();
    }

  private:

    /** variable that holds all assigned signal flags */
    static int32_t signals;
    /** signal flag of this object */
    int32_t signal;
    /** mutex to lock critical sections */
    Mutex mutex;
  };


public:

  /** Execution period of this thread [s]. */
  const float period;
  /** Execution priority of this thread. */
  const osPriority_t priority;
  /** Reserved stack size of this thread [bytes]. */
  const uint32_t stackSize;

  /**
   * Create and initialize a RealtimeThread.
   * @param period The period of this thread in seconds.
   * @param priority The priority of this thread. Defaults to osPriorityHigh.
   * @param stackSize The size of the stack to allocate for this thread. Defaults to STACK_SIZE.
   */
  RealtimeThread(const float period, const osPriority_t priority = osPriorityHigh, const uint32_t stackSize = STACK_SIZE);

  /**
   * Terminate the thread and release any allocated resources.
   */
  virtual ~RealtimeThread();

  /**
   * Start running this thread.
   * @see #stop
   */
  virtual void start();

  /**
   * Stops this thread. This method makes the #waitForNextPeriod return
   * @c false the next time it is called and waits for the run method to return.
   * @see #start
   */
  virtual void stop();

  /**
   * Tests if this thread is alive and running.
   * @return @c true if this thread is alive; @c false otherwise.
   */
  bool isAlive();

protected:

  /**
   * Performs the work of the thread.
   * This method will be called from #start and the thread will run until this method returns.
   * For periodic execution, use a while loop that checks #waitForNextPeriod every loop.
   * Refer to the usage example above.
   * @see #waitForNextPeriod
   */
  virtual void run() = 0;

  /**
   * Blocks the thread for the rest of the duration of one period.
   * @return @c false if the #stop method was called; @c true otherwise.
   */
  inline bool waitForNextPeriod() {

    if (thread && keepRunning) {
      thread->signal_wait(signal);
      return keepRunning;
    }
    return false;
  }

private:

  /** stack size of thread, given in [bytes] */
  static const uint32_t STACK_SIZE = 4096;

  /**
   * Convenience flag that stores whether the thread should keep running or stop.
   * The flag is set to @c true by #start and to @c false by #stop.
   * The flag is read in #waitForNextPeriod.
   */
  bool keepRunning;

  /** The signal to wake up this thread when the ticker commands it. */
  Signal signal;
  /** The underlying mbed-os Thread object. */
  Thread* thread;
  /** The ticker object to wake up the thread at the desired period. */
  Ticker ticker;

  /**
   * Static entry point to start running the given thread.
   * @param realtimeThread Pointer to RealtimeThread object to run.
   */
  static void staticRun(RealtimeThread* realtimeThread);

  /**
   * This method is called by the ticker timer interrupt service routine.
   * It sends a signal to the thread to continue running.
   * @see waitForNextPeriod
   */
  static void sendSignal(RealtimeThread* realtimeThread);

};

}
}
}
}
