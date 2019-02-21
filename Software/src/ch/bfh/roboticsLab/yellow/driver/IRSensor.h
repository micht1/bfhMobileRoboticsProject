#line 2 "ch/bfh/roboticsLab/yellow/driver/IRSensor.h"
/* IRSensor.h
 * Copyright (c) ZHAW, BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <mbed.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

/**
 * This class implements the interface to a hardware multiplexer.
 * The current implementaiton works for a 3-bit multiplexer.
 *
 * @author gabriel.gruener@bfh.ch
 */
class Multiplexer {

public:

  /** Number of multiplexer bits. */
  static const uint8_t N = 3;

  /**
   * Create a new Multiplexer using the 3 given digital outputs to control the multiplexer.
   * @param bit0 a digital output to set the first bit of the multiplexer.
   * @param bit1 a digital output to set the second bit of the multiplexer.
   * @param bit2 a digital output to set the third bit of the multiplexer.
   */
  Multiplexer(DigitalOut& bit0, DigitalOut& bit1, DigitalOut& bit2);

  virtual ~Multiplexer() {
  }

  /**
   * Sets the multiplexer to the given index.
   * Since this implementation is for a 3-bit multiplexer,
   * note that only the lowest 3 significant bits of @c index will be used.
   * @param index The desired multiplexer setting.
   */
  inline void set(uint8_t index);

private:
  /** Array of pointers to the digital outputs controlling the multiplexer. */
  DigitalOut* bits[N];
};

/**
 * This is a device driver class to read the distance measured with the Sharp IR sensors.
 * @author marcel.honegger@zhaw.ch
 */
class IRSensor {

public:
  /** The number of IR sensors supported. */
  static const uint8_t N = 6;

  /**
   * Creates an IRSensor object.
   * @param distance Reference to an analog input object to read the voltage of the sensor from.
   * @param multiplexer Reference to a Multiplexer object that controls the input to read.
   * @param number The multiplexer index for the sensor to read. Must be in the range from 0 to #N-1.
   */
  IRSensor(AnalogIn& distance, Multiplexer& multiplexer, const uint8_t number);

  /**
   * Deletes the IRSensor object.
   */
  virtual ~IRSensor();

  /**
   * Gets the distance measured with the IR sensor in [m].
   * @return the distance, given in [m].
   */
  float read();

  /**
   * The empty operator is a shorthand notation of the <code>read()</code> method.
   */
  operator float();

private:
  /** Reference to analog input to read. */
  AnalogIn& distance;
  /** Reference to Multiplexer. */
  Multiplexer& multiplexer;
  /** The multiplexer index of this sensor. */
  const uint16_t number;
};

}
}
}
}
}
