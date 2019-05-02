function [globalMap3,globalMapZeroPoint1] = globalMap(lStart1,lEnd1,robotCoordinate,orientation)

persistent firstFlag;
persistent globalMap1;
persistent globalMapZeroPoint;
persistent oldGMapZp;
persistent oldZeroPoint;

if isempty(firstFlag)
        firstFlag = 0;
end
%get local map
[map,zeroPoint] = localMap(lStart1,lEnd1,orientation,1);
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


%% Calculat new map size and where the local map and old global Map has to be placed
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
    end  

    gMapStart(2)= globalMapZeroPoint(2)-(oldGMapZp(2));
    startPoint(2)= globalMapZeroPoint(2)+robotCoordinate(1,1)-zeroPoint(2);
    endPoint(2)= globalMapZeroPoint(2)+robotCoordinate(1,1)-zeroPoint(2)+mapSize(2);
end

if(robotCoordinate(1,2)<0)
    newSize(1) = abs(robotCoordinate(1,2))+zeroPoint(1)+globalMapSize(1)-globalMapZeroPoint(1);

     if(globalMapZeroPoint(1)<abs(robotCoordinate(1,2))+zeroPoint(1))
        globalMapZeroPoint(1)=abs(robotCoordinate(1,2))+zeroPoint(1);
    end
    gMapStart(1)= globalMapZeroPoint(1)-(oldGMapZp(1));
    startPoint(1)= globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1);
    endPoint(1)= globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1)+mapSize(1);

end

%%

%check that new Map size is not smaller than old global Map
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
   oldZeroPoint = zeroPoint;

    mapBuffer(gMapStart(1)+1:gMapStart(1)+globalMapSize(1),gMapStart(2)+1:gMapStart(2)+globalMapSize(2)) = globalMap1;
    rcount = 1;
    ccount = 1;
    if(endPoint(1) > bufferSize(1))
        endPoint(1)=bufferSize(1);
    end
    if(endPoint(2) > bufferSize(2))
        endPoint(2)=bufferSize(2);
    end
   
    %merge old global map and local map to new global Map
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


globalMap1 = mapBuffer;
globalMap3 = globalMap1;
globalMapZeroPoint1=[globalMapZeroPoint(2) globalMapZeroPoint(1)];


end

