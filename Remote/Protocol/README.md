<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics

Prof. Dr. Gabriel Gruener

## Yellow Remote Communication Protocol
This directory contains the files that define the communication protocol between Yellow and your device.

### Definitions
The following definitions are given:

**Telemetry**  
A message that Yellow sends to you.

<table>
<tr><th colspan=3>Telemetry</td></tr>
<tr><td>Yellow</td><td><font size='+2'>&rarr;</font></td><td>PC</td>
</table>

A Telemetry message may contain any or many of the following information:

* Sensor data
* Odometry estimation
* Current State Machine state


**Telecommand**  
A message that you send to Yellow.

<table>
<tr><th colspan=3>Telecommand</td></tr>
<tr><td>Yellow</td><td><font size='+2'>&larr;</font></td><td>PC</td>
</table>


A Telecommand message may contain any or many of the following requests to:

* Change state
* Send LIDAR data
* Send LIDAR lines data
* Set the desired robot velocities
* Set a desired goal pose
* Correct the estimated global pose

### Protocol Buffers
The communication protocol is defined and implemented using Google's [protocol buffers](https://developers.google.com/protocol-buffers/).

### Protocol Definition
The file [yellow.proto](yellow.proto) defines the protobuf messages that are exchanged between the robot and your computer.
Towards the end of this file you will find definitions for a message `Telemetry` and message `Telecommand`.
These 2 messages contain sub-messages of different types, like message `Pose`.
These sub-messages are defined on the initial part of the `yellow.proto` file.

### Usage
You **do not need to modify or recompile** anything in this directory. It is simply here as reference.
