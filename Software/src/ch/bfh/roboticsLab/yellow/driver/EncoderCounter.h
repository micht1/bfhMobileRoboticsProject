#line 2 "ch/bfh/roboticsLab/yellow/driver/EncoderCounter.h"
/* EncoderCounter.h
 * Copyright (c) ZHAW
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
 * This class implements a driver to read the quadrature
 * encoder counter of the STM32 microcontroller.
 *
 * @author marcel.honegger@zhaw.ch
 * @author gabriel.gruener@bfh.ch
 */
class EncoderCounter {

public:

  /**
   * Creates and initializes the driver to read the quadrature encoder counter of the STM32 microcontroller.
   * @param a the input pin for the encoder's channel A.
   * @param b the input pin for the encoder's channel B.
   */
  EncoderCounter(const PinName a, const PinName b);

  virtual ~EncoderCounter();

  /** Resets the counter value to zero. */
  void reset();

  /**
   * Resets the counter value to a given offset value.
   * @param offset the offset value to reset the counter to.
   */
  void reset(const int16_t offset);

  /**
   * Reads the quadrature encoder counter value.
   * @return the quadrature encoder counter as a signed 16-bit integer value.
   */
  int16_t read();

  /**
   * The empty operator is a shorthand notation of the <code>read()</code> method.
   */
  operator int16_t();

private:

  /** The HW timer to use to read the encoder counter. */
  TIM_TypeDef* TIM;
};

}
}
}
}
}
