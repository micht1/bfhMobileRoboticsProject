#line 2 "ch/bfh/roboticsLab/yellow/StateMachine.cpp"
/* StateMachine.cpp
 * Copyright (c) BFH roboticsLab, ZHAW
 * All rights reserved.
 */

#include <algorithm>

#include <ch/bfh/roboticsLab/yellow/StateMachine.h>
#include <ch/bfh/roboticsLab/yellow/Peripherals.h>
#include <ch/bfh/roboticsLab/util/Util.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

StateMachine& StateMachine::getInstance() {
    static StateMachine stateMachine;
    return stateMachine;
}

StateMachine::StateMachine()
    : RealtimeThread(PERIOD, osPriorityAboveNormal, STACK_SIZE),
      controller(Controller::getInstance()),
      translationalProfileVelocity(Controller::TRANSLATIONAL_PROFILE_VELOCITY),
      minDistance(MIN_DISTANCE),
      maxDistance(MAX_DISTANCE),
      rotationalVelocityGain(KR),
      state(State::OFF),
      desiredState(State::OFF),
      buttonNow(peripherals::userButton),
      buttonBefore(buttonNow),
      translationalVelocity(0.0f),
      rotationalVelocity(0.0f),
      xDesired(0.0f),
      yDesired(0.0f),
      alphaDesired(0.0f),
      velocity(0.2),
      tolerance(0.02)
{
    peripherals::enableMotorDriver = 0;

    timer.start();
    watchdogTimer.start();
}

StateMachine::~StateMachine() {
}

State::Enum StateMachine::getState() {

    return state;
}

void StateMachine::setDesiredState(State::Enum desiredState) {

    // Note SWITCH_ON and SWITCH_OFF are transitory states and should not be selected by the user.
    if (desiredState != State::SWITCH_ON && desiredState != State::SWITCH_OFF)
        this->desiredState = desiredState;
}

void StateMachine::setVelocities(const float translationalVelocity, const float rotationalVelocity) {

    this->translationalVelocity = translationalVelocity;
    this->rotationalVelocity = rotationalVelocity;
}

void StateMachine::setGoalPose(const float xDesired, const float yDesired, const float alphaDesired, const float velocity, const float tolerance) {

    this->xDesired = xDesired;
    this->yDesired = yDesired;
    this->alphaDesired = alphaDesired;
    this->velocity = velocity;
    this->tolerance = tolerance;
}

void StateMachine::resetWatchdogTimer() {

    watchdogTimer.reset();
}

void StateMachine::run() {

    peripherals::enableIRSensors = 1;
    float distance[peripherals::N_IRs];

    while (waitForNextPeriod()) {

        /* TODO (Ex3.2): Read the IR sensors & activate the corresponding LED
         * Read the IR sensors and fill the `distance` array.
         * Turn on and off the corresponding LED.
         * NOTE: Use the member variables `minDistance` / `maxDistance`.
         * NOTE: Use your code from Ex1.4 & 1.5.
         */
        peripherals::enableIRSensors = 1;

        for(int cnt = 0; cnt <peripherals::N_IRs; ++cnt){
            distance[cnt]=peripherals::irSensors[cnt];  //.read();

            if(distance[cnt] <= minDistance){
                peripherals::irLEDs[cnt] = 1;
            }
            else if(distance[cnt]>=maxDistance){
                peripherals::irLEDs[cnt] = 0;
            }
        }

        // handle state machine
        switch (state) {

        case State::OFF:

            buttonNow = peripherals::userButton;
            if (buttonNow && !buttonBefore)
                desiredState = State::AUTO_REACTIVE;

            if (desiredState >= State::ON) {

                peripherals::enableMotorDriver = 1;
                timer.reset();

                state = State::SWITCH_ON;
            }

            buttonBefore = buttonNow;

            break;

        case State::SWITCH_ON:

            if (desiredState == State::OFF) {

                controller.setTranslationalVelocity(0.0f);
                controller.setRotationalVelocity(0.0f);
                timer.reset();

                state = State::SWITCH_OFF;

            } else if (timer.read() > SWITCH_ON_DELAY) {

                controller.start();
                peripherals::led = 1;
                state = State::ON;
            }

            break;

        case State::ON:

            if (desiredState == State::OFF) {

                controller.setTranslationalVelocity(0.0f);
                controller.setRotationalVelocity(0.0f);
                timer.reset();

                peripherals::led = 0;
                state = State::SWITCH_OFF;

            } else if (desiredState == State::MANUAL) {

                state = State::MANUAL;

            } else if (desiredState == State::AUTO_REACTIVE) {

                state = State::AUTO_REACTIVE;

            } else if (desiredState == State::AUTO_POSITION) {

                state = State::AUTO_POSITION;
            }

            break;

        case State::SWITCH_OFF:

            if (timer.read() > SWITCH_OFF_DELAY) {

                peripherals::enableMotorDriver = 0;
                controller.stop();

                state = State::OFF;
            }

            break;

        case State::MANUAL:

            if (desiredState <= State::ON) {

                controller.setTranslationalVelocity(0.0f);
                controller.setRotationalVelocity(0.0f);

                state = State::ON;

            } else {

                /* TODO (Ex3.3): Complete the MANUAL state
                 * Let Yellow drive at the desired translational / rotational velocities.
                 */
                controller.setTranslationalVelocity(translationalVelocity);
                controller.setRotationalVelocity(rotationalVelocity);
            }

            break;

        case State::AUTO_REACTIVE:

            buttonNow = peripherals::userButton;
            if (buttonNow && !buttonBefore)
                desiredState = State::OFF;

            if (desiredState <= State::ON) {

                controller.setTranslationalVelocity(0.0f);
                controller.setRotationalVelocity(0.0f);

                state = State::ON;

            } else {

                /* TODO (Ex3.4): Implement Reactive navigation
                 * Set the translational and rotational velocity based on the distances to an obstacle.
                 * NOTE: Use the `distance` array created and filled (Ex3.2) at the beginning of this `StateMachine::run` method.
                 * NOTE: Again, use the member variables `minDistance` / `maxDistance`.
                 * Request desired velocities to the controller.
                 */
                if(distance[0]>=maxDistance && distance[1]>=maxDistance && distance[5]>=maxDistance){
                    controller.setTranslationalVelocity(maxForwardVelocity);
                    controller.setRotationalVelocity(0.0f);
                }
                else if(distance[0]<=minDistance || distance[1]<=minDistance || distance[5]<=minDistance){
                    controller.setTranslationalVelocity(maxBackwardVelocity);
                    controller.setRotationalVelocity(0.0f);
                }
                else {
                    controller.setTranslationalVelocity(maxForwardVelocity*(distance[0]/maxDistance)*(distance[1]+distance[5])/(2.0f*maxDistance));
                    if(abs(distance[1]-distance[5])>0.05){
                        controller.setRotationalVelocity(maxRotationalVelocity*((distance[5]/maxDistance)-(distance[1]/maxDistance)));
                    }
                    else {
                        controller.setRotationalVelocity(0.0f);
                    }
                }
            }

            buttonBefore = buttonNow;
            break;

        case State::AUTO_POSITION:

            if (desiredState <= State::ON) {

                controller.setTranslationalVelocity(0.0f);
                controller.setRotationalVelocity(0.0f);

                state = State::ON;

            } else {

                /* TODO (Ex3.5): Implement position control (Step-wise maneuver)
                 * Use a step-wise maneuver to drive the robot to a desired pose.
                 * Rotate the robot so that its forward direction is oriented towards the goal position.
                 * Translate straight ahead to the goal position.
                 * Rotate the robot to the goal orientation.
                 */

                float distanceToTarget=sqrt((this->xDesired-controller.getX())*(this->xDesired-controller.getX())+(this->yDesired-controller.getY())*(this->yDesired-controller.getY()));
                float angleToTargetPos=atan2f(this->yDesired-controller.getY(),this->xDesired-controller.getX())-controller.getAlpha();
                float angleCorrection=angleToTargetPos+controller.getAlpha()-this->alphaDesired;

                if(abs(distanceToTarget)>0.001f){
                controller.setTranslationalVelocity(K1*distanceToTarget*cosf(angleToTargetPos));
                }
                if(abs(angleToTargetPos)>0.001f){
                controller.setRotationalVelocity(K2*angleToTargetPos+K1*sinf(angleToTargetPos)*cosf(angleToTargetPos)*((angleToTargetPos+K3*angleCorrection)/angleToTargetPos));
                }



                if(sqrt((this->xDesired-controller.getX())*(this->xDesired-controller.getX())+(this->yDesired-controller.getY())*(this->yDesired-controller.getY()))<this->tolerance)
                {
                    if(abs(this->alphaDesired)>=M_PI-0.05){
                        if(abs(controller.getAlpha())>=M_PI-0.05) {
                            desiredState=State::OFF;
                        }
                    }
                    else if(abs(this->alphaDesired-controller.getAlpha())<this->tolerance){
                       desiredState=State::OFF;
                    }
                }

            }


            break;

        default:

            state = State::OFF;

            break;
        }
    }
    peripherals::enableIRSensors = 0;
}

}
}
}
}
