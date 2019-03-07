<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics

Prof. Dr. Gabriel Gruener

## Yellow Matlab Interface
This directory contains the files necessary to connect to Yellow and an example on how to exchange information using *Matlab*.

This is the preferred way to interact with the robot remotely.

### Files

`yellowMain.m`  
This script contains the main code to control and communicate with Yellow. In this file you set a desired State Machine state or specify motion parameters for the robot.  
You may also use this script to display incoming LIDAR data, build an occupancy grid, perform global localization by sending pose corrections to your robot, plan navigation, etc.

`getLidar.m`  
This function retrieves LIDAR data from Yellow.  
You do not need to make any changes to this function. However, you may change the resolution at which the LIDAR data are requested (e.g. each 10°). Look at the script to understand how the communication works.

`getLidarLines.m`  
This function retrieves LIDAR lines found by the on-board algorithm.
Since you have to implement the C++ code on the robot that finds lines in LIDAR data, you receive no lines until you implement it.
This function requests LIDAR lines with default thresholds. You may want to request using different thresholds to the line-finding algorithm. Refer to the examples inside the comments for that:
```Matlab
yellow.set('requestLidarLines{minRangeDistance:500, maxLineImprecision:50, maxAngleBetweenLines:150}');
```

`yellowTelemetry.m`  
This script contains some examples on how to interact with the Yellow robot from Matlab. Do not execute this script!

`telemetry.txt`  
This file contains a text-based protobuf Telemetry message that can be used to simulate a message comming from the robot for testing purposes.

#### Libraries
The matlab functions and scripts described above depend on the following 2 Java libraries:

`YellowInterface.jar` Java library with BFH's implementation of the Yellow communication and protocol. Refer to the [Java implementation and documentation](../Java/).

`protobuf-java-3.4.0.jar` Java library necessary to use Google's Protobuf to parse the [communication protocol](../Protocol/).
