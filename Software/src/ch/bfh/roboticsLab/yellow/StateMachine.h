#line 2 "ch/bfh/roboticsLab/yellow/StateMachine.h"
/* StateMachine.h
 * Copyright (c) BFH roboticsLab, ZHAW
 * All rights reserved.
 */

#pragma once

#include <ch/bfh/roboticsLab/yellow/RealtimeThread.h>
#include <ch/bfh/roboticsLab/yellow/Controller.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/** This structure defines the known states. */
struct State {
    enum Enum {
        /** OFF state: The motor controllers are disabled. */
        OFF = 0,
        /** SWITCH_ON state: The motor controllers are being enabled. */
        SWITCH_ON,
        /** SWITCH_OFF state: The motor controllers are being switched off. */
        SWITCH_OFF,
        /** ON state: The motor controllers are on. */
        ON,
        /** MANUAL state: The robot can be controlled using direct speed inputs from the user. */
        MANUAL,
        /** AUTO_REACTIVE state: The robot drives automatically straight with reactive navigation. */
        AUTO_REACTIVE,
        /** AUTO_POSITION state: The robot drives to a given goal position. */
        AUTO_POSITION,
    };
};

/**
 * This class implements the state machine of the robot controller.
 * It is an active class that uses a thread which is triggered periodically
 * by a timer interrupt.
 * @author marcel.honegger@zhaw.ch
 * @author gabriel.gruener@bfh.ch
 */
class StateMachine: public RealtimeThread {

public:

    static StateMachine& getInstance();

    /**
   * Delete the state machine object and release all allocated resources.
   */
    virtual ~StateMachine();

    /**
   * Retrieve the current state of the state machine.
   * @return the current state.
   * @see State
   */
    State::Enum getState();

    /**
   * Sets the desired state of the state machine.
   * @param stateDemand the desired state of the state machine.
   */
    void setDesiredState(State::Enum stateDemand);

    /**
   * Sets the robot's velocities for manual operation mode.
   * @param translationalVelocity the translational velocity, given in [m/s].
   * @param rotationalVelocity the rotational velocity, given in [rad/s].
   */
    void setVelocities(const float translationalVelocity, const float rotationalVelocity);

    /**
   * Sets the desired robot global pose that will be used when in the State::AUTO_POSITION.
   * @param xDesired the desired global x coordinate, given in [m].
   * @param yDesired the desired global y coordinate, given in [m].
   * @param alphaDesired the desired global alpha orientation, given in [rad].
   * @param velocity The maximum linear velocity for the motion [m/s]. Defaults to 0.2 m/s.
   * @param tolerance the radius of a circle around the goal pose where the motion is considered completed, given in [m]. Defaults to 0.02 m.
   */
    void setGoalPose(const float xDesired, const float yDesired, const float alphaDesired, const float velocity = 0.2f, const float tolerance = 0.02f);

    /**
   * Resets the timer of the watchdog.
   * This method should be called by the http server when a request was received.
   * When the watchdog timer expires, the robot stops.
   */
    void resetWatchdogTimer();

    /** Reference to Controller. */
    Controller& controller;

    /** Desired (max) translation velocity in reactive navigation. */
    float translationalProfileVelocity;
    /** minimum IR sensor distance to allow forward motion in automatic state, given in [m] */
    float minDistance;
    /** Default minimum IR sensor distance to allow forward motion in automatic state, given in [m] */
    static constexpr float MIN_DISTANCE = 0.1f;
    /** maximum IR sensor distance for forward motion in automatic state, given in [m] */
    float maxDistance;
    /** Default maximum IR sensor distance for forward motion in automatic state, given in [m] */
    static constexpr float MAX_DISTANCE = 0.4f;
    /** Rotational velocity controller gain in automatic state [rad/s /m]. */
    float rotationalVelocityGain;
    /** Default rotational velocity controller gain in automatic state [rad/s /m]. */
    static constexpr float KR = 10.0f;

    float monitor1;
    float monitor2;

private:

    /** Thread stack size, given in [bytes]. */
    static const uint32_t STACK_SIZE = 0x1000;
    /** Thread period, given in [s]. */
    static constexpr float PERIOD = 0.01f;

    /** Delay to wait for controller to switch on [s]. */
    static constexpr float SWITCH_ON_DELAY = 0.5f;
    /** Delay to wait for controller to switch off [s]. */
    static constexpr float SWITCH_OFF_DELAY = 0.5f;

    /** Watchdog timeout for State::MANUAL state.
   * @see #resetWatchdogTimer
   */
    static constexpr float WATCHDOG_TIMEOUT = 2.0f;

    /** The current state. */
    State::Enum state;
    /** The desired state for a state change request. */
    State::Enum desiredState;
    /** Saves the current state of the user button. */
    int32_t buttonNow;
    /** Saves the previous state of the user button. */
    int32_t buttonBefore;

    /** The desired translational velocity for State::MANUAL. */
    float translationalVelocity;
    /** The desired rotational velocity for State::MANUAL. */
    float rotationalVelocity;

    /** Position control constant K1. */
    static constexpr float K1 = 10.0f;
    /** Position control constant K2. */
    static constexpr float K2 = 2.0f;
    /** Position control constant K3. */
    static constexpr float K3 = 8.0f;
    /** Position control desired x [m]. */
    float xDesired;
    /** Position control desired y [m]. */
    float yDesired;
    /** Position control desired alpha [rad]. */
    float alphaDesired;
    /** Position control max linear velocity [m/s]. */
    float velocity;
    /** Position control arrival tolerance radius [m]. */
    float tolerance;
    float yDiffPrevious;
    float Iangle;

    unsigned int manuver;



    static constexpr float maxForwardVelocity = 0.5f;
    static constexpr float maxBackwardVelocity = -0.5f;
    static constexpr float maxRotationalVelocity = 4.0f;

    /** A timer used to switch states automatically based on time delays. */
    Timer timer;
    /** A watchdog timer for State::MANUAL. */
    Timer watchdogTimer;

    /**
   * Create and initialize the state machine.
   * @param controller Reference to the robot controller.
   */
    StateMachine();
    /** Private empty constructor to force usage of #getInstance. */
    StateMachine(StateMachine const&);
    /** Private equals operator to force usage of #getInstance. */
    void operator=(StateMachine const&);

    /* Implements RealtimeThread::run */
    virtual void run();
};

}
}
}
}
