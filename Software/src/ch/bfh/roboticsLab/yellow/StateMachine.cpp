#line 2 "ch/bfh/roboticsLab/yellow/StateMachine.cpp"
/* StateMachine.cpp
 * Copyright (c) BFH roboticsLab, ZHAW
 * All rights reserved.
 */

#include <algorithm>

#include <ch/bfh/roboticsLab/yellow/StateMachine.h>
#include <ch/bfh/roboticsLab/yellow/Peripherals.h>
#include <ch/bfh/roboticsLab/util/Util.h>
#include <ch/bfh/roboticsLab/yellow/Console.h>


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
      tolerance(0.009)
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

        //read IR-Sensors and light LEDS if distance is under threshold
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
                //con.printf("desired %d\r\n",desiredState);
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
                manuver=1;
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
        //drives robot with speeds transmitted by  wirless comunication
            if (desiredState <= State::ON) {

                controller.setTranslationalVelocity(0.0f);
                controller.setRotationalVelocity(0.0f);

                state = State::ON;

            } else {

                controller.setTranslationalVelocity(translationalVelocity);
                controller.setRotationalVelocity(rotationalVelocity);
            }

            break;

        case State::AUTO_REACTIVE:
        // navigates robot around objects with ir-distance sensors
            buttonNow = peripherals::userButton;
            if (buttonNow && !buttonBefore)
                desiredState = State::OFF;

            if (desiredState <= State::ON) {

                controller.setTranslationalVelocity(0.0f);
                controller.setRotationalVelocity(0.0f);

                state = State::ON;

            } else {

                //distance array is read out and translation and rotation velocity is set, according to the formula, except when all three frontsensor
                //senses a distance smaller than minimum threshhold or when difference between outer sensor is too small
                maxDistance = 0.9f / 1.5f *translationalProfileVelocity;


                if(distance[0]>=maxDistance && distance[1]>=maxDistance && distance[5]>=maxDistance){
                    controller.setTranslationalVelocity(translationalProfileVelocity);
                    controller.setRotationalVelocity(0.0f);
                }
                else if(distance[0]<=minDistance || distance[1]<=minDistance || distance[5]<=minDistance){
                    controller.setTranslationalVelocity(-0.1*translationalProfileVelocity);
                    controller.setRotationalVelocity(0.0f);
                }
                else {
                    controller.setTranslationalVelocity(0.3+8.0f*translationalProfileVelocity*(distance[0]/maxDistance)*(distance[1]+distance[5])/(2.0f*maxDistance));
                    if(abs(distance[1]-distance[5])>0.00){
                        controller.setRotationalVelocity(0.1+10.0f*maxRotationalVelocity*((distance[5]/maxDistance)-(distance[1]/maxDistance)));
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


                bool dontRot=false;
                if(alphaDesired==123456) // angle 123456 is indicator, that the robot should ignore the angle indication
                {
                    dontRot=true;
                }
                //direkt manuver to reach a requested location
                float angleOfLane=atan2(yDesired-controller.getY(),xDesired-controller.getX());
                float deltaAngle=util::unwrap(angleOfLane-controller.getAlpha());
                float distanceToTarget=sqrtf(((xDesired-controller.getX())*(xDesired-controller.getX()))+((yDesired-controller.getY())*(yDesired-controller.getY())));
                float orientatonKor=0;
                monitor1=(float)angleOfLane;


                switch (manuver)
                {
                case 1:
                    //rotate Robot in the direction it needs to drive to reach target position
                    controller.setRotationalVelocity((deltaAngle)*K1);
                    if((abs(deltaAngle)*K1)>maxRotationalVelocity && (deltaAngle)*K1<0)
                    {
                        controller.setRotationalVelocity(-maxRotationalVelocity);

                    }
                    else if((abs(deltaAngle)*K1)>maxRotationalVelocity && (deltaAngle)*K1>0)
                    {
                        controller.setRotationalVelocity(maxRotationalVelocity);
                    }
                    if(distanceToTarget<tolerance && dontRot==false)
                    {
                        manuver=3;
                        controller.setRotationalVelocity(0.0f);
                        controller.setTranslationalVelocity(0.0f);

                    }
                    else if(abs(deltaAngle)<tolerance)
                    {
                        manuver=2;
                        controller.setRotationalVelocity(0.0f);
                    }
                    break;
                case 2:
                    //travel along line between points. Correct if direction is to far of

                    controller.setTranslationalVelocity(distanceToTarget*K2);

                    controller.setRotationalVelocity((deltaAngle)*K3);
                    if(abs(deltaAngle)*K3>maxRotationalVelocity && (deltaAngle)*K3>0)
                    {
                        controller.setRotationalVelocity(maxRotationalVelocity );
                    }
                    if(abs(deltaAngle)*K3>maxRotationalVelocity && (deltaAngle)*K3<0)
                    {
                        controller.setRotationalVelocity(-maxRotationalVelocity );
                    }

                    if(abs(distanceToTarget*K2)>maxForwardVelocity)
                    {
                        controller.setTranslationalVelocity(maxForwardVelocity);
                    }



                    if(distanceToTarget<=tolerance)
                    {
                        controller.setTranslationalVelocity(0.0f);
                        controller.setRotationalVelocity(0.0f);
                        if(dontRot==true)
                        {
                            manuver=1;
                            desiredState=State::OFF;
                        }
                        else
                        {
                            manuver=3;
                        }

                        //Thread::wait(1000);
                    }
                    break;

                case 3:
                    //orient robot into the desired direction
                    if(dontRot==false)
                    {
                        orientatonKor =  (alphaDesired-controller.getAlpha());
                        double korVel = orientatonKor*K1;

                        if(abs(korVel)>maxRotationalVelocity && korVel<0)
                        {
                            korVel= -maxRotationalVelocity;
                        }
                        else if((abs(korVel))>maxRotationalVelocity && korVel>0)
                        {
                            korVel = maxRotationalVelocity;
                        }
                        // didnt implement fully fleged i part, but when error is under a certion level and the speed is very low.
                        //set speed onto a level at which the robot still turns
                        if(abs(controller.getAlpha()-alphaDesired)>=tolerance*0.5 && abs(korVel)<0.5)
                        {
                            if(orientatonKor*K1<0)
                            {
                                korVel = -0.5;
                            }
                            else
                            {
                                korVel = 0.5;
                            }
                        }
                        controller.setRotationalVelocity(korVel);
                        //con.printf("anlge diff: %f\r\n",controller.getAlpha()-alphaDesired);
                        if(abs(controller.getAlpha()-alphaDesired)<tolerance*0.5)
                        {

                            manuver=1;
                            controller.setTranslationalVelocity(0.0f);
                            controller.setRotationalVelocity(0.0f);
                            desiredState=State::OFF;
                        }
                    }

                    else if(dontRot==true)
                    {
                        manuver=1;
                        controller.setTranslationalVelocity(0.0f);
                        controller.setRotationalVelocity(0.0f);
                        desiredState=State::OFF;
                    }
                    break;
                }

               /* if(abs(distanceToTarget)<this->tolerance)
                {
                    if(abs(this->alphaDesired)>=M_PI-0.01){
                        if(abs(controller.getAlpha())>=M_PI-0.01) {
                            desiredState=State::OFF;
                        }
                    }
                    else if(abs(this->alphaDesired-controller.getAlpha())<this->tolerance){
                       desiredState=State::OFF;
                    }
                }*/

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
