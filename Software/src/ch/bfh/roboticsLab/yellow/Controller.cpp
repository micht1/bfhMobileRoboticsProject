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
    RealtimeThread(PERIOD, osPriorityHigh, STACK_SIZE), translationalVelocity(0.0f), rotationalVelocity(0.0f), x(0.0f), y(0.0f), totalErrorLeft(0),totalErrorRight(0),alpha(0.0f) {

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

      float desiredSpeedLeft = ((translationalMotion.velocity-WHEEL_DISTANCE/2*rotationalMotion.velocity)/(WHEEL_RADIUS*2*M_PI))*60.0f;     // TODO: Replace with calculation
      float desiredSpeedRight = ((translationalMotion.velocity+WHEEL_DISTANCE/2*rotationalMotion.velocity)/(WHEEL_RADIUS*2*M_PI))*60.0f;     // TODO: Replace with calculation

      /** TODO (Ex2.2): Calculate the actual speed of the motors in [rpm] **/

      // TODO: Read the current encoder counts
      // TODO: Calculate the encoder counts of the last period
      // TODO: Update the "previous" encoder counts
      // TODO: Calculate the current wheel motor speeds in [rpm] ('actualSpeedLeft' & 'actualSpeedRight')
      float encoderCountsLeft = peripherals::counterLeft.read();
      float encoderCountsRight = peripherals::counterRight.read();
      float actualSpeedLeft = ((encoderCountsLeft-previousValueCounterLeft)/(PERIOD*peripherals::COUNTS_PER_TURN))*60.0f;
      float actualSpeedRight = -((encoderCountsRight-previousValueCounterRight)/(PERIOD*peripherals::COUNTS_PER_TURN))*60.0f;
      previousValueCounterLeft = encoderCountsLeft;
      previousValueCounterRight = encoderCountsRight;

      //Counter overflow might lead to undefined behaviour

      /** Calculate the voltage that needs to be applied (with closed loop P-control) **/
      // Calculate the error between the desired and the actual speed in [rpm]
      float speedErrorLeft = desiredSpeedLeft - actualSpeedLeft;
      float speedErrorRight = desiredSpeedRight - actualSpeedRight;
      /*
      totalErrorLeft += speedErrorLeft;
      totalErrorRight +=speedErrorRight;
      if(totalErrorLeft>=maxError)
      {
          totalErrorLeft=maxError;
      }
      else if(totalErrorLeft<=-maxError)
      {
          totalErrorLeft=-maxError;
      }
      if(totalErrorRight>=maxError)
      {
          totalErrorRight=maxError;
      }
      else if(totalErrorRight<=-maxError)
      {
          totalErrorRight=-maxError;
      }
      */
      // Calculate the motor phase voltages (with P-controller closed loop)
      float voltageLeft = (desiredSpeedLeft > 0.0 ? KP_POS : KP_NEG) * (speedErrorLeft) + desiredSpeedLeft / peripherals::KN;//+Ki*totalErrorLeft;
      float voltageRight = (desiredSpeedRight > 0.0 ? KP_POS : KP_NEG) * (speedErrorRight) + desiredSpeedRight / peripherals::KN;//+Ki*totalErrorRight;
      /** TODO (Ex2.4): Set corresponding PWM **/

      // TODO: Calculate duty cycle
      // TODO: Limit the PWM duty cycle
      // TODO: Set the duty cycle on the corresponding PWM
       float desiredPwmLeft=voltageLeft/24.0f+0.5;
       if(desiredPwmLeft>=peripherals::MAX_DUTY_CYCLE)
       {
           desiredPwmLeft=peripherals::MAX_DUTY_CYCLE;
       }
       else if(desiredPwmLeft<=peripherals::MIN_DUTY_CYCLE)
       {
           desiredPwmLeft=peripherals::MIN_DUTY_CYCLE;
       }

       //desiredPwmLeft = ((desiredPwmLeft < peripherals::MIN_DUTY_CYCLE ? peripherals::MIN_DUTY_CYCLE : desiredPwmLeft));

       float desiredPwmRight=(-voltageRight)/24.0f+0.5;
       if(desiredPwmRight>=peripherals::MAX_DUTY_CYCLE)
       {
           desiredPwmRight=peripherals::MAX_DUTY_CYCLE;
       }
       else if(desiredPwmRight<=peripherals::MIN_DUTY_CYCLE)
       {
           desiredPwmRight=peripherals::MIN_DUTY_CYCLE;
       }
       //desiredPwmRight = ((desiredPwmRight < peripherals::MIN_DUTY_CYCLE ? peripherals::MIN_DUTY_CYCLE : desiredPwmRight));

       peripherals::pwmLeft.write(desiredPwmLeft);
       peripherals::pwmRight.write(desiredPwmRight);



      /** TODO (Ex2.5): Estimate global position from odometry **/

      // TODO: Calculate the 'actualTranslationalVelocity' and 'actualRotationalVelocity' using the kinematic model
      float actualTranslationVelocity = (0.5f*(actualSpeedLeft+actualSpeedRight)*2*WHEEL_RADIUS*M_PI)/60.0f;
      float actualRotationVelocity = (1/(WHEEL_DISTANCE)*((actualSpeedRight-actualSpeedLeft)*2*WHEEL_RADIUS*M_PI))/60.0f;

      // TODO: Estimate the global robot pose (x, y & alpha) by integration
      x = x + cos(alpha+actualRotationVelocity*PERIOD)*actualTranslationVelocity*PERIOD;
      y = y + sin(alpha+actualRotationVelocity*PERIOD)*actualTranslationVelocity*PERIOD;
      monitor1 = x;
      monitor2 = y;
      alpha = alpha+actualRotationVelocity*PERIOD;
     if(abs((fmod(alpha,2*M_PI)))>M_PI){
        alpha = -M_PI-(M_PI-fmod(alpha,2*M_PI));
     }
     else{
        alpha = fmod(alpha,2*M_PI);
     }


      // TODO: Unwrap alpha (Make sure alpha is inside the range ]-pi,pi] )

  }
}

}
}
}
}
