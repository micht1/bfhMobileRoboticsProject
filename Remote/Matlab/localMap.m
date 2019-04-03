% clearvars; clear all; close all; clc
% load('workspaceVariables.mat')

function map = localMap(lStart,lEnd,orientation) 
% localMap1 = imread("occupancyGrid_1.bmp");
% localMap1 = imcomplement(localMap1);
load('workspaceVariables.mat')
freeSpace = 5;
sizeKernel = 3;
%imshow(localMap1);

t = cputime;
robotCoordinate = [0,0];

%% Draw local Map as Matrix
angle = atan2(lEnd(1,1)-lStart(1,1),lEnd(1,2)-lStart(1,2));
R = Rz(angle+orientation)*Rx(pi());
L = [0,0,0]';
Tmat=TraMat3D(R,L);

if(angle~=0)
  for x = 1:size(lStart)     
    rStart = [lStart(x,2),lStart(x,1),0,1]*Tmat;
    lStart(x,1) = round(rStart(1)); 
    lStart(x,2) = round(rStart(2)); 
    
    rEnd = [lEnd(x,2),lEnd(x,1),0,1]*Tmat;
    lEnd(x,1) = round(rEnd(1)); 
    lEnd(x,2) = round(rEnd(2));      
  end  
end

if(min(min(lEnd(:,2),lStart(:,2)))<0)
    minX = abs(min(min(lEnd(:,2),lStart(:,2))))+freeSpace;
else
    minX = freeSpace;
end

if(min(min(lEnd(:,1),lStart(:,1)))<0)
    minY = abs(min(min(lEnd(:,1),lStart(:,1))))+freeSpace;
else
    minY = freeSpace;
end

lStart(:,1)=lStart(:,1)+abs(minY);
lStart(:,2)=lStart(:,2)+abs(minX);

lEnd(:,1)=lEnd(:,1)+abs(minY);
lEnd(:,2)=lEnd(:,2)+abs(minX);

robotCoordinate(1) = robotCoordinate(:,1)+abs(minY);
robotCoordinate(2) = robotCoordinate(:,2)+abs(minX);

minX = min(min(lEnd(:,2),lStart(:,2)))-freeSpace;
minY = min(min(lEnd(:,1),lStart(:,1)))-freeSpace;
maxX = max(max(lEnd(:,2),lStart(:,2)))+freeSpace;
maxY = max(max(lEnd(:,1),lStart(:,1)))+freeSpace;

localMap2 = uint8(zeros(maxY,maxX)+200);

for k = 1:size(lStart())
   direction=(lEnd(k,:)-lStart(k,:))/1000;
   newPoint = lStart(k,:);
   lineArray = zeros(2,2);
   cnt = 1;
   
   while (round(newPoint(1,1)) ~= lEnd(k,1))     
     newPoint = newPoint + direction;
     localMap2(round(newPoint(1,1)),round(newPoint(1,2)))=0;
     cnt = cnt+1;
   end
   while (round(newPoint(1,2)) ~= lEnd(k,2))     
     newPoint = newPoint + direction;
     localMap2(round(newPoint(1,1)),round(newPoint(1,2)))=0;
     cnt = cnt+1;
   end

end
linePoints = zeros(2,2);   
cnt = 1;
sizeMap = size(localMap2);
for y = 1:sizeMap(1)
    for x = 1:sizeMap(2)     
        if(localMap2(y,x) == 0)
           linePoints(cnt,1) = y;
           linePoints(cnt,2) = x;
           cnt = cnt+1;
        end
    end
end

for k = 1:size(linePoints)
   direction=(robotCoordinate-linePoints(k,:))/1000;
   newPoint = linePoints(k,:);
   lineArray = zeros(2,2);
   cnt = 1;
   sCnt = 1;
   
   while (round(newPoint(1,1)) ~= robotCoordinate(1,1))     
     newPoint = newPoint + direction;
     if(localMap2(round(newPoint(1,1)),round(newPoint(1,2)))~=0)
     localMap2(round(newPoint(1,1)),round(newPoint(1,2)))=255;
     end   
     cnt = cnt+1;
   end
   while (round(newPoint(1,2)) ~= robotCoordinate(1,2))     
     newPoint = newPoint + direction;
     if(localMap2(round(newPoint(1,1)),round(newPoint(1,2)))~=0)
     localMap2(round(newPoint(1,1)),round(newPoint(1,2)))=255;
     end
     cnt = cnt+1;
   end
end

cnt = 1;
whiteSector = zeros(2,2);
for y = 1:sizeMap(1)
    for x = 1:sizeMap(2)     
        if(localMap2(y,x) == 255)
           whiteSector(cnt,1) = y;
           whiteSector(cnt,2) = x;
           cnt = cnt+1;
        end
    end
end


for k = 1: size(whiteSector)
    surroundings = getSurroundings(sizeKernel,whiteSector(k,:),localMap2);
    if(surroundings(1,:) <255 & surroundings(3,:)<255 & surroundings(2,1) <255 & surroundings(2,3) <255)
    localMap2(whiteSector(k,1),whiteSector(k,2))=200;
    end
end

localMap2(robotCoordinate(1),robotCoordinate(2)) = 230;
% time = cputime-t
% imshow(localMap2)

map = localMap2;
end




function kernel = getSurroundings(sizeKernel,currentPosition,map)
kernel= zeros(sizeKernel,sizeKernel);
for n = 1:sizeKernel
    for i = 1:sizeKernel    
         kernel(n,i) = map(currentPosition(1)-(sizeKernel-1-n),currentPosition(2)-(sizeKernel-1-i));
    end  
end
end


