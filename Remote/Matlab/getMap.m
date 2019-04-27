function lMap = getMap

if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;   
end

yellow.set('state{stateName: OFF}')
    pause(2)
    [lStart, lEnd] = getLidarLines(yellow);
    telemetry = yellow.receive;
    orientation= (telemetry.odometry.pose.alpha);
    lStart1 = round(lStart/100);
    lEnd1 = round(lEnd/100);
    [map,zeroPoint] = localMap(lStart1,lEnd1,orientation,1);

lMap = map;
end