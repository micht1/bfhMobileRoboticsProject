function [map,mapZeroPoint] = mapping

if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;
    
end

clear 'globalMap'
yellowString = sprintf('correctedPose: { x: %f, y: %f, alpha: %f}',0,0,0);
yellow.set(yellowString);
pause(2);
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
    %bwDist(bwDist==200)=255;
    se = strel('square',3);
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
            map = gMap;
            mapZeroPoint = zeroPoint;
            break;
        end
    end
%     bwDist(point(1),point(2))=100;
% %     figure(1000)
% %     imshow(bwDist)
    viaPoints=navToPoint(bwDist2,double([point(2) point(1)]).*0.1,0.1,[zeroPoint(1) zeroPoint(2)].*0.1,[telemetry.odometry.pose.y telemetry.odometry.pose.x]);
    
    viaCnt=1;
    matSize=size(viaPoints);
    
    oldPose = [0 0 0];
    while(viaCnt<=matSize(1))
        pause(0.5);
        telemetry = yellow.receive;
        oldPose = [telemetry.odometry.pose.x telemetry.odometry.pose.y telemetry.odometry.pose.alpha];
        driveToPosition(viaPoints(viaCnt,2),viaPoints(viaCnt,1),viaPoints(viaCnt,3),yellow);
        waitForResending = 3;
        atPos = false;
        
        %pause(10);
        while(atPos==false)
            
            [atPos,telemetry]=isAtPosition(viaPoints(viaCnt,2),viaPoints(viaCnt,1),viaPoints(viaCnt,3),0.05,yellow);
            pause(0.5);
            actualPose = [telemetry.odometry.pose.x telemetry.odometry.pose.y telemetry.odometry.pose.alpha];
            if(waitForResending<1 & (norm(actualPose(1:2)-oldPose(1:2)))<0.01)
                driveToPosition(viaPoints(viaCnt,2),viaPoints(viaCnt,1),viaPoints(viaCnt,3),yellow);
                waitForResending = 3;
            else
                waitForResending = waitForResending-1;
            end
        end
        viaCnt=viaCnt+1;
    end
    
    %doMapping=false;
    
end


end