%clearvars; clear all; close all; clc
% lStart1 = round(lStart/100);
% lEnd1 = round(lEnd/100);
% lStart1 = round([-1000 ,-2000;2000,-2000;2000,2000;  100,1500;-600 ,1000;-1000, 1000]/100);
% lEnd1 =   round([2000  ,-2000;2000, 2000;1500,2000;  500,1500;-1000,1000;-1000,-2000]/100);

 lStart1 = round([-700 ,700; 1400, 700; 2500,-1500; 2500,-2600; -500,-2600; -700,-2600; -200,-1000]/100);
 lEnd1 =   round([1400 ,700; 1400,-900; 2500,-2600; 2300,-2600; -700,-2600; -700,  700;  900,-1000]/100);

% lStart1=round([1000,1000;-1000,-1000]/100);
% lEnd1=round([-1000,1000; 1000,-1000]/100);


robotCoordinate = [0,0,0;50,50,pi();25,25,0;100,100,0;-75,-75,0;0,-50,0];
%mapZeroPoint = [0,0];
% oldZeroPoint = [0,0];

globalMap1 = 200;
newSize = [0,0];
firstFlag = 0;
newZeroPoint = [0,0];
startPoint = [0,0];
endPoint = [0,0];
oldZeroPoint = [0,0];

% globalMapZeroPoint neu bestimmen bei jeder neuen Map da sonst negative
% Werte in der Matrix möglich sind.

for x = 1:3
figure(1)
[map,zeroPoint] = localMap(lStart1,lEnd1,robotCoordinate(x,3));
imshow(map)

mapSize=size(map);
globalMapSize = size(globalMap1);

if(firstFlag == 0)
  globalMapZeroPoint = zeroPoint;
  firstFlag = 1;
  globalMapSize = size(map);
end




if(robotCoordinate(x,1)>=0)   
    newSize(2) = robotCoordinate(x,1)+mapSize(2)-zeroPoint(2)+globalMapZeroPoint(2);
        
    startPoint(2)= globalMapZeroPoint(2)+robotCoordinate(x,1)-zeroPoint(2)
    endPoint(2) = globalMapZeroPoint(2)+robotCoordinate(x,1)-zeroPoint(2)+mapSize(2);
end  

if(robotCoordinate(x,2)>=0)   
    newSize(1) = robotCoordinate(x,2)+mapSize(1)-zeroPoint(1)+globalMapZeroPoint(1);
    
    startPoint(1)= globalMapZeroPoint(1)+robotCoordinate(x,2)-zeroPoint(1);
    endPoint(1) = globalMapZeroPoint(1)+robotCoordinate(x,2)-zeroPoint(1)+mapSize(1);   
end 

if(robotCoordinate(x,1)<0)   
    newSize(2) = abs(robotCoordinate(x,1))+zeroPoint(2)+globalMapSize(2)-globalMapZeroPoint(2);  
      
%     if(newZeroPoint(2)>robotCoordinate(x,1))
%     globalMapZeroPoint(2) =  globalMapZeroPoint(2)+abs(robotCoordinate(x,1))+newZeroPoint(2)
%     newZeroPoint(2) = robotCoordinate(x,1) 
%     end
    
    if(globalMapZeroPoint(2)<abs(robotCoordinate(x,1))+zeroPoint(2))
        globalMapZeroPoint(2)=abs(robotCoordinate(x,1))+zeroPoint(2)
        newZeroPoint(2) = robotCoordinate(x,1)
    end
    
     
    startPoint(2)= globalMapZeroPoint(2)+robotCoordinate(x,1)-zeroPoint(2)
    endPoint(2)= globalMapZeroPoint(2)+robotCoordinate(x,1)-zeroPoint(2)+mapSize(2); 
end  

if(robotCoordinate(x,2)<0)   
    newSize(1) = abs(robotCoordinate(x,2))+zeroPoint(1)+globalMapSize(1)-globalMapZeroPoint(2);
    
%     if(newZeroPoint(1)>robotCoordinate(x,2))
%     globalMapZeroPoint(1) =  globalMapZeroPoint(1)+abs(robotCoordinate(x,2))+newZeroPoint(1);
%     newZeroPoint(1) = robotCoordinate(x,2);
%     end
    
     if(globalMapZeroPoint(1)<abs(robotCoordinate(x,2))+zeroPoint(1))
        globalMapZeroPoint(1)=abs(robotCoordinate(x,2))+zeroPoint(1)
        newZeroPoint(1) = robotCoordinate(x,2);
    end
    
    startPoint(1)= globalMapZeroPoint(1)+robotCoordinate(x,2)-zeroPoint(1)
    endPoint(1)= globalMapZeroPoint(1)+robotCoordinate(x,2)-zeroPoint(1)+mapSize(1);
    
end 


if(newSize(1)<globalMapSize(1))
     newSize(1) = globalMapSize(1);        
end     
if(newSize(2)<globalMapSize(2))
     newSize(2) = globalMapSize(2);        
end    

mapBuffer = uint8(zeros(newSize(1),newSize(2))+200);
bufferSize = size(mapBuffer);   
    
if(robotCoordinate(x,2)>0)
    gMapStart(1)= globalMapZeroPoint(1)-oldZeroPoint(1)
else
    gMapStart(1)= bufferSize(1)-globalMapSize(1);
end

if(robotCoordinate(x,1)>0)
    gMapStart(2)= globalMapZeroPoint(2)-oldZeroPoint(2)
else
    gMapStart(2)= bufferSize(2)-globalMapSize(2);
end  
   
    mapBuffer(gMapStart(1)+1:gMapStart(1)+globalMapSize(1),gMapStart(2)+1:gMapStart(2)+globalMapSize(2)) = globalMap1; 
    oldZeroPoint = zeroPoint;    
    rcount = 1;
    ccount = 1;
    
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

mapBuffer(globalMapZeroPoint(1),globalMapZeroPoint(2))= 100;
globalMap1 = mapBuffer;
figure(4)
imshow(globalMap1)


end