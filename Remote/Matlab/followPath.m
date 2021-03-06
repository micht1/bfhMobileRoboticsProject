%follows path. pathVector is a 3xN Vector containing[x y alpha]. And the Object of the Yellow
%resends move command when robot hasnt moved
function followPath(pathVector,yellow)
 viaCnt=1;
matSize=size(pathVector)
%for all points in pathVector drive to point
while(viaCnt<=matSize(1))
    pause(0.5);
    telemetry = yellow.receive;
    oldPose = [telemetry.odometry.pose.x telemetry.odometry.pose.y telemetry.odometry.pose.alpha]
    driveToPosition(pathVector(viaCnt,2),pathVector(viaCnt,1),pathVector(viaCnt,3),yellow);
    waitForResending = 3;
    atPos = false;
    
    %when not at target pos wait and check if robot is moving. if not send
    %move command again
    while(atPos==false)
        
        [atPos,telemetry]=isAtPosition(pathVector(viaCnt,2),pathVector(viaCnt,1),pathVector(viaCnt,3),0.05,yellow);
        pause(0.5);
        actualPose = [telemetry.odometry.pose.x telemetry.odometry.pose.y telemetry.odometry.pose.alpha];
        if(waitForResending<1 & (norm(actualPose(1:2)-oldPose(1:2)))<0.01)
            driveToPosition(pathVector(viaCnt,2),pathVector(viaCnt,1),pathVector(viaCnt,3),yellow);
            waitForResending = 3;
        else
            waitForResending = waitForResending-1;
        end
    end
    viaCnt=viaCnt+1;
end
end