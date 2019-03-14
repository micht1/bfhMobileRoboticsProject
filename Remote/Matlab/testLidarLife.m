if(~exist('yellow'))
    
    global States;
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
    
    % Connect to the robot
    yellow = SerialClient.getInstance;
    
end

figure(1)
while (1)
    tic
    [lAngle, lDistance, lQuality] = getLidar(yellow);
toc
% Plot lidar data
x = lDistance.*cos(lAngle*pi/180);
y = lDistance.*sin(lAngle*pi/180);
scatter(x, y, 20, lQuality, 'filled');
colorbar
grid on
axis([-1000 1000 -1000 1000])
pause(0.1);

end
