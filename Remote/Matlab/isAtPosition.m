function atPos = isAtPosition(x,y,alpha,tolerance,yellow)
telemetry = yellow.receive;
if((abs(telemetry.odometry.pose.x-x)<tolerance) & abs(telemetry.odometry.pose.y-y)<tolerance))
    if(abs(telemetry.odometry.pose.alpha-alpha)<tolerance)
        atPos=true;
    end
else
    atPos=false;
end
end