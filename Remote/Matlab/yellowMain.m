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
% % Retrieve Lidar data for every 2 degrees
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



% Example usage of getLidarLines function
%Get Lidar lines
%% Example usage of getLidarLines function
% Get Lidar lines
% for l=1:1
    tic
    [lStart, lEnd] = getLidarLines(yellow);
    toc
    figure(20)
    clf
    % Draw Robo
    plot([90 90 -120 -120 90], [90 -90 -90 90 90], 'r');
    hold on
    plot([0 120], [0 0], 'r');
    length(lStart)
    length(lEnd)
    for k=1:length(lStart)
        plot([lStart(k,1) lEnd(k,1)], [lStart(k,2) lEnd(k,2)],'+-r')
        hold on
        lStart
        lEnd
    end
    grid on
    axis equal
    drawnow
% end
%% do map
%yellow.set('state { stateName: AUTO_REACTIVE }')
% 
% clear 'globalMap'
% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,2));
% robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10));
% robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10));
% orientation= (telemetry.odometry.pose.alpha);





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
% 
% 
%load('workspaceVariables.mat')
% yellow.set('state { stateName: OFF}');
% % 
% clear 'globalMap'
% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,2));
% robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10));
% robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10));
% orientation= (telemetry.odometry.pose.alpha);
% 
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% gMap = globalMap(lStart1,lEnd1,robotCoordinate,orientation);
% 
% point = bestSpot(gMap);
% gMap(point(1),point(2))=100;
% 
% figure(9)
% imshow(gMap)
% pause(3)
% %yellow.set('state { stateName: OFF }')
% % yellow.append('state { stateName: ON }')
% xPosition =1.0;
% yellow.set('state { stateName: AUTO_POSITION },desiredPose { x: 1.0, y: 0, alpha: -1.507}')
% pause(10)
% yellow.set('state { stateName: OFF}');
% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,2));
% robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10))
% robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10))
% orientation= (telemetry.odometry.pose.alpha)
% 
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% gMap = globalMap(lStart1,lEnd1,robotCoordinate,orientation);
% 
% point = bestSpot(gMap);
% gMap(point(1),point(2))=100;
% 
% figure(10)
% imshow(gMap)
% yellow.set('state { stateName: AUTO_POSITION },desiredPose { x: 1, y: -2, alpha: -3.14}')
% pause(10)
% yellow.set('state { stateName: OFF}');
% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,2));
% robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10))
% robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10))
% orientation= (telemetry.odometry.pose.alpha)
% 
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% gMap = globalMap(lStart1,lEnd1,robotCoordinate,orientation);
% 
% point = bestSpot(gMap);
% %gMap(point(1),point(2))=100;
% 
% figure(11)
% imshow(gMap)
% 
% yellow.set('state { stateName: AUTO_POSITION },desiredPose { x: 0.0, y: -2, alpha: -3.14}')
% pause(10)
% yellow.set('state { stateName: OFF}');
% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,2));
% robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10))
% robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10))
% orientation= (telemetry.odometry.pose.alpha)
% 
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% % gMap = globalMap(lStart1,lEnd1,robotCoordinate,orientation);
% % figure(12)
% % imshow(gMap)
% 
% yellow.set('state { stateName: AUTO_POSITION },desiredPose { x: 1, y: -2, alpha: -3.14}')
% pause(10)
% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,2));
% robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10))
% robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10))
% orientation= (telemetry.odometry.pose.alpha)
% 
% %yellow.set('state { stateName: OFF}');
% %[lStart1, lEnd1] = getLidarLines(yellow);
% % pause(2)
% 
%  lStart1 = round([-1000 ,-2000;2000,-2000;2000,2000; 1500,1500;-600 ,1000;-1000, 1000;-600,1000;1500,1500 ]/100);
%  lEnd1 =   round([2000  ,-2000;2000, 2000;1500,2000; -600,1500;-1000,1000;-1000,-2000;-600,1500;1500,2000]/100);
% 
% robotCoordinate = [0,0];
% orientation = 0;
% gMap = globalMap(lStart1,lEnd1,robotCoordinate,orientation);
% 
% filename = 'yellow.mat';
% save(filename)
% 
% lStart2 = round([  100,1500;-600 ,1000;-1000,1000]);
% lEnd2 =   round([  500,1500;-1000,1000;-1000,100]);
% lStart3 = round(lStart2/100);
% lEnd3 = round(lEnd2/100);
% t = cputime;
% [coordinate,alpha] = localisation(lStart3,lEnd3,gMap);
% time = cputime-t
% 
% 
% gMap(coordinate(2),coordinate(1))=100;
% alpha
% coordinate
% % 
% figure(25)
% imshow(gMap)



%% Movment test

driveToPosition(1,0,0,yellow);

pause(10)

driveToPosition(-1,0,0,yellow);
pause(10)
driveToPosition(0,0,0,yellow);
pause(10)
driveToPosition(0,-1,0,yellow);
pause(10)
driveToPosition(0,1,0,yellow);
pause(10)
driveToPosition(0,0,0,yellow);
pause(10)

%% velocitiy test
yellow.set('state{stateName: MANUAL}')

% You may append commands, so they will be sent to the robot one after the other
% Set the velocities for manual mode: linear and angular speed
yellow.append('velocities{linearSpeed:0.5, angularSpeed:0}')
%test velocity without filter in controller.h, take out the motionplaner in
%controller

%% mapping
clear 'globalMap'
doMapping = true
while(doMapping==true)
    yellow.set('state{stateName: OFF}')
    pause(2)
    [lStart, lEnd] = getLidarLines(yellow);
    telemetry = yellow.receive;
    robotCoordinate = int8(zeros(1,2));
    robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10));
    robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10));
    orientation= (telemetry.odometry.pose.alpha);
    
    lStart1 = round(lStart/100);
    lEnd1 = round(lEnd/100);
    [gMap,zeroPoint]= globalMap(lStart1,lEnd1,robotCoordinate,orientation);
    bwDist = gMap;
    bwDist(bwDist==200)=0;
    se = strel('diamond',1);
    bwDist1 = imerode(double(gMap),se);
    bwDist2 = bwDist1;
    bwDist2(bwDist1==200)=0;
    figure(2000)
    imshow(mat2gray(bwDist1));
    title('map in navigation')
    point = bestSpot(bwDist1)
    if(point(1)==0)
        if(point(2)==0)
            doMapping=false;
            break;
        end
    end
%     bwDist(point(1),point(2))=100;
% %     figure(1000)
% %     imshow(bwDist)
    viaPoints=navToPoint(bwDist2,double([point(2) point(1)]).*0.1,0.1,[zeroPoint(1) zeroPoint(2)].*0.1,[telemetry.odometry.pose.y telemetry.odometry.pose.x])
    
    viaCnt=1;
    matSize=size(viaPoints)
    while(viaCnt<=matSize(1))
        driveToPosition(viaPoints(viaCnt,2),viaPoints(viaCnt,1),viaPoints(viaCnt,3),yellow);
        pause(10)
        viaCnt=viaCnt+1;
    end
    
    %doMapping=false;
    
end


%% drive to target
clear 'globalMap'
targetPoint=[0 0];
targetOrientation =0;
yellowString = sprintf('correctedPose: { x: %f, y: %f, alpha: %f}',0,0,0);
yellow.set(yellowString);
pause(2)
yellow.set('state{stateName: OFF}')
pause(2)
[lStartLoc, lEndLoc] = getLidarLines(yellow);
telemetry = yellow.receive;
[coordinateLoc1,orientationLoc1] = localisation(lStartLoc/100,lEndLoc/100,gMap);

% %***** untested
% yellowString = sprintf('correctedPose: { x: %f, y: %f, alpha: %f}',coordinateLoc1(1),coordinateLoc1(2),orientationLoc1(1));
% yellow.set(yellowString);
% pause(2)
% %*****
% [lStart, lEnd] = getLidarLines(yellow);
% telemetry = yellow.receive;
% robotCoordinate = int8(zeros(1,2));
% robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10));
% robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10));
% orientation= (telemetry.odometry.pose.alpha);
% 
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% [locMap,zeroPointLocMap]= globalMap(lStart1,lEnd1,robotCoordinate,orientation);
% 
% se = strel('diamond',1);
% bwLocMap = imerode(double(locMap),se);
% 
% title('map in Localization')
% pointLoc = bestSpot(bwLocMap)
% bwLocMap(bwLocMap==200)=0;
% figure(2000)
% imshow(mat2gray(bwLocMap));
% oldOdommetrie = telemetry.odometry
% viaPointsLoc=navToPoint(bwLocMap,double([pointLoc(2) pointLoc(1)]).*0.1,0.1,[zeroPointLocMap(1) zeroPointLocMap(2)].*0.1,[telemetry.odometry.pose.y telemetry.odometry.pose.x])
% followSize=size(viaPoints)
% followPath(viaPointsLoc(1:round(followSize/2),:),yellow)

driveToPosition(0,0,pi,yellow);

pause(10)
yellow.set('state{stateName: OFF}')
pause(2)
[lStartLoc2, lEndLoc2] = getLidarLines(yellow);
clear possibilityMap
[coordinateLoc2,orientationLoc2] = localisation(lStartLoc2/100,lEndLoc2/100,gMap);



% coordinateLoc = (double(coordinateLoc1(1,:)) + double(coordinateLoc2(1,:)))/2;
% coordinateLoc(1,:) = (coordinateLoc(1,:)-zeroPoint)*0.1
% orientationLoc = (double(orientationLoc2)+double(orientationLoc2))/2/180*pi
% xToSend = coordinateLoc(1,2)
% yToSend = coordinateLoc(1,1)
% rotToSend = orientationLoc(1)
% yellowString = sprintf('correctedPose: { x: %f, y: %f, alpha: %f}',xToSend,yToSend,rotToSend)
% yellow.set(yellowString);
% pause(2)
% telemetry = yellow.receive
% %startPoint = telemetry.
% se = strel('diamond',1);
% navMap = imerode(double(gMap),se);
% navMap(navMap==200)=0;
% figure(200)
% imshow(bwDist1)
% viaPoints = navToPoint(navMap,zeroPoint*0.1,0.1,zeroPoint*0.1,[telemetry.odometry.pose.y,telemetry.odometry.pose.x])
% matSize=size(viaPoints)
% viaCnt=1;
% while(viaCnt<=matSize(1))
%     driveToPosition(viaPoints(viaCnt,2),viaPoints(viaCnt,1),0,yellow);
%     pause(10)
%     viaCnt=viaCnt+1;
% end
%driveToPosition(targetPoint(1),targetPoint(2),targetOrientation, yellow)


