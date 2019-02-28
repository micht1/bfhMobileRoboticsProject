#line 2 "ch/bfh/roboticsLab/yellow/Motion.h"
/* Motion.h
 * Copyright (C) ZHAW
 * All rights reserved.
 */

#pragma once

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/**
 * This class keeps the motion values <code>position</code> and <code>velocity</code>, and
 * offers methods to increment these values towards a desired target position or velocity.
 * <br/>
 * To increment the current motion values, this class uses a simple 2nd order motion planner.
 * This planner calculates the motion to the target position or velocity with the various motion
 * phases, based on given limits for the profile velocity, acceleration and deceleration.
 * <br/>
 * Note that the trajectory is calculated every time the motion state is incremented.
 * This allows to change the target position or velocity, as well as the limits for profile
 * velocity, acceleration and deceleration at any time.
 *
 * @author marcel.honegger@bfh.ch
 */
class Motion {

public:

    double position; /**< The position value of this motion, given in [m] or [rad]. */
    float velocity; /**< The velocity value of this motion, given in [m/s] or [rad/s]. */
    float acceleration; /**< The acceleration value of this motion, given in [m/s&sup2;] or [rad/s&sup2;]. */

    /**
   * Creates a <code>Motion</code> object.
   * The values for position, velocity and acceleration are set to 0.
   */
    Motion();

    /**
   * Creates a <code>Motion</code> object with given values for position and velocity.
   * @param position the initial position value of this motion, given in [m] or [rad].
   * @param velocity the initial velocity value of this motion, given in [m/s] or [rad/s].
   */
    Motion(double position, float velocity);

    /**
   * Creates a <code>Motion</code> object with given values for position, velocity and acceleration.
   * @param position the initial position value of this motion, given in [m] or [rad].
   * @param velocity the initial velocity value of this motion, given in [m/s] or [rad/s].
   * @param acceleration the initial acceleration value of this motion, given in [m/s&sup2;] or [rad/s&sup2;].
   */
    Motion(double position, float velocity, float acceleration);

    /**
   * Creates a <code>Motion</code> object with given values for position and velocity.
   * @param motion another <code>Motion</code> object to copy the values from.
   */
    Motion(const Motion& motion);

    virtual ~Motion();

    /**
   * Sets the values for position and velocity.
   * @param position the desired position value of this motion, given in [m] or [rad].
   * @param velocity the desired velocity value of this motion, given in [m/s] or [rad/s].
   */
    void set(double position, float velocity);

    /**
   * Sets the values for position, velocity and acceleration.
   * @param position the desired position value of this motion, given in [m] or [rad].
   * @param velocity the desired velocity value of this motion, given in [m/s] or [rad/s].
   * @param acceleration the desired acceleration value of this motion, given in [m/s&sup2;] or [rad/s&sup2;].
   */
    void set(double position, float velocity, float acceleration);

    /**
   * Sets the values for position, velocity and acceleration.
   * @param motion another <code>Motion</code> object to copy the values from.
   */
    void set(const Motion& motion);

    /**
   * Sets the position value.
   * @param position the desired position value of this motion, given in [m] or [rad].
   */
    void setPosition(double position);

    /**
   * Gets the position value.
   * @return the position value of this motion, given in [m] or [rad].
   */
    double getPosition();

    /**
   * Sets the velocity value.
   * @param velocity the desired velocity value of this motion, given in [m/s] or [rad/s].
   */
    void setVelocity(float velocity);

    /**
   * Gets the velocity value.
   * @return the velocity value of this motion, given in [m/s] or [rad/s].
   */
    float getVelocity();

    /**
   * Sets the acceleration value.
   * @param acceleration the desired acceleration value of this motion, given in [m/s&sup2;] or [rad/s&sup2;].
   */
    void setAcceleration(float acceleration);

    /**
   * Gets the acceleration value.
   * @return the acceleration value of this motion, given in [m/s&sup2;] or [rad/s&sup2;].
   */
    float getAcceleration();

    /**
   * Sets the limit for the velocity value.
   * @param profileVelocity the limit of the velocity.
   */
    void setProfileVelocity(float profileVelocity);

    /**
   * Sets the limit for the acceleration value.
   * @param profileAcceleration the limit of the acceleration.
   */
    void setProfileAcceleration(float profileAcceleration);

    /**
   * Sets the limit for the deceleration value.
   * @param profileDeceleration the limit of the deceleration.
   */
    void setProfileDeceleration(float profileDeceleration);

    /**
   * Sets the limits for velocity, acceleration and deceleration values.
   * @param profileVelocity the limit of the velocity.
   * @param profileAcceleration the limit of the acceleration.
   * @param profileDeceleration the limit of the deceleration.
   */
    void setLimits(float profileVelocity, float profileAcceleration, float profileDeceleration);

    /**
   * Gets the time needed to move to a given target position.
   * @param targetPosition the desired target position given in [m] or [rad].
   * @return the time to move to the target position, given in [s].
   */
    float getTimeToPosition(double targetPosition);

    /**
   * Gets the distance moved until the velocity reaches zero.
   * @return the distance to the stop position.
   */
    double getDistanceToStop();

    /**
   * Increments the current motion towards a given target velocity.
   * @param targetVelocity the desired target velocity given in [m/s] or [rad/s].
   * @param period the time period to increment the motion values for, given in [s].
   */
    void incrementToVelocity(float targetVelocity, float period);

    /**
   * Increments the current motion towards a given target position.
   * @param targetPosition the desired target position given in [m] or [rad].
   * @param period the time period to increment the motion values for, given in [s].
   */
    void incrementToPosition(double targetPosition, float period);

private:

    /** default value for limits */
    static const float DEFAULT_LIMIT;
    /** smallest value allowed for limits */
    static const float MINIMUM_LIMIT;

    /** Used profile velocity */
    float profileVelocity;
    /** Used profile acceleration */
    float profileAcceleration;
    /** Used profile deceleration */
    float profileDeceleration;
};
}
}
}
}
