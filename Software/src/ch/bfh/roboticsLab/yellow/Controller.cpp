#line 2 "ch/bfh/roboticsLab/yellow/Controller.cpp"
/* Controller.cpp
 * Copyright (c) ZHAW, BFH roboticsLab
 * All rights reserved.
 */

#include <cmath>

#include <ch/bfh/roboticsLab/yellow/Controller.h>
#include <ch/bfh/roboticsLab/yellow/Peripherals.h>
#include <ch/bfh/roboticsLab/util/Util.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

Controller& Controller::getInstance() {
  static Controller controller;
  return controller;
}

Controller::Controller() :
    RealtimeThread(PERIOD, osPriorityHigh, STACK_SIZE), translationalVelocity(0.0f), rotationalVelocity(0.0f), x(0.0f), y(0.0f), alpha(0.0f) {

  // Configure PWM
  peripherals::pwmLeft.period(0.00005f);
  peripherals::pwmLeft.write(0.5f);
  peripherals::pwmRight.period(0.00005f);
  peripherals::pwmRight.write(0.5f);

  // Initialize motion planners
  translationalMotion.setProfileVelocity(TRANSLATIONAL_PROFILE_VELOCITY);
  translationalMotion.setProfileAcceleration(1.5f);
  translationalMotion.setProfileDeceleration(3.0f);

  rotationalMotion.setProfileVelocity(ROTATIONAL_PROFILE_VELOCITY);
  rotationalMotion.setProfileAcceleration(15.0f);
  rotationalMotion.setProfileDeceleration(15.0f);

  // Initialize encoder values
  previousValueCounterLeft = peripherals::counterLeft.read();
  previousValueCounterRight = peripherals::counterRight.read();

  // Setup speed estimation low-pass filters
  speedLeftFilter.setPeriod(PERIOD);
  speedLeftFilter.setFrequency(LOWPASS_FILTER_FREQUENCY);
  speedRightFilter.setPeriod(PERIOD);
  speedRightFilter.setFrequency(LOWPASS_FILTER_FREQUENCY);
}

Controller::~Controller() {

}

void Controller::setTranslationalVelocity(float translationalVelocity) {

  this->translationalVelocity = translationalVelocity;
}

void Controller::setRotationalVelocity(float rotationalVelocity) {

  this->rotationalVelocity = rotationalVelocity;
}

void Controller::setX(float x) {

  this->x = x;
}

float Controller::getX() {

  return x;
}

void Controller::setY(float y) {

  this->y = y;
}

float Controller::getY() {

  return y;
}

void Controller::setAlpha(float alpha) {

  this->alpha = alpha;
}

float Controller::getAlpha() {

  return alpha;
}

void Controller::run() {

  while (waitForNextPeriod()) {

      // Increment motion planner for translational and rotational velocities
      translationalMotion.incrementToVelocity(translationalVelocity, period);
      rotationalMotion.incrementToVelocity(rotationalVelocity, period);

      /** TODO (Ex2.1): Use the kinematic model to calculate the desired wheel speeds in [rpm] **/
      // TODO (Ex3.1): Use the members `translationalMotion.velocity` and `rotationalMotion.velocity` to calculate the desired wheel speeds.

      float desiredSpeedLeft = 0;     // TODO: Replace with calculation
      float desiredSpeedRight = 0;    // TODO: Replace with calculation

      /** TODO (Ex2.2): Calculate the actual speed of the motors in [rpm] **/
      // TODO (Ex5.1): Use the `speedLeftFilter` & `speedRightFilter` members to filter the current wheel motor speeds.

      // TODO: Read the current encoder counts
      // TODO: Calculate the encoder counts of the last period
      // TODO: Update the "previous" encoder counts
      // TODO: Calculate the current wheel motor speeds in [rpm] ('actualSpeedLeft' & 'actualSpeedRight')
      float actualSpeedLeft = 0;
      float actualSpeedRight = 0;

      /** Calculate the voltage that needs to be applied (with closed loop P-control) **/

      // Calculate the error between the desired and the actual speed in [rpm]
      float speedErrorLeft = desiredSpeedLeft - actualSpeedLeft;
      float speedErrorRight = desiredSpeedRight - actualSpeedRight;
      // Calculate the motor phase voltages (with P-controller closed loop)
      float voltageLeft = (desiredSpeedLeft > 0.0 ? KP_POS : KP_NEG) * (speedErrorLeft) + desiredSpeedLeft / peripherals::KN;
      float voltageRight = (desiredSpeedRight > 0.0 ? KP_POS : KP_NEG) * (speedErrorRight) + desiredSpeedRight / peripherals::KN;

      /** TODO (Ex2.4): Set corresponding PWM **/

      // TODO: Calculate duty cycle
      // TODO: Limit the PWM duty cycle
      // TODO: Set the duty cycle on the corresponding PWM

      /** TODO (Ex2.5): Estimate global position from odometry **/

      // TODO: Calculate the 'actualTranslationalVelocity' and 'actualRotationalVelocity' using the kinematic model
      // TODO: Estimate the global robot pose (x, y & alpha) by integration
      // TODO: Unwrap alpha (Make sure alpha is inside the range ]-pi,pi] )
  }
}

}
}
}
}
