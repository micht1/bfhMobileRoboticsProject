%% --- DO NOT MAKE ANY CHANGES IN THIS SECTION --- %%

if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;
    
end

%% ---------- YOUR CODE HERE ---------- %%


%% How to read telemetry from the robot:
telemetry = yellow.receive;
telemetry.state

% telemetry now holds the following structure:
%  int timestamp
%  State state
%  Odometry odometry      % Odometry: Estimated pose x [m], y [m], alpha [deg]
%  Lidar lidar;           % Lidar data: Array of Points: angle [deg], distance [mm], quality
%  LidarLines lidarLines  % LidarLines analysis result: Array of Lines: start and end poses
%  IRSensors ir           % IR sensor measurements: Array of distances [m]
%
% Note: all these entries are optional. If the robot doesn't deliver them, they will be 'null'



%% How to write telecommands to the robot:
% Commands are put on a queue for sequential execution.
% You may:
% + 'append' a command at the end of the queue.
% + 'set' a command for immediate execution (deletes existing queue).
%
% Commands are written in protobuf json format according to the protocol definition.
% The available commands are found in the protobuf protocol:
% 'Protocol/yellow.proto' under 'message Telecommand {}'
% Since most commands and parameters are defined as 'optional' you only need to write the commands and parameters you want to change.
%
% To change the robot state:
yellow.set('state { stateName: OFF }')

% To drive manual with a given linear and angular speed:
% > yellow.set('state { stateName: MANUAL}, velocities { linearSpeed: 0.0, angularSpeed: 0.3 }');

% To drive in auto reactive mode
% > yellow.set('state { stateName: AUTO_REACTIVE }')

% To set the reactive navigation parameters (e.g. the translational velocity)
% > yellow.set('reactiveParameters { translationalVelocity: 1 }');
% To set multiple reactive navigation parameters
% > yellow.set('reactiveParameters { translationalVelocity: 1, minDistance: 0.1, maxDistance: 0.4 }');


%% Example usage of getLidar function
% Retrieve Lidar data for every 2 degrees
%  yellow.set('requestLidarData: 1');
% %
% % The matlab functin 'getLidar' retrieves Lidar data and assigns the result to an array
% % containing angle, distance and quality of every point.
% 
% % Get lidar data and plot
% [lAngle, lDistance, lQuality] = getLidar(yellow);
% x = lDistance.*cos(lAngle*pi/180);
% y = lDistance.*sin(lAngle*pi/180);
% figure(20)
% scatter(x, y, 8, lQuality);
% colorbar
% grid on
% axis equal
% title("Lidar")



%% Example usage of getLidarLines function
% Get Lidar lines
% for l=1:1
%     tic
%     [lStart, lEnd] = getLidarLines(yellow);
%     toc
%     figure(20)
%     clf
%     % Draw Robo
%     plot([90 90 -120 -120 90], [90 -90 -90 90 90], 'r');
%     hold on
%     plot([0 120], [0 0], 'r');
%     length(lStart)
%     length(lEnd)
%     for k=1:length(lStart)
%         plot([lStart(k,1) lEnd(k,1)], [lStart(k,2) lEnd(k,2)],'+-r')
%         hold on
%         lStart
%         lEnd
%     end
%     grid on
%     axis equal
%     drawnow
% end

%% do Mapping
%yellow.set('state { stateName: AUTO_REACTIVE }')

% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,3));
% robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x/100));
% robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y/100));
% robotCoordinate(1,3)= (telemetry.odometry.pose.alpha);
% 
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% gMap = globalMap(lStart1,lEnd1,robotCoordinate);
% figure(9)
% imshow(gMap)
% pause(3)
yellow.set('state { stateName: OFF }')
%yellow.append('state { stateName: ON }')

yellow.set('state { stateName: AUTO_POSITION },desiredPose { x: -0.0, y: -1.0, alpha: 0}')
% pause(5)
% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,3));
% robotCoordinate(1,2)= 0;%int8(round(telemetry.odometry.pose.x/100));
% robotCoordinate(1,1)= 10;%int8(round(telemetry.odometry.pose.y/100));
% robotCoordinate(1,3)= 0;%(telemetry.odometry.pose.alpha);
% 
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% gMap = globalMap(lStart1,lEnd1,robotCoordinate);
% figure(10)
% imshow(gMap)