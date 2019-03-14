function [lAngle, lDistance, lQuality] = getLidar(yellow)
%getLidar   Get lidat data
%  [lAngle, lDistance, lQuality] = getLidar(yellow) requests that 'yellow' make a LIDAR
%  measurement. The points delivered are returned in an array of lAngle, lDistance and lQuality points.

% Request Lidar data every '10' degrees
yellow.set('requestLidarData: 10');
% Wait for lidar data to arrive
while 1
    telemetry = yellow.receive();
    if (~isempty(telemetry.lidar))
        break
    end
    pause(0.1)
end

% Parse Lidar data (stored as Java ArrayList)
n = telemetry.lidar.points.size();
lAngle = zeros(n,1);
lDistance = zeros(n,1);
lQuality = zeros(n,1);
for k = 1:n
    p = telemetry.lidar.points.get(k-1);
    lAngle(k) = p.angle;
    lDistance(k) = p.distance;
    lQuality(k) = p.quality;
end

% Remove points that are too far away (e.g. 9000 mm)
row = find(lDistance > 9000);
lAngle(row) = [];
lDistance(row) = [];
lQuality(row) = [];
end
