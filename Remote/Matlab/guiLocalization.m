function [coordinateLoc1,orientationLoc1]=guiLocalization

if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;   
end
load('mapFile')
% load('mapFile','gMap')
% load('mapFile','loadedMap')


yellowString = sprintf('correctedPose: { x: %f, y: %f, alpha: %f}',0,0,0);
yellow.set(yellowString);

yellow.set('state{stateName: OFF}')
pause(2)
[lStartLoc, lEndLoc] = getLidarLines(yellow);
%telemetry = yellow.receive;
xDrive = 0;
yDrive = 0;
[coordinateLoc1,orientationLoc1] = localisation(lStartLoc/100,lEndLoc/100,gMap,xDrive,yDrive);
%driveToPosition(0,0,pi,yellow);

% % this section needs testing
%     telemetry = yellow.receive;
%     robotCoordinate = int8(zeros(1,2));
%     robotCoordinate(1,2)= int8(round(telemetry.odometry.pose.x*10));
%     robotCoordinate(1,1)= int8(round(telemetry.odometry.pose.y*10));
%     orientation= (telemetry.odometry.pose.alpha)
%     
%     lStart = round(lStartLoc/100);
%     lEnd = round(lEndLoc/100);
%     [LocLMap,LocZeroPoint]= localMap(lStart,lEnd,orientation,1);
%     yellowString = sprintf('correctedPose: { x: %f, y: %f, alpha: %f}',LocZeroPoint(2)*0.1,LocZeroPoint(1)*0.1,0);
%     yellow.set(yellowString);
%     bwDist = LocLMap;
%     %bwDist(bwDist==200)=255;
%     se = strel('square',3);
%     bwDist1 = imerode(double(bwDist),se);
%     bwDist1(LocLMap==200)=200;
%     bwDist2 = bwDist1;
%     bwDist2(bwDist1==200)=0;
%     figure(2100)
%     imshow(mat2gray(bwDist1));
%     title('map in map In Localisation')
%     LocPoint = bestSpot(bwDist1)
%     if(~(LocPoint(1)==0 && (LocPoint(2)==0)))
%         viaPoints=navToPoint(bwDist2,double([LocPoint(2) LocPoint(1)]).*0.1,0.1,[LocZeroPoint(1) LocZeroPoint(2)].*0.1,[telemetry.odometry.pose.y telemetry.odometry.pose.x])
%         followPath(viaPoints,yellow)        
%     end
%     xDrive = int8(round(telemetry.odometry.pose.x*10))-robotCoordinate(1,2);
%     yDrive = int8(round(telemetry.odometry.pose.y*10))-robotCoordinate(1,1);
%     [lStartLoc, lEndLoc] = getLidarLines(yellow);
%     [coordinateLoc1,orientationLoc1] = localisation(lStartLoc/100,lEndLoc/100,gMap,xDrive,yDrive);
%     %until here needs testing



    coordinateLoc2 = coordinateLoc1*0.1;
    yellowString = sprintf('correctedPose: { x: %f, y: %f, alpha: %f}',coordinateLoc2(2),coordinateLoc2(1),(orientationLoc1/180 *pi));
    yellow.set(yellowString);
    

end






