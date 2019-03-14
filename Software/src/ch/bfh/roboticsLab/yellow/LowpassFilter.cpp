#line 2 "ch/bfh/roboticsLab/yellow/LowpassFilter.cpp"
/* LowpassFilter.cpp
 * Copyright (c) ZHAW
 * All rights reserved.
 */

#include <cmath>
#include <ch/bfh/roboticsLab/yellow/LowpassFilter.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

LowpassFilter::LowpassFilter() :
    period(1.0f), frequency(1000.0f) {

  update();
  reset();
}

LowpassFilter::~LowpassFilter() {
}

void LowpassFilter::update() {

  a11 = (1.0f + frequency * period) * exp(-frequency * period);
  a12 = period * exp(-frequency * period);
  a21 = -frequency * frequency * period * exp(-frequency * period);
  a22 = (1.0f - frequency * period) * exp(-frequency * period);
  b1 = (1.0f - (1.0f + frequency * period) * exp(-frequency * period)) / frequency / frequency;
  b2 = period * exp(-frequency * period);
}

void LowpassFilter::reset() {

  x1 = 0.0f;
  x2 = 0.0f;
}

void LowpassFilter::reset(float value) {

  x1 = value / frequency / frequency;
  x2 = (x1 - a11 * x1 - b1 * value) / a12;
}

void LowpassFilter::setPeriod(float period) {

  this->period = period;
  update();
}

void LowpassFilter::setFrequency(float frequency) {

  this->frequency = frequency;
  update();
}

float LowpassFilter::getFrequency() {

  return frequency;
}

float LowpassFilter::filter(float value) {

  float x1old = x1;
  float x2old = x2;

  x1 = a11 * x1old + a12 * x2old + b1 * value;
  x2 = a21 * x1old + a22 * x2old + b2 * value;

  return frequency * frequency * x1;
}

}
}
}
}
