#line 2 "ch/bfh/roboticsLab/yellow/LowpassFilter.h"
/* LowpassFilter.h
 * Copyright (c) ZHAW
 * All rights reserved.
 */

#pragma once

#include <cstdlib>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/**
 * This class implements a time-discrete 2nd-order low-pass filter for a series of data values.
 * This filter can typically be used within a periodic task that takes measurements that need
 * to be filtered, like speed or position values.
 *
 * The filtered value can be retrieved by calling the method #filter.
 *
 * @author marcel.honegger@zhaw.ch
 */
class LowpassFilter {

public:

  /**
   * Creates a LowpassFilter object with a default cutoff frequency of 1000 [rad/s].
   */
  LowpassFilter();

  /**
   * Deletes the LowpassFilter object.
   */
  virtual ~LowpassFilter();

  /**
   * Resets the filtered value to zero.
   */
  void reset();

  /**
   * Resets the filtered value to a given value.
   * @param value the value to reset the filter to.
   */
  void reset(float value);

  /**
   * Sets the sampling period of the filter.
   * This is typically the sampling period of the periodic task of a controller that uses this filter.
   * @param the sampling period, given in [s].
   */
  void setPeriod(float period);

  /**
   * Sets the cutoff frequency of this filter.
   * @param frequency the cutoff frequency of the filter in [rad/s].
   */
  void setFrequency(float frequency);

  /**
   * Gets the current cutoff frequency of this filter.
   * @return the current cutoff frequency in [rad/s].
   */
  float getFrequency();

  /**
   * Filters a value.
   * @param value the original unfiltered value.
   * @return the filtered value.
   */
  float filter(float value);

private:

  /**
   * Update the low-pass parameters of the filter.
   * Call this method after modifying period or frequency.
   */
  void update();

  float period;
  float frequency;
  float a11, a12, a21, a22, b1, b2;
  float x1, x2;
};

}
}
}
}
