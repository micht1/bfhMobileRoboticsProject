#line 2 "ch/bfh/roboticsLab/yellow/Controller.cpp"
/* Controller.cpp
 * Copyright (c) ZHAW, BFH roboticsLab
 * All rights reserved.
 */

#include <cmath>

#include <ch/bfh/roboticsLab/yellow/Console.h>


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
    RealtimeThread(PERIOD, osPriorityHigh, STACK_SIZE), translationalVelocity(0.0f), rotationalVelocity(0.0f),totalErrorLeft(0.0f),totalErrorRight(0.0f),oldVelocityLeft(0.0f),oldVelocityRight(0.0f), x(0.0f), y(0.0f),alpha(0.0f){

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

      float desiredSpeedLeft = ((translationalMotion.velocity-WHEEL_DISTANCE/2*rotationalMotion.velocity)/(WHEEL_RADIUS*2*M_PI))*60.0f;     // TODO: Replace with calculation
      float desiredSpeedRight = ((translationalMotion.velocity+WHEEL_DISTANCE/2*rotationalMotion.velocity)/(WHEEL_RADIUS*2*M_PI))*60.0f;     // TODO: Replace with calculation

      /** calculate the acutal speed of the Wheels. Encoder data is read and in combination with the
       * Thread Executiontime  the speeds can be calculated **/
      int16_t encoderCountsLeft = peripherals::counterLeft.read();
      int16_t encoderCountsRight = peripherals::counterRight.read();
      float actualSpeedLeft = ((encoderCountsLeft-previousValueCounterLeft)/(PERIOD*peripherals::COUNTS_PER_TURN))*60.0f;
      float actualSpeedRight = -((encoderCountsRight-previousValueCounterRight)/(PERIOD*peripherals::COUNTS_PER_TURN))*60.0f;
      previousValueCounterLeft = encoderCountsLeft;
      previousValueCounterRight = encoderCountsRight;
      /** code strucktur to prevent an encoder overflow from disrupting odometrie. **/
      if(abs(oldVelocityLeft-actualSpeedLeft)>1500)
      {
        actualSpeedLeft = oldVelocityLeft;
      }
      else
      {
        oldVelocityLeft= actualSpeedLeft;
      }
      if(abs(oldVelocityRight-actualSpeedRight)>1500)
      {
         actualSpeedRight = oldVelocityRight;
      }
      else
      {
        oldVelocityRight=actualSpeedRight;
      }
      /** filter speed with given filter method **/
      actualSpeedLeft=Controller::speedLeftFilter.filter(actualSpeedLeft);
      actualSpeedRight=Controller::speedRightFilter.filter(actualSpeedRight);

      /** Calculate the voltage that needs to be applied (with closed loop P-control) **/
      // Calculate the error between the desired and the actual speed in [rpm]
      float speedErrorLeft = desiredSpeedLeft - actualSpeedLeft;
      float speedErrorRight = desiredSpeedRight - actualSpeedRight;
      /**Code snipped of not implemented I-Part of Controller */
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
      }*/

      // Calculate the motor phase voltages (with P-controller closed loop)
      float voltageLeft = (desiredSpeedLeft > 0.0 ? KP_POS : KP_NEG) * (speedErrorLeft) + desiredSpeedLeft / peripherals::KN;//+Ki*totalErrorLeft;
      float voltageRight = (desiredSpeedRight > 0.0 ? KP_POS : KP_NEG) * (speedErrorRight) + desiredSpeedRight / peripherals::KN;//+Ki*totalErrorRight;
      /*
        * PWM calculation. The Motors used +-12V -> to scale it to 0.5 the calculated voltage need to be divided by 24
        * Pwm Method of motor drives takes a 0 - 1 PWM. 0.5 is stop ->desiredPWM need to be shifted by 0.5
        */
       float desiredPwmLeft=voltageLeft/24.0f+0.5;
       if(desiredPwmLeft>=peripherals::MAX_DUTY_CYCLE)
       {
           desiredPwmLeft=peripherals::MAX_DUTY_CYCLE;
       }
       else if(desiredPwmLeft<=peripherals::MIN_DUTY_CYCLE)
       {
           desiredPwmLeft=peripherals::MIN_DUTY_CYCLE;
       }



       float desiredPwmRight=(-voltageRight)/24.0f+0.5; // voltage is negative since the weelmotor is mirrored
       //limit the PWM so it is in the range of the driver method
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



      // calculates the speed of the robot with the encoder data
      float actualTranslationVelocity = (0.5f*(actualSpeedLeft+actualSpeedRight)*2*WHEEL_RADIUS*M_PI)/60.0f;
      float actualRotationVelocity = (1/(WHEEL_DISTANCE)*((actualSpeedRight-actualSpeedLeft)*2*WHEEL_RADIUS*M_PI))/60.0f;
      /*if(abs(actualRotationVelocity)>1.5f)
      {
          actualRotationVelocity=oldRotationalVelocity;
      }
      else if(abs(actualTranslationVelocity)<1.5f)
      {
        oldRotationalVelocity=actualRotationVelocity;
      }*/

      // Estimate the global robot pose (x, y & alpha) by integration
      x = x + cos(alpha+actualRotationVelocity*PERIOD)*actualTranslationVelocity*PERIOD;
      y = y + sin(alpha+actualRotationVelocity*PERIOD)*actualTranslationVelocity*PERIOD;

      alpha = alpha+actualRotationVelocity*PERIOD;
      // Unwrap alpha (Make sure alpha is inside the range ]-pi,pi] )
      alpha = util::unwrap(alpha);


  }
}

}
}
}
}
