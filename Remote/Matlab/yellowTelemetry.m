% This script contains some indicators on how to interact with the Yellow
% robot from Matlab

% Do not simply execute this script from beginning to end!
% Read through it and use the snippets you find useful for your own
% application.


% Add our classes to the Matlab Java path
dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
javaclasspath(dpath);
import ch.bfh.roboticsLab.yellow.*;


% Parse a telemetry message from file
% filename = 'telemetry.txt';
% telemetry = SerialClient.parseFromFile(filename);

% Connect to the robot
robot = SerialClient.getInstance;
% Read one message, extract the payload and parse it
telemetry = robot.receive()

% Use the telemetry object
% Note: all fields in telemetry are optional, so check they exist before trying
% to use them:

if (~isempty(telemetry.odometry))
    telemetry.odometry.pose.x
end




% Sending commands to the robot

% Commands are defined in yellow.proto.

% Set state MANUAL (speed is 0)
robot.set('state{stateName: MANUAL}')

% You may append commands, so they will be sent to the robot one after the other
% Set the velocities for manual mode: linear and angular speed
robot.append('velocities{linearSpeed:0.1, angularSpeed:0}')

% Make the robot stop by setting the speed to 0
robot.set('velocities{linearSpeed:0, angularSpeed:0}')
% Note the robot is still in MANUAL state

% Alternatively, you can simply stop the robot by setting the state to OFF
robot.set('state{stateName: OFF}')

% Request Lidar data
robot.set('requestLidarData: 10');
% Wait for lidar data to arrive
while 1
    telemetry = robot.receive();
    if (~isempty(telemetry.lidar))
        break
    end
end

% Parse Lidar data (stored as Java ArrayList)
n = telemetry.lidar.points.size();
lAngle = zeros(n,1);
lDistance = zeros(n,1);
lQuality = zeros(n,1);
% TODO improve to filter out points with distance > 10000 or quality < 10
for k = 1:n
    p = telemetry.lidar.points.get(k-1);
    lAngle(k) = p.angle;
    lDistance(k) = p.distance;
    lQuality(k) = p.quality;
end

% Plot lidar data
x = lDistance.*cos(lAngle*pi/180);
y = lDistance.*sin(lAngle*pi/180);
figure(1)
scatter(x, y, 8, lQuality);
colorbar
grid on
axis equal

