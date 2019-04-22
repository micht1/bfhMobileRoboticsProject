
function [coordinate,orientation] = localisation(lStart,lEnd,globalMap)

%orientation = 0;

sizeGmap = size(globalMap);
globalIm = mat2gray(globalMap);
persistent possibilityMap

if isempty(possibilityMap)
possibilityMap = zeros(sizeGmap(1),sizeGmap(2)); 
for y = 1:sizeGmap(1)
   for x = 1:sizeGmap(2)
       if(globalMap(y,x)==255)
          possibilityMap(y,x) = 1;
       end
    end
end
end

% figure(222)
% imshow(possibilityMap)
% 
% c = 0;
match = [0,0,0,0];
cnt = 1;
for angle = -180:1:180

[map,localZeroPoint] = localMap(lStart,lEnd,double((pi()/180)*angle),0);
localIm= mat2gray(map);

sizeLmap = size(map);

if(sizeLmap(1)<=sizeGmap(1) & sizeLmap(2)<=sizeGmap(2))
cnew = normxcorr2(localIm,globalIm);
[ypeak, xpeak] = find(cnew==max(cnew(:)));
y = ypeak(1)-size(localIm,1)+localZeroPoint(1);
x = xpeak(1)-size(localIm,2)+localZeroPoint(2);
kernel = [0.5,0.75,0.5;0.75,1,0.75;0.5,0.75,0.5];

    for column = -1:1
        for row = -1:1     
            match(cnt,1)=y+column;
            match(cnt,2)=x+row;
            match(cnt,3)=max(cnew(:))*kernel(column+2,row+2);
            match(cnt,4) = angle;
            cnt = cnt+1;
        end
    end
end
%     if(max(cnew(:))>max(c(:)))
%         c = cnew;
%         zeroPoint = localZeroPoint;
%         orientation = angle;
%     end
end

matchSize=size(match);
posSize = size(possibilityMap);
for cnt = 1:matchSize(1)
    if((match(cnt,1)>0) & (match(cnt,2)>0))
        if((match(cnt,1)<posSize(1)) & (match(cnt,2)<posSize(2)))
            possibilityMap(match(cnt,1),match(cnt,2)) = possibilityMap(match(cnt,1),match(cnt,2))+match(cnt,3)*possibilityMap(match(cnt,1),match(cnt,2));
        end
    end
end


maxP = max(possibilityMap);
possibilityMap = possibilityMap./max(maxP);

[yPoint,xPoint] = find(possibilityMap==max(max(possibilityMap)));
[column,row] = find(match==max(match(:,3)));




% figure(3)
% imshow(possibilityMap)

% figure(8), surf(c), shading flat
% [ypeak, xpeak] = find(c==max(c(:)));

% ypeak = match(column,1);
% xpeak = match(column,2);
% 
% yoffSet = ypeak-size(localIm,1);
% xoffSet = xpeak-size(localIm,2);


coordinate = [0,0];
% coordinate(2) = match(column,1);
% coordinate(1) = match(column,2);

coordinate(2) = yPoint;
coordinate(1) = xPoint;

% coordinate = zeros(length(column),2);
% coordinate(:,2) = match(column,1);
% coordinate(:,1) = match(column,2);

orientation = match(column,4);

end


