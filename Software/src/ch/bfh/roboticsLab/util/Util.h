#line 2 "ch/bfh/roboticsLab/util/Util.h"
/* Util.h
 * Copyright (C) BFH roboticsLab
 * All rights reserved.
 */

#pragma once

namespace ch {
namespace bfh {
namespace roboticsLab {
/** This namespace contains useful utility classes and functions. */
namespace util {


/** The mathematical constant Pi. */
constexpr float PI = 3.141592653589793;

/** Number of radians in one degree. */
constexpr float RAD = PI / 180.0;

/**
 * Saturates the given value to the given min and max values.
 * @tparam T typename, must allow processing by std::min and std::max.
 * @param val The value to saturate.
 * @param min The minimum saturation value.
 * @param max The maximum saturation value.
 * @return The value, saturated if needed.
 */
template<typename T>
inline T saturate(const T& val, const T& min, const T& max) {
  return std::min(std::max(val, min), max);
}

/**
 * Unwraps the given angle in radians to be in the range [-PI .. PI].
 * @param[in] val the angle to wrap [rad].
 * @return the wrapped angle
 */
template<typename T>
inline T unwrap(const T& val) {
  T v = val;
  while (v < -PI)
    v += 2.0f * PI;
  while (v > PI)
    v -= 2.0f * PI;
  return v;
}

}
}
}
}
