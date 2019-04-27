function [globalMap3,globalMapZeroPoint1] = globalMap(lStart1,lEnd1,robotCoordinate,orientation)

persistent firstFlag;
persistent globalMap1;
persistent globalMapZeroPoint;
persistent oldGMapZp;
persistent oldZeroPoint;

if isempty(firstFlag)
        firstFlag = 0;
end

[map,zeroPoint] = localMap(lStart1,lEnd1,orientation,1);
% figure(1)
% imshow(map)

if(firstFlag == 0)
  globalMapZeroPoint = zeroPoint;
  oldZeroPoint = zeroPoint;
  firstFlag = 1;
  globalMapSize = size(map);
  globalMap1 = 200;

else
  globalMapSize = size(globalMap1);
end
mapSize=size(map);
oldGMapZp = globalMapZeroPoint;
if(robotCoordinate(1,1)>=0)

    newSize(2) = robotCoordinate(1,1)+mapSize(2)-(zeroPoint(2)-globalMapZeroPoint(2));
    
    %test
    newSize(2) = globalMapZeroPoint(2)+robotCoordinate(1,1)+(mapSize(2)-zeroPoint(2));
    
    gMapStart(2)= globalMapZeroPoint(2)-oldGMapZp(2);
    if(globalMapZeroPoint(2)+robotCoordinate(1,1)<zeroPoint(2))
        globalMapZeroPoint(2) = zeroPoint(2);
        newSize(2) = robotCoordinate(1,1)+globalMapZeroPoint(2)+(globalMapSize(2)-oldGMapZp(2));
        gMapStart(2)= globalMapZeroPoint(2)-oldGMapZp(2);%-robotCoordinate(1,1);
    end

    startPoint(2)= globalMapZeroPoint(2)+robotCoordinate(1,1)-zeroPoint(2);
    endPoint(2) = globalMapZeroPoint(2)+robotCoordinate(1,1)-zeroPoint(2)+mapSize(2);

end

if(robotCoordinate(1,2)>=0)
    newSize(1) = robotCoordinate(1,2)+mapSize(1)-(zeroPoint(1)-globalMapZeroPoint(1));
    
    %test
    newSize(1) = globalMapZeroPoint(1)+robotCoordinate(1,2)+(mapSize(1)-zeroPoint(1));
    
    gMapStart(1)= globalMapZeroPoint(1)-oldGMapZp(1);
    if(globalMapZeroPoint(1)+robotCoordinate(1,2)<zeroPoint(1))
        globalMapZeroPoint(1) = zeroPoint(1);
        newSize(1) = robotCoordinate(1,2)+globalMapZeroPoint(1)+(globalMapSize(1)-oldGMapZp(1));
        gMapStart(1)= globalMapZeroPoint(1)-oldGMapZp(1);%-robotCoordinate(1,2);
    end

    startPoint(1)= globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1);
    endPoint(1) = globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1)+mapSize(1);  
end


if(robotCoordinate(1,1)<0)
    newSize(2) = abs(robotCoordinate(1,1))+zeroPoint(2)+globalMapSize(2)-globalMapZeroPoint(2);
    if(globalMapZeroPoint(2)<abs(robotCoordinate(1,1))+zeroPoint(2))
        globalMapZeroPoint(2)=abs(robotCoordinate(1,1))+zeroPoint(2);
%         newZeroPoint(2) = robotCoordinate(x,1)
    end  

    gMapStart(2)= globalMapZeroPoint(2)-(oldGMapZp(2));
    startPoint(2)= globalMapZeroPoint(2)+robotCoordinate(1,1)-zeroPoint(2);
    endPoint(2)= globalMapZeroPoint(2)+robotCoordinate(1,1)-zeroPoint(2)+mapSize(2);
end

if(robotCoordinate(1,2)<0)
    newSize(1) = abs(robotCoordinate(1,2))+zeroPoint(1)+globalMapSize(1)-globalMapZeroPoint(1);

     if(globalMapZeroPoint(1)<abs(robotCoordinate(1,2))+zeroPoint(1))
        globalMapZeroPoint(1)=abs(robotCoordinate(1,2))+zeroPoint(1);
%         newZeroPoint(1) = robotCoordinate(x,2);
    end
    gMapStart(1)= globalMapZeroPoint(1)-(oldGMapZp(1));
    startPoint(1)= globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1);
    endPoint(1)= globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1)+mapSize(1);

end

   
if(newSize(1)<globalMapSize(1))
     newSize(1) = globalMapSize(1);
end
if(newSize(2)<globalMapSize(2))
     newSize(2) = globalMapSize(2);
end

newSize(1) = newSize(1)+5;
newSize(2) = newSize(2)+5;

mapBuffer = uint8(zeros(newSize(1),newSize(2))+200);
bufferSize = size(mapBuffer);
% figure(3)
% imshow(mapBuffer)
     

% if(robotCoordinate(1,2)>=0)
%     gMapStart(1)= globalMapZeroPoint(1)-oldGMapZp(1)-robotCoordinate(1,2);
% else
%     gMapStart(1)= globalMapZeroPoint(1)-(oldGMapZp(1));
% end
%
% if(robotCoordinate(1,1)>=0)
%     %
%     gMapStart(2)= globalMapZeroPoint(2)-oldGMapZp(2)-robotCoordinate(1,1);
% else
%     gMapStart(2)= globalMapZeroPoint(2)-(oldGMapZp(2));  %bufferSize(2)-globalMapSize(2);
% end

   oldZeroPoint = zeroPoint;

    mapBuffer(gMapStart(1)+1:gMapStart(1)+globalMapSize(1),gMapStart(2)+1:gMapStart(2)+globalMapSize(2)) = globalMap1;
    %oldZeroPoint = zeroPoint;
    rcount = 1;
    ccount = 1;
    if(endPoint(1) > bufferSize(1))
        endPoint(1)=bufferSize(1);
    end
    if(endPoint(2) > bufferSize(2))
        endPoint(2)=bufferSize(2);
    end
    
%     figure(2)
%     imshow(mapBuffer)
    for c = startPoint(1)+1:endPoint(1)
        for r = startPoint(2)+1:endPoint(2)
            if(mapBuffer(c,r) == 200)
                mapBuffer(c,r) = map(ccount,rcount);

            elseif(mapBuffer(c,r) == 255 && map(ccount,rcount) == 0)
                mapBuffer(c,r) = map(ccount,rcount);
            end
            rcount = rcount+1;
        end
        rcount = 1;
        ccount = ccount+1;
    end

% mapBuffer(globalMapZeroPoint(1),globalMapZeroPoint(2))= 220;
globalMap1 = mapBuffer;
% figure(4)
% imshow(globalMap1)
globalMap3 = globalMap1;
globalMapZeroPoint1=[globalMapZeroPoint(2) globalMapZeroPoint(1)];


end

