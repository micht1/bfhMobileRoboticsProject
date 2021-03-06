
function [coordinate,orientation] = localisation(lStart,lEnd,globalMap,xDrive,yDrive)
sizeGmap = size(globalMap);
globalIm = mat2gray(globalMap);
persistent possibilityMap

%possibilityMap with 1 in white Sectors
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

%put possible spots to new coordinates of robot to improve localization =>
%not used 
for y = 1:sizeGmap(1)
    for x = 1:sizeGmap(2)
        
        if(y+yDrive > 0  & x+xDrive > 0 & y+yDrive < sizeGmap(1)  & x+xDrive > sizeGmap(2))        
        possibilityMap(y,x) = possibilityMap(y+yDrive,x+xDrive);       
        possibilityMap(y+yDrive,x+xDrive) = 0; 
        end
    end    
end

match = [0,0,0,0];
cnt = 1;

%Localization with local Map for every 1? step
for angle = -180:1:180

[map,localZeroPoint] = localMap(lStart,lEnd,double((pi()/180)*angle),0);
localIm= mat2gray(map);
sizeLmap = size(map);

%cross correlation and search of best matching point for actual local map
if(sizeLmap(1)<=sizeGmap(1) & sizeLmap(2)<=sizeGmap(2))
cnew = normxcorr2(localIm,globalIm);
[ypeak, xpeak] = find(cnew==max(cnew(:)));
y = ypeak(1)-size(localIm,1)+localZeroPoint(1);
x = xpeak(1)-size(localIm,2)+localZeroPoint(2);
kernel = [0.5,0.75,0.5;0.75,1,0.75;0.5,0.75,0.5];
%save Coordinates in match array
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
end

%check if best matching points are in white Sectors
%made a possibility Map with match Values
matchSize=size(match);
posSize = size(possibilityMap);
for cnt = 1:matchSize(1)
    if((match(cnt,1)>0) & (match(cnt,2)>0))
        if((match(cnt,1)<posSize(1)) & (match(cnt,2)<posSize(2)))
            possibilityMap(match(cnt,1),match(cnt,2)) = possibilityMap(match(cnt,1),match(cnt,2))+match(cnt,3)*possibilityMap(match(cnt,1),match(cnt,2));
        end
    end
end


%divide all Values with max Value to have a max of 1
maxP = max(possibilityMap);
possibilityMap = possibilityMap./max(maxP);

figure(11)
imshow(possibilityMap)

%find best match
[yPoint,xPoint] = find(possibilityMap==max(max(possibilityMap)));
[column,row] = find(match==max(match(:,3)));

coordinate = [0,0];

coordinate(2) = yPoint;
coordinate(1) = xPoint;

orientation = match(column,4);


end


