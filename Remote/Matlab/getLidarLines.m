function [lStart, lEnd] = getLidarLines(yellow)
%getLidarLines   Get lidat line data
%  [lStart, lEnd] = getLidarLines(yellow) requests that 'yellow' make a LIDAR
%  measurement and line analysis. The lines delivered are returned in an
%  array of lStart and lEnd points.

% Request Lidar lines with default parameters
yellow.set('requestLidarLines{}');
% You may use different parameters as defined in yellow.proto:
% > yellow.set('requestLidarLines{minRangeDistance:500, maxLineImprecision:50, maxAngleBetweenLines:150}');

% Wait for lidar line data to arrive
while 1
    telemetry = yellow.receive;
    if (~isempty(telemetry.lidarLines))
        break
    end
end

% Parse Lidar data (stored as Java ArrayList)
n = telemetry.lidarLines.lines.size;
lStart = zeros(n,2);
lEnd = zeros(n,2);
for k = 1:n
    p = telemetry.lidarLines.lines.get(k-1);
    lStart(k,:) = [p.start.x p.start.y];
    lEnd(k,:) = [p.end.x p.end.y];
end

end
