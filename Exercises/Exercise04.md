<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics
Prof. Dr. Gabriel Gruener

## Exercise 4

### Goal
* Get to know the WiFi communication and the protocol messages **Telemetry** and **Telecommand**.
* Get to know the `LIDAR` class.
* Transfer LIDAR scans from the robot to your PC and visualize them there.
* Implement a LIDAR line finding algorithm on Yellow, transfer the data to your PC and visualize it there.

### Introduction
The Yellow robot software now implements a communication interface that allows you to exchange data with it from a WiFi-connected device (e.g. your PC). In this exercise you will test the existing interface.

#### Definitions
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
* Set the desired robot velocities
* Set a desired goal pose
* Correct the estimated pose

All information regarding the communication interface on your PC is located under the [../Remote](../Remote/) directory. Refer to the [../Remote/README.md](../Remote/README.md) file for more information.

### Procedure
1. Update your project from the git upstream (refer to [../README.md](../README.md)).
<br><br>

1. Nothing to do

<br><br>

1. Inspect the new classes

	1. `communication/SerialServer.h`  
	The class `communication::SerialServer` implements a communication server using the serial port to talk to the on-board WiFi adapter. It includes a simple serial communication encoder.

	1. `communication/yellow.pb.h`  
	This file is automatically generated from `yellow.proto` and implements the [protocol buffers](https://developers.google.com/protocol-buffers/) Yellow protocol. Refer to the [../Remote](../Remote/) directory for further information.

	1. `communication/ProtocolInterface.h`  
	The class `communication::ProtocolInterface` allows you to easily send outgoing `Telemetry` objects and receive incoming `Telecommand` objects. The `TelemetrySender` class (see below) uses it to send `Telemetry` messages. `Main` uses it to parse incoming `Telecommand`s

	1. `communication/TelemetrySender.h`  
	The `communication::TelemetrySender` class implements a real-time thread that prepares and sends `Telemetry` messages at regular intervals. You may read these messages from your PC.

	1. `driver/LIDAR.h`  
	The `driver::LIDAR` class implements a driver to read the LIDAR sensor. It is used by the `TelemetrySender` and the `LidarAnalysis` classes (see below).  

	1. `LidarAnalysis.h`  
	The `LidarAnalysis` class provides a skelleton for you to implement on-board LIDAR analysis. For example the line finding algorithm. 
<br><br>

1. **Listen and talk to Yellow**

	1. Connect to your robot's WiFi Access Point (AP), it has the same name as your robot (e.g. `Yellow_14`).
	1. Go to the [../Remote/Matlab](../Remote/Matlab/) directory and follow the instructions there to:
		1. Send a Telecommand to the robot to go into the `MANUAL` state. Test setting different linear and angular velocities.
		1. Stop the robot by requesting the `OFF` state.
		1. Request the `AUTO_REACTIVE` state. Test different reactive navigation parameters as the translational velocity or the obstacle reaction distance (`minDistance`, `maxDistance`).
		1. Request the `AUTO_POSITION` state and command the robot to drive to a given desired pose.
<br><br>

1. **LIDAR scan analysis**  
	1. Inside the *Matlab* routine retrieve a Lidar scan from the robot and look at the resulting figure.
	<br><br>

	Depending on the resolution you request, LIDAR scan data can be quite large. Transferring the data from Yellow to you PC may take up to 30 seconds!  
	
	Therefore you shall implement the **Split & Merge line finding algorithm** as seen in the lecture. Based on the LIDAR scan points, Yellow shall find lines and transmit them to your PC.
	
	1. Implement the **split** part of the *Split & Merge* algorithm.
		1. Read the LIDAR scan data and transform it from polar to Cartesian space (in the robot frame).  
			**Hint**: Look for the `TODO` Ex4.2 comment inside `LidarAnalysis.cpp`.
		1. Implement 2 methods: one to calculate the euclidian distance [mm] between two points, another to calculate the orthogonal distance between a line and a point.  
			**Hint**: Look for the `TODO` Ex4.3 & Ex4.4 comments inside `LidarAnalysis.cpp`.
		1. **Segment** the raw scan points. For instance, this could be the left and right walls of a corridor. Use the parameter `minRangeDistance` and choose a suitable value for its default value `MIN_RANGE_DISTANCE_DEFAULT`.  
			**Hint**: Look for the `TODO` Ex4.5 comment inside `LidarAnalysis.cpp`.
		1. **Split** the point segments into lines. Ignore loose points and lines that are too short.  
			**Hint**: Look for the `TODO` Ex4.6 comment inside `LidarAnalysis.cpp`.
		1. Optionally **Merge** lines as seen in the lecture.
		1. Fill the `LineContainer` and return it at the end of the line finding method.  
			**Hint**: Look for the `TODO` Ex4.7 comment inside `LidarAnalysis.cpp`.
	1. You can display and analyze the resulting lines on your PC by requesting them from *Matlab*.  
		**Hint**: Uncomment the example snippet at the end of the script.
