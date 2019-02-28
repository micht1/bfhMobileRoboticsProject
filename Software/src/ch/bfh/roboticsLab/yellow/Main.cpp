#line 2 "ch/bfh/roboticsLab/yellow/Main.cpp"
/* Main.cpp
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#include <mbed.h>

#include <ch/bfh/roboticsLab/yellow/Console.h>
#include <ch/bfh/roboticsLab/yellow/Peripherals.h>
#include <ch/bfh/roboticsLab/yellow/Controller.h>

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
          controller(Controller::getInstance())
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

    /* This method will be called when the thread starts. When this method returns, the thread stops. */
    void run() {

        /* TODO (Ex1.1): Write messages to the serial console.
         * Use the 'console' object to write messages to the serial console. Refer to the documentation of the 'Console' class.
         * On your PC, use a serial terminal (e.g. 'hterm') to read the generated messages.
         */

        console.printf("Hello World\n");

        /* TODO (Ex1.2 & 1.3): Control wheel motors by setting PWM duty cycles.
         * Apply a duty cycle to the left and right wheel PWM outputs.
         * Understand the wheel motion according to the duty cycle you apply. (Forward, backward motion?)
         */

        // Enable the motor drivers.
        peripherals::enableMotorDriver = 1;

        // Set PWM period
        peripherals::pwmLeft.period(0.00005f);
        peripherals::pwmRight.period(0.00005f);

        // NOTE: Respect the min / max allowed duty cycles defined in peripherals::MIN_DUTY_CYCLE and peripherals::MAX_DUTY_CYCLE
        //peripherals::pwmLeft.write(0.5f);
        //peripherals::pwmRight.write(0.5f);



        // Disable the motor drivers.
        peripherals::enableMotorDriver = 0;


        /* TODO (Ex1.4 & 1.5): Read distance sensors & activate the corresponding LED
         * Enable the IR sensors.
         * Read the sensors and understand what data you are receiving. (Hint: Look at the array peripherals::irSensors)
         * Turn on and off the corresponding LED to signal if an obstacle is present.
         */

        peripherals::enableIRSensors = 1;

        float sens[peripherals::N_IRs]={0};
        for(int cnt = 0; cnt <peripherals::N_IRs; ++cnt){
            sens[cnt]=peripherals::irSensors[cnt];  //.read();

            if(sens[cnt] <= 0.2){
                peripherals::irLEDs[cnt] = 1;
            }
            else{
                peripherals::irLEDs[cnt] = 0;
            }

            //console.printf("Sens %d: %f\n\r",cnt,sens[cnt]);
        }
        /* TODO (Ex2): Complete the controller class to control the motors
         * Look at the Controller.h class and complete it to achieve a desired linear and angular velocity.
         */

        // Start the controller thread
        controller.start();

        // Set a translational velocity [m/s].
        controller.setTranslationalVelocity(0.3f);
        // Set a rotational velocity [rad/s].
        controller.setRotationalVelocity(0.0f);
        // Wait 1000 ms before continuing
        Thread::wait(1000);
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
