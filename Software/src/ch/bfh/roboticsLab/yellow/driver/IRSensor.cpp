#line 2 "ch/bfh/roboticsLab/yellow/driver/IRSensor.cpp"
/* IRSensor.cpp
 * Copyright (c) ZHAW
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/driver/IRSensor.h>

#include <cmath>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

Multiplexer::Multiplexer(DigitalOut& bit0, DigitalOut& bit1, DigitalOut& bit2) {

  bits[0] = &bit0;
  bits[1] = &bit1;
  bits[2] = &bit2;
}

void Multiplexer::set(uint8_t index) {

  for (uint8_t i = 0; i < N; ++i)
    bits[i]->write((index >> i) & 1);
}

IRSensor::IRSensor(AnalogIn& distance, Multiplexer& multiplexer, const uint8_t number) :
    distance(distance), multiplexer(multiplexer), number(number) {

  MBED_ASSERT(number < N);
}

IRSensor::~IRSensor() {
}

float IRSensor::read() {

  multiplexer.set(number);

  // Convert distance measurment from volts to meters
  float d = -0.58f * sqrt(distance) + 0.58f;
  //float d = distance;
  return d;
}

IRSensor::operator float() {

  return read();
}
}
}
}
}
}
