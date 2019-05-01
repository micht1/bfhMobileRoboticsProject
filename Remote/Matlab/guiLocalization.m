function [coordinateLoc1,orientationLoc1]=guiLocalization

if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;   
end

gMap = load('mapFile','gMap')
loadedMap = load('mapFile','loadedMap')

yellow.set('state{stateName: OFF}')
pause(2)
[lStartLoc, lEndLoc] = getLidarLines(yellow);
%telemetry = yellow.receive;
[coordinateLoc1,orientationLoc1] = localisation(lStartLoc/100,lEndLoc/100,gMap,xDrive,yDrive);
%driveToPosition(0,0,pi,yellow);

end






