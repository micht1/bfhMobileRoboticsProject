%%returns viaPoints between start and endPoints. Start adn end point are
%%not included in the returned vector

function viaPoints = navToPoint(Map,target,meterPerPixel,mapCenterPoint,startPoint)
figure(300)
%imshow(mat2gray(Map));
tic
%mapCenterPoint
map =Map;
startPoint;
mapCenterPoint;
startPoint = startPoint+mapCenterPoint;
target1 = round((target)/meterPerPixel);
startPoint1 = round((startPoint)/meterPerPixel)
changedToWhite = false;
if(~(map(startPoint1(2),startPoint1(1))==1))
    map(startPoint1(2),startPoint1(1))=1;
    changedToWhite=true;
end
%map(startpoint1(2)-1:startpoint1(2)+1,startpoint1(1)-1:startpoint1(1)+1)=[1 1 1; 1 1 1; 1 1 1];


prm = PRM(~map);
prm.plan('npoints',100,'distthresh',30);
pathVector = prm.query(startPoint1,target1);
prm.plot()
% figure(1)
% dx = DXform(~map);   % create navigation object
% dx.plan(target1);       % create plan for specified goal
% pathVector=dx.query(startPoint1)

% 
viaPoints= pathVector*meterPerPixel;
%viaPoints(1,:) = startPoint;

%figure(200)
%imshow(mat2gray(dx.distancemap))

diffPoints= diff(viaPoints);
pointAngle = ones(length(diffPoints)+1,1)*123456;

pointAngle(1)=0;
pointAngle(end)=0;
%pointAngle(1:end-1)=atan2(diffPoints(:,2),diffPoints(:,1))
% tmpDiff = circshift(pointAngle,-1);
% 
% [foundWayPoints]=find(~(abs(pointAngle-tmpDiff)<10^-1));
% wayPoints = zeros(length(foundWayPoints)+1,1);
% wayPoints(1:end-1) = foundWayPoints;
% wayPoints(end)=length(pointAngle)
% if(isempty(wayPoints))
%     wayPoints=[1 0]
% end
% viaPoints= [viaPoints(wayPoints(2:end),:) circshift(pointAngle(wayPoints(2:end)),0)];
% viaPoints(end,:) = [target 0];
% 
% viaPoints(:,3) = (viaPoints(:,3))

% circshift(pointAngle(waypoints),-1)
% for pntCnt =2:length(diffPoints)
%     if()
%     end
% end
viaPoints= [viaPoints pointAngle];
viaPoints(:,1:2) = viaPoints(:,1:2)-mapCenterPoint;

if(changedToWhite==true)
    map(startPoint1(2),startPoint1(1))=0;
end
%viaPoints(1:end,1:2)+mapCenterPoint 

toc
%dx.plot()
end
