function [atPos,telemetry] = isAtPosition(x,y,alpha,tolerance,yellow)
telemetry = yellow.receive;
atPos=false;
stateStr = telemetry.state.toString;
if(strcmp(stateStr,'State = OFF'))
    if((abs(telemetry.odometry.pose.x-x)<tolerance) & (abs(telemetry.odometry.pose.y-y)<tolerance))
        %if(abs(telemetry.odometry.pose.alpha-alpha)<tolerance*1.2)
            atPos=true;
        %end   
    end
end

end