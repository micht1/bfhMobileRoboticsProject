<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics
Prof. Dr. Gabriel Gruener

# Exercise 1

## Goals
* Install the *ARM cross-compiler*. Compile your first program, transfer and execute it on **Yellow**.
* Get to know the available hardware and its drivers. Interact with the `Peripherals` namespace.
* Understand the wheel motor layout.
* Learn to use the infrared (IR) sensors and activate the LEDs.
* Get familiar with the serial Console.

## Procedure
1. Update your repository from the git upstream as described in [../README](../README.md).

1. Install the necessary development tools as described in [../Software/README](../Software/README.md).

1. Inspect the [Documentation directory](../Documentation/README.md) to learn what hardware is available on **Yellow** and how it is connected to the microcontroller.

1. Inspect the provided files:
	* `Console.h` -
	This class simplifies writing messages to the serial console from anywhere in your code. See class definition for an example on how to use it.
	* `Peripherals.h` -
	This file creates the namespace `peripherals` and defines static objects to all hardware on the robot. You may also add here static definitions of useful constants, see for example `MIN_DUTY_CYCLE`.
	* `driver/IRSensor.h` -
	This class implements the device driver to the Sharp infrared sensors. The electrical design uses only one microprocessor `AnalogInput` to read all 6 sensors by employing a multiplexer, as discussed in class.

1. Add code to the `Main.cpp` class to:
	1. Write messages to the serial **Console**.
	1. **Apply a duty cycle** to the left and right wheel **PWM outputs**.  
	   Use the given `MIN_DUTY_CYCLE` and `MAX_DUTY_CYCLE` constants to make sure that the duty cycle will never be beyond these limits.
	1. Understand which duty cycles make the left and right wheels turn forward and backward.
	1. **Read the IR distance sensors** and understand what data you are receiving. Respect the minimum distance the sensor can detect.
	1. **Control the LEDs** placed above each of the IR sensors, according to the sensors output: Turn on the LED when the distance reported by the corresponding sensor is smaller than a certain threshold.

**Hint**: Look for the `TODO` comments in the C++ source code.
