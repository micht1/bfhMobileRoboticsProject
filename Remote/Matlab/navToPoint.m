%%returns viaPoints between start and endPoints. Start adn end point are
%%not included in the returned vector

function viaPoints = navToPoint(Map,target,meterPerPixel,mapCenterPoint,startPoint)
tic
map =Map;
target = target+mapCenterPoint;
startPoint = startPoint+mapCenterPoint;
target1 = round((target)/meterPerPixel);
startPoint1 = round((startPoint)/meterPerPixel);
se = strel('diamond',1);
bwDist = imerode(~double(map),se);
figure(2)
imshow(mat2gray(bwDist));


% prm = PRM(map);
% prm.plan('npoints',60,'distthresh',40);
% pathVector = prm.query(startPoint1,target1);
% prm.plot()
figure(1)
dx = DXform(~bwDist);   % create navigation object
dx.plan(target1);       % create plan for specified goal
pathVector=dx.query(startPoint1,'animate');

% 
viaPoints= pathVector*meterPerPixel;
viaPoints(1,:) = startPoint;
viaPoints(end,:) = target
%figure(200)
%imshow(mat2gray(dx.distancemap))

diffPoints= diff(viaPoints);
pointAngle=atan2(diffPoints(:,2),diffPoints(:,1));
tmpDiff = circshift(pointAngle,1);
[pointAngle tmpDiff];
[wayPoints]=find(~(abs(pointAngle-tmpDiff)<10^-5));
viaPoints= [viaPoints(wayPoints(2:end),:) circshift(pointAngle(wayPoints(2:end)-1),-1)]

% viaPoints(1:end,1:2)+mapCenterPoint 
% circshift(pointAngle(waypoints),-1)
% for pntCnt =2:length(diffPoints)
%     if()
%     end
% end




% tmpMap =double((~(Map)*inf));
% 
% tmpMap(isnan(tmpMap))=1;

% bwDist=mat2gray(bwDist);
% % %bwDist=bwulterode(Map)
% % % showMap=tmpMap;
% % % showMap(isinf(showMap))=255
% % figure(202)
% % title('original')
% % imshow(mat2gray(Map))
% % figure(201)
% % imshow(mat2gray(tmpMap))
% % figure(200)
% % imshow(mat2gray(bwDist))
% % sizes=size(Map);
% % 
% % [row,col]=find(bwDist>0.9);
% % 
% % pointsToChoose = randperm(length(row),20)
% % indexVector = [row(pointsToChoose) col(pointsToChoose)]
% %bwDist()
% 
% % targetx =int8(target(1,1)/10);
% % targety = int8(target(1,2)/10);
% % 
% % xtmp =  double([targetx:-1:1 0 1:1:(sizes(2)-targetx-1)]);
% % ytmp =  double([targety:-1:1 0 1:1:(sizes(1)-targety-1)]);
% % 
% % 
% % distanzMatrixTmp1 = ones(sizes);
% % distanzMatrixTmp1 = ytmp'.*distanzMatrixTmp1;
% 
% % distanzMatrixTmp2 = ones(sizes);
% % distanzMatrixTmp2 = xtmp.*distanzMatrixTmp2;
% % 
% % distanzMatrixTmp = sqrt(distanzMatrixTmp1.^2 + distanzMatrixTmp2.^2);
% % distanzMap = distanzMatrixTmp .*tmpMap
% % %distanzMatrixTmp = xtmp.*distanzMatrixTmp
% % %distanzMatrixTmp1(targety,targetx) = 1;
% % showMap = (distanzMap)*4;
% % showMap(isinf(showMap))=255
% % figure(2)
% % imshow(showMap./255)
% % %imshow(distanzMap)


toc
%dx.plot()
end
