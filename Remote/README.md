<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics

Prof. Dr. Gabriel Gruener

## Yellow Remote Communication
The Yellow robot implements a communication interface that allows you to exchange data with it from a WiFi-connected device (e.g. your PC).

The files in this directory will help you set up the communication and exchange data.

The preferred way to interact with the robot is through Matlab. Refer to the [Matlab/README.md](Matlab/README.md) interface.


## Instructions
In order to connect your device to Yellow you need first to connect per WiFi to your robot's Access Point (AP).
The AP has the same name as your robot, for example `Yellow_14`.

Once you connect to the robot your device will be assigned a local IP address (e.g. 192.168.1.11).

The robot will always have the IP **192.168.1.1**.

**!!  DANGER  !!**  
Every robot has an AP and you will be able to connect to any robot in the vicinity without authentication.  
**Connect only to your robot and double-check the connection before you start testing**.  
Never connect to another team's robot, you do not know how they programmed it and how it will react to your commands.
If you connect to the wrong robot by mistake, you may create **major accidents** by commanding the wrong robot to perform an action
while expecting your robot to move. You will be looking at your static robot while the other robot runs away!

## Contents
In this directory you will find several files that define and implement communication between the Yellow robot and
your WiFi-enabled device (e.g. PC).

### Protocol
The [Protocol](Protocol) directory contains the communication protocol definition.

### Matlab
The [Matlab](Matlab) directory contains an example that connects to the robot and exchanges information.

This is the preferred way to interact with the robot.

### Java
The [Java](Java) directory contains a Java implementation of the Yellow communication protocol.
This implementation is used by the Matlab example.

The preferred method to interact with the robot is [Matlab](Matlab) but,
if you know Java well and feel comfortable working with Java, you could write your own Java code instead of Matlab.
