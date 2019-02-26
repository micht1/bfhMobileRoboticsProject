<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics
Prof. Dr. Gabriel Gruener

# Exercise 2

## Goals
* Get to know the `RealtimeThread` class.
* Write a `Controller` class to control the motors of the robot to achieve a desired linear and angular velocity.
* Add odometry to the `Controller`.

## Procedure
1. Update your project from the upstream remote (refer to [../README](../README.md)).

1. Inspect the new files
	* `RealtimeThread.h` -
	This class defines a real-time thread. Read the class documentation and usage example.
	* `driver/EncoderCounter.h` -
	This class implements a driver to read the encoder counters on the motors. `Main.cpp` contains code example to read them.

1. Write the `Controller` class that commands the robot's wheels given a desired linear and angular velocity. The desired velocities are requested inside the `main::run()` method.
	1. Use the kinematic model to calculate the desired wheel speeds.
	1. Read the encoder counts to calculate the current wheel motor speeds.
	1. Set the PWM duty cycle corresponding to the voltage that needs to be applied.
	1. A closed loop P-controller calculates the motor phase voltages that need to applied with the help of the motor speed error. Set the PWM duty cycle corresponding to this motor phase voltage.

1. The `Controller` class has members to hold the global pose of the robot as well as methods to retrieve (`getX`) or set (`setX`) it. Estimate the global position from odometry based on encoder counter data. Refer to the **Kinematics** lecture of this course (global robot pose integrated from current speed).

**Hint**: Look for the `TODO` comments inside the `Controller.cpp` file.
