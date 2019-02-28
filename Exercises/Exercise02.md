<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics
Prof. Dr. Gabriel Gruener

# Exercise 2

## Goals
* Get to know the `RealtimeThread` class.
* Implement a `Controller` to control the motors of the robot in order to achieve a desired linear and angular velocity.
* Add odometry to the `Controller`.

## Procedure
1. Update your project from the upstream remote (refer to [../README.md](../README.md)).

1. Inspect the new files
	* `RealtimeThread.h` -
		This class defines a real-time thread. Read the class documentation and usage example.
	* `Controller.h` -
		This class implements a RealtimeThread to control the wheels of the robot. Read the class documentation. `Main.cpp` contains the necessary code that instantiates, starts and interacts with the Controller.
	* `driver/EncoderCounter.h` -
		This class implements a driver to read the encoder counters on the motors. The constructor of the Controller class (`Controller.cpp`) contains a code example to read them.

1. Implement `Controller::run()` to command the robot's wheels given a desired linear and angular robot velocity. The desired velocities can be requested from `main::run()`.
	1. Use the differential-drive kinematic model to calculate the desired wheel speeds from the desired linear and angular robot velocities.
	1. Read the wheel encoder counts to derivate the current wheel motor speeds.
	1. A feed-forward, closed-loop P-controller is already provided. It calculates the motor phase voltages needed, based on the motor speed errors.
	1. Set the motor PWM duty cycle that corresponds to the motor phase voltage calculated.

1. The `Controller` class has members to hold the global pose of the robot as well as methods to retrieve it (e.g. `getY`) or set it (`setX`, e.g. during initialization).
	1. Estimate the global position from odometry based on encoder counter data. Refer to the **Kinematics** lecture of this course (global robot pose integrated from current speed).

**Hint**: Look for the `TODO` comments inside the `Controller.cpp` file.
