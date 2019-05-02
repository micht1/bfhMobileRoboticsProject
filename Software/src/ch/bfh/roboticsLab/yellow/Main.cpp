#line 2 "ch/bfh/roboticsLab/yellow/Main.cpp"
/* Main.cpp
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#include <mbed.h>

#include <ch/bfh/roboticsLab/yellow/Console.h>
#include <ch/bfh/roboticsLab/yellow/Peripherals.h>
#include <ch/bfh/roboticsLab/yellow/Controller.h>
#include <ch/bfh/roboticsLab/yellow/StateMachine.h>

#include <ch/bfh/roboticsLab/yellow/LidarAnalysis.h>

#include <ch/bfh/roboticsLab/yellow/communication/SerialServer.h>
#include <ch/bfh/roboticsLab/yellow/communication/ProtocolInterface.h>
#include <ch/bfh/roboticsLab/yellow/communication/TelemetrySender.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/** Simple main class to run the main application on its own thread. */
class Main {

public:

    Main()
        : thread(osPriorityNormal, STACK_SIZE),
          console(Console::getInstance()),
          controller(Controller::getInstance()),
          stateMachine(StateMachine::getInstance()),
          serialServer(communication::SerialServer::getInstance()),
          telemetrySender(communication::TelemetrySender::getInstance())
    {
        thread.start(callback(this, &Main::run));
    }

    virtual ~Main() {}

private:

    /** Thread stack size in bytes */
    static const uint32_t STACK_SIZE = 0x2000;

    /** Private thread object to run this task. */
    Thread thread;

    /** Reference to Console. */
    Console& console;

    /** Reference to Controller. */
    Controller& controller;
    /** Reference to State Machine. */
    StateMachine& stateMachine;
    /** Reference to Serial Server. */
    communication::SerialServer& serialServer;
    /** Reference to Telemetry Sender. */
    communication::TelemetrySender& telemetrySender;

    /* This method will be called when the thread starts. When this method returns, the thread stops. */
    void run() {
        console.printf("Hello World\n");
        // Enable the motor drivers.
        peripherals::enableMotorDriver = 1;

        // Set PWM period
        peripherals::pwmLeft.period(0.00005f);
        peripherals::pwmRight.period(0.00005f);

        // Disable the motor drivers.
        peripherals::enableMotorDriver = 0;

        // Start the controller thread
        peripherals::enableMotorDriver=1;
        controller.start();

        // Start state machine
        console.printf("Starting state machine...\r\n");
        stateMachine.start();

        // Start LIDAR
        console.printf("Starting LIDAR...\r\n");
        driver::LIDAR::getInstance().start();

        // Communication
        console.printf("Starting Telemetry Sender...\r\n");
        communication::TelemetrySender::getInstance().start();
        Thread::wait(1000);

        while (true) {
          processIncomingTelecommand();
          

        }

        console.printf("Done\r\n");
    }

    /**
     * Process an incoming telecommand message.
     */
    void processIncomingTelecommand() {

        console.printf("Waiting for incoming message...\r\n");

        communication::Stream incoming;
        ch_bfh_roboticsLab_yellow_communication_Telecommand telecommand = communication::ProtocolInterface::processTelecommand(serialServer.receive(incoming));

        if (telecommand.has_timestamp)
            console.printf("Received telecommand.timestamp %ld\r\n", telecommand.timestamp);

        if (telecommand.has_requestLidarData && telecommand.requestLidarData > 0) {
          console.printf("Received telecommand.requestLidarData %ld\r\n", telecommand.requestLidarData);
          telemetrySender.requestLidar(telecommand.requestLidarData);
        }

        if (telecommand.has_requestLidarLines) {
          console.printf("Received telecommand.requestLidarLines\r\n");
          telemetrySender.requestLidarLines(telecommand.requestLidarLines);
        }

        if (telecommand.has_state) {
            console.printf("Received telecommand.state %d\r\n", telecommand.state.stateName);
            State::Enum state = communication::ProtocolInterface::getState(telecommand.state.stateName);
            if (state != State::AUTO_POSITION || telecommand.has_desiredPose)
                stateMachine.setDesiredState(state);
        }

        if (telecommand.has_velocities) {
            console.printf("Received telecommand.velocities %f, %f\r\n", telecommand.velocities.linearSpeed, telecommand.velocities.angularSpeed);
            stateMachine.setVelocities(telecommand.velocities.linearSpeed, telecommand.velocities.angularSpeed);
        }

        if (telecommand.has_desiredPose) {
            console.printf("Received telecommand.desiredPose %f, %f, %f\r\n", telecommand.desiredPose.x, telecommand.desiredPose.y,
                           telecommand.desiredPose.alpha);
            stateMachine.setGoalPose(telecommand.desiredPose.x, telecommand.desiredPose.y, telecommand.desiredPose.alpha);
        }

        if (telecommand.has_correctedPose) {
            console.printf("Received telecommand.correctedPose %f, %f, %f\r\n", telecommand.correctedPose.x, telecommand.correctedPose.y,
                           telecommand.correctedPose.alpha);
            // Apply the correction to the controller
            controller.setX(telecommand.correctedPose.x);
            controller.setY(telecommand.correctedPose.y);
            controller.setAlpha(telecommand.correctedPose.alpha);
        }

        if (telecommand.has_reactiveParameters) {
            ch_bfh_roboticsLab_yellow_communication_ReactiveNavigationParameters p = telecommand.reactiveParameters;
            if (p.has_minDistance) {
                console.printf("Received reactive param minDistance %f\r\n", p.minDistance);
                if (p.minDistance < 0.0)
                    stateMachine.minDistance = StateMachine::MIN_DISTANCE;
                else
                    stateMachine.minDistance = p.minDistance;
            }
            if (p.has_maxDistance) {
                console.printf("Received reactive param maxDistance %f\r\n", p.maxDistance);
                if (p.maxDistance < 0.0)
                    stateMachine.maxDistance = StateMachine::MAX_DISTANCE;
                else
                    stateMachine.maxDistance = p.maxDistance;
            }
            if (p.has_rotationalVelocityGain) {
                console.printf("Received reactive param rotationalVelocityGain %f\r\n", p.rotationalVelocityGain);
                if (p.rotationalVelocityGain < 0.0)
                    stateMachine.rotationalVelocityGain = StateMachine::KR;
                else
                    stateMachine.rotationalVelocityGain = p.rotationalVelocityGain;
            }
            if (p.has_translationalVelocity) {
                console.printf("Received reactive param rotationalVelocityGain %f\r\n", p.rotationalVelocityGain);
                if (p.translationalVelocity < 0.0)
                    stateMachine.translationalProfileVelocity = Controller::TRANSLATIONAL_PROFILE_VELOCITY;
                else
                    stateMachine.translationalProfileVelocity = p.translationalVelocity;
            }
        }
    }
};
}
}
}
}


/** This is the main program of the application. */
int main() {

    // This call creates the Main thread and starts it.
    ch::bfh::roboticsLab::yellow::Main main;

    Thread::wait(osWaitForever);
    return 0;
}
