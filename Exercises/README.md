<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics
Prof. Dr. Gabriel Gruener

# Exercises
During the first 5 weeks of lecture there are 5 practical exercises that will enable you to put into practice the theory learned in class.

By solving these exercises you and your robot will be ready to attack the course's project.

## [Exercise 1](Exercise01.md)
In this exercise you get to know your mobile robot and its programming tools. Write, compile and execute your first program on **Yellow**.

You will then increase your knowledge about the available hardware and its drivers. Get to know the `Peripherals` namespace. Move the robot's wheels by applying **PWM Outputs** and characterize the wheel's motions to this command. Test reading the analogue **Infrared Sensors** and control the available **LEDs** with digital outputs.

Get familiar with the serial **Console** to print useful messages.

## [Exercise 2](Exercise02.md)
In this exercise you get to know the `RealtimeThread` class and start controlling the robot.

You will write the `Controller` class to **control the motors** of the robot to achieve a desired linear and angular velocity.

Add **odometry** into the `Controller` class based on encoder counter data.

##  [Exercise 3](Exercise03.md)
In this exercise you implement **Reactive Navigation**: `Yellow` can find the exit of a one-track labyrinth.

Get familiar with the wheel motion planner.

Add a **State Machine**. Read a push to the user button as a signal to execute a program, then wait when done.

##  [Exercise 4](Exercise04.md)
In this exercise you integrate the LIDAR sensor.

Read LIDAR data and get to know the data you are receiving. Implement a **line finding algorithm**.

Add a **low-pass filter** to the EncoderCounter for smoother performance.

##  [Exercise 5](Exercise05.md)
Read IMU.
Add sensor fusion.  
Add global localization based on LIDAR beacons.
Navigate using global localization

## Plan

Week | Class topic | Exercise
:-: | --- | :-:
1 | Introduction, Kinematics | 1
2 | Position control | 2
3 | Localization | 3
4 | Sensor filters & fusion | 4
5 | Navigation | 5
6 | Advanced topics | Project work
7 | *Excursion: ASL ETH* | Project work
8 | Applications | Project work
9 | *Spring break* | *no class*
10 | Final exam / Roboethics | Project work
11 | Project delivery |
