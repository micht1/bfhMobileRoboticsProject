#line 2 "ch/bfh/roboticsLab/yellow/driver/Servo.cpp"
/* Servo.cpp
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/driver/Servo.h>
#include <ch/bfh/roboticsLab/util/Util.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

Servo::Servo(PwmOut pwmOut, const float& range, const float& angle) :
    pwmOut(pwmOut), range(range), angle(angle) {
  write(0.5);
}

void Servo::write(const float& percent) {
  lastPercent = util::saturate(percent, 0.0f, 1.0f);
  float offset = range * (percent - 0.5);
  float v = center + offset;
  pwmOut.pulsewidth(v);
}

void Servo::position(const float& angle) {
  write(angle / this->angle);
}

float Servo::read() const {
  return lastPercent;
}

Servo& Servo::operator=(float percent) {
  write(percent);
  return *this;
}

Servo& Servo::operator=(Servo& rhs) {
  write(rhs.read());
  return *this;
}

Servo::operator float() {
  return read();
}

}
}
}
}
}
