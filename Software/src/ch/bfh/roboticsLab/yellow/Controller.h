#line 2 "ch/bfh/roboticsLab/yellow/Controller.h"
/* Controller.h
 * Copyright (c) ZHAW & BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <mbed.h>
#include <ch/bfh/roboticsLab/yellow/RealtimeThread.h>
#include <ch/bfh/roboticsLab/yellow/Console.h>
#include <ch/bfh/roboticsLab/yellow/Motion.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/**
 * This class implements the robot controller.
 * It is an active class that uses a high priority real-time thread.
 *
 * @author marcel.honegger@zhaw.ch
 * @author gabriel.gruener@bfh.ch
 */
class Controller: public RealtimeThread {

public:

  /** Translational velocity for profiled motion planner [m/s]. */
  static constexpr float TRANSLATIONAL_PROFILE_VELOCITY = 1.5f;
  /** Rotational velocity for profiled motion planner [rad/s]. */
  static constexpr float ROTATIONAL_PROFILE_VELOCITY = 3.0f;

  static Controller& getInstance();

  virtual ~Controller();

  /**
   * Sets the desired translational velocity of the robot.
   * @param translationalVelocity the translational velocity, given in [m/s].
   */
  void setTranslationalVelocity(float translationalVelocity);

  /**
   * Sets the desired rotational velocity of the robot.
   * @param rotationalVelocity the rotational velocity, given in [rad/s].
   */
  void setRotationalVelocity(float rotationalVelocity);

  /**
   * Sets the x coordinate of the robot's global pose.
   * Use this method to correct the estimated odometry value.
   * @param x the x coordinate of the global pose, given in [m].
   */
  void setX(float x);

  /**
   * Gets the estimated x coordinate of the robot's global pose.
   * @return the x coordinate of the global pose, given in [m].
   */
  float getX();

  /**
   * Sets the y coordinate of the robot's global pose.
   * Use this method to correct the estimated odometry value.
   * @param y the y coordinate of the global pose, given in [m].
   */
  void setY(float y);

  /**
   * Gets the estimated y coordinate of the robot's global pose.
   * @return the y coordinate of the global pose, given in [m].
   */
  float getY();

  /**
   * Sets the alpha coordinate of the robot's global pose.
   * Use this method to correct the estimated odometry value.
   * @param alpha the alpha coordinate of the global pose, given in [rad].
   */
  void setAlpha(float alpha);

  /**
   * Gets the estimated y coordinate of the robot's global pose.
   * @return the y coordinate of the global pose, given in [rad].
   */
  float getAlpha();

  float monitor1;
  float monitor2;

private:

  /** The default period of the this real-time thread [s] */
  static constexpr float PERIOD = 0.001f;
  /** stack size of thread, given[bytes] */
  static constexpr uint32_t STACK_SIZE = 0x1000;

  /***   Robot kinematic model   ***/
  /** distance between wheels, given in [m] */
  static constexpr float WHEEL_DISTANCE = 0.18f;
  /** radius of wheels, given in [m] */
  static constexpr float WHEEL_RADIUS = 0.0375f;

  /** Speed controller proportional gain [V/rpm] */
  static constexpr float KP_POS = 0.2f;
  static constexpr float KP_NEG = 0.1f;

  /** Motion planner for translation */
  Motion translationalMotion;
  /** Motion planner for rotation */
  Motion rotationalMotion;
  /** Estimated current translational velocity [m/s] */
  float translationalVelocity;
  /** Estimated current rotational velocity [rad/s] */
  float rotationalVelocity;
  /** Left encoder count at previous loop [counts] */
  int16_t previousValueCounterLeft;
  /** Right encoder count at previous loop [counts] */
  int16_t previousValueCounterRight;

  /** Estimated global x [m]. */
  float x;
  /** Estimated global y [m]. */
  float y;
  /** Estimated global alpha [rad]. */
  float alpha;

  /** Create and initialize the robot controller object. */
  Controller();
  /** Private empty constructor to force usage of #getInstance. */
  Controller(Controller const&);
  /** Private equals operator to force usage of #getInstance. */
  void operator=(Controller const&);

  /* Implements RealtimeThread::run */
  virtual void run();
};

}
}
}
}
