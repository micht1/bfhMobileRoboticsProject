% clearvars; clear all; close all; clc
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% lStart1 = round([-1000 ,-2000;2000,-2000;2000,2000;  100,1500;-600 ,1000;-1000, 1000]/100);
% lEnd1 =   round([2000  ,-2000;2000, 2000;1500,2000;  500,1500;-1000,1000;-1000,-2000]/100);

%   lStart1 = round([-700 ,700; 1400, 700; 2500,-1500; 2500,-2600; -500,-2600; -700,-2600; -200,-1000]/100);
%   lEnd1 =   round([1400 ,700; 1400,-900; 2500,-2600; 2300,-2600; -700,-2600; -700,  700;  900,-1000]/100);

% lStart1=round([1000,1000;-1000, 1000;-1000,-1000;1000,-1000]/100);
% lEnd1=round([-1000,1000; -1000,-1000; 1000,-1000;1000,1000]/100);

<<<<<<< HEAD:Remote/Matlab/globalMapTest.m
 robotCoordinate = [0,0,0;0,0,pi();25,25,0;100,100,pi()/2;75,0,pi();-50,-50,pi/2];
=======
%  robotCoordinate = [0,0,0;-100,1,pi();25,25,0;100,100,pi()/2;75,0,pi();-50,-50,pi/2];
>>>>>>> d839660c9e0792d76d526a81a1447a0cc4134b97:Remote/Matlab/globalMap.m
%globalMap1 = 200;
%newSize = [0,0];

%startPoint = [0,0];
%endPoint = [0,0];
%oldZeroPoint = [0,0];
%newZeroPoint = [0,0];
% for x = 1:2
% gMap = globalMap2(lStart1,lEnd1,robotCoordinate(x,:));
% figure(10)
% imshow(gMap)
% end

clear 'globalMap2'


function globalMap3 = globalMap2(lStart1,lEnd1,robotCoordinate)
persistent firstFlag;
persistent globalMap1;
persistent globalMapZeroPoint;
persistent oldGMapZp;
persistent oldZeroPoint;

if isempty(firstFlag)
        firstFlag = 0;
end

[map,zeroPoint] = localMap(lStart1,lEnd1,robotCoordinate(1,3));
figure(1)
imshow(map)

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
    gMapStart(2)= globalMapZeroPoint(2)-oldGMapZp(2);
<<<<<<< HEAD:Remote/Matlab/globalMapTest.m
    if(globalMapZeroPoint(2)+robotCoordinate(1,1)<zeroPoint(2))    
        globalMapZeroPoint(2) = zeroPoint(2);   
        newSize(2) = robotCoordinate(1,1)+globalMapZeroPoint(2)+(globalMapSize(2)-oldGMapZp(2));
        gMapStart(2)= globalMapZeroPoint(2)-oldGMapZp(2)%-robotCoordinate(1,1);
=======
    if(globalMapZeroPoint(2)+robotCoordinate(1,1)<zeroPoint(2))
        globalMapZeroPoint(2) = zeroPoint(2);
        newSize(2) = robotCoordinate(1,1)+globalMapZeroPoint(2)+(globalMapSize(2)-oldGMapZp(2));
        gMapStart(2)= globalMapZeroPoint(2)-oldGMapZp(2);%-robotCoordinate(1,1);
>>>>>>> d839660c9e0792d76d526a81a1447a0cc4134b97:Remote/Matlab/globalMap.m
    end

    startPoint(2)= globalMapZeroPoint(2)+robotCoordinate(1,1)-zeroPoint(2);
    endPoint(2) = globalMapZeroPoint(2)+robotCoordinate(1,1)-zeroPoint(2)+mapSize(2);

end

if(robotCoordinate(1,2)>=0)

    newSize(1) = robotCoordinate(1,2)+mapSize(1)-(zeroPoint(1)-globalMapZeroPoint(1));
    gMapStart(1)= globalMapZeroPoint(1)-oldGMapZp(1);
<<<<<<< HEAD:Remote/Matlab/globalMapTest.m
    if(globalMapZeroPoint(1)+robotCoordinate(1,2)<zeroPoint(1))    
        globalMapZeroPoint(1) = zeroPoint(1);     
        newSize(1) = robotCoordinate(1,2)+globalMapZeroPoint(1)+(globalMapSize(1)-oldGMapZp(1));
        gMapStart(1)= globalMapZeroPoint(1)-oldGMapZp(1)%-robotCoordinate(1,2);
=======
    if(globalMapZeroPoint(1)+robotCoordinate(1,2)<zeroPoint(1))
        globalMapZeroPoint(1) = zeroPoint(1);
        newSize(1) = robotCoordinate(1,2)+globalMapZeroPoint(1)+(globalMapSize(1)-oldGMapZp(1));
        gMapStart(1)= globalMapZeroPoint(1)-oldGMapZp(1);%-robotCoordinate(1,2);
>>>>>>> d839660c9e0792d76d526a81a1447a0cc4134b97:Remote/Matlab/globalMap.m
    end

    startPoint(1)= globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1);
<<<<<<< HEAD:Remote/Matlab/globalMapTest.m
    endPoint(1) = globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1)+mapSize(1);  

end
=======
    endPoint(1) = globalMapZeroPoint(1)+robotCoordinate(1,2)-zeroPoint(1)+mapSize(1);

end

if(robotCoordinate(1,1)<0)
    newSize(2) = abs(robotCoordinate(1,1))+zeroPoint(2)+globalMapSize(2)-globalMapZeroPoint(2);
>>>>>>> d839660c9e0792d76d526a81a1447a0cc4134b97:Remote/Matlab/globalMap.m

    if(globalMapZeroPoint(2)<abs(robotCoordinate(1,1))+zeroPoint(2))
        globalMapZeroPoint(2)=abs(robotCoordinate(1,1))+zeroPoint(2);
%         newZeroPoint(2) = robotCoordinate(x,1)
<<<<<<< HEAD:Remote/Matlab/globalMapTest.m
    end  
=======
    end
>>>>>>> d839660c9e0792d76d526a81a1447a0cc4134b97:Remote/Matlab/globalMap.m
    gMapStart(2)= globalMapZeroPoint(2)-(oldGMapZp(2))
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

mapBuffer = uint8(zeros(newSize(1),newSize(2))+200);
bufferSize = size(mapBuffer);
figure(3)
imshow(mapBuffer)
<<<<<<< HEAD:Remote/Matlab/globalMapTest.m
    
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
    
    
    if(endPoint(1) >bufferSize(1))
        endPoint(1) = bufferSize(1);
    end
    
    if(endPoint(2) >bufferSize(2))
        endPoint(2) = bufferSize(2);
    end
%     
=======

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
>>>>>>> d839660c9e0792d76d526a81a1447a0cc4134b97:Remote/Matlab/globalMap.m
    figure(2)
    imshow(mapBuffer)
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


end
