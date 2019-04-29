function map = mapping

if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;
    
end

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
    bwDist(bwDist==200)=255;
    se = strel('square',4);
    bwDist1 = imerode(double(bwDist),se);
    bwDist1(gMap==200)=200;
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
end