clearvars; close all; clear all; clc 
t = cputime;
world = imread('occupancyGrid_1.bmp'); % Wall = 0, Room = 255
world = imcomplement(world);
imshow(world)
size(world);

sizeKernel = 3;
startPoint = [25,4];
endPoint = [9,37];
world(startPoint(1),startPoint(2)) = 60;
world(endPoint(1),endPoint(2)) = 60;
%direction = [1 0 0 0];%N,E,S,W
direction = startDirection(startPoint,endPoint);

currentPosition = startPoint;
oldPosition = startPoint;
endFlag = 0;
startFlag = 1;
oldDirection = direction;
endDirection = [0 0 0 0];
directionSwitched = 0;

for x = 1:200

oldDirection = direction;
deltaEndPoint = currentPosition-endPoint;
   
if((deltaEndPoint(1)== 0 | deltaEndPoint(2)== 0) & endFlag == 0)   
    endDirection = searchEndPoint(deltaEndPoint,direction);
    endFlag = 1;
    %startFlag = 0;
    direction = endDirection;
end 

[newPosition,endFlag,startFlag] = getNewPosition(currentPosition,sizeKernel,world,direction,endFlag,startFlag,endPoint);


direction = getDirection(newPosition, currentPosition);

oldPosition = currentPosition;
currentPosition = newPosition;
world(currentPosition(1),currentPosition(2)) = world(currentPosition(1),currentPosition(2))-50;
if(world(currentPosition(1),currentPosition(2))<80)
   world(currentPosition(1),currentPosition(2)) = 80;
end

if(currentPosition == endPoint)
    endCounter = x;
 break
end
%imshow(world)
end
time = cputime-t
imshow(world)


wayPoints = zeros(x+2,2);
sizeWorld=size(world);
wayPointCount = 1;
for y = 1:sizeWorld(1)
    for x = 1:sizeWorld(2)
    
     if(world(y,x)==255-50)  
        wayPoints(wayPointCount,1)= y;
         wayPoints(wayPointCount,2)= x;
         wayPointCount = wayPointCount+1;
     end
    end
end
wayPoints
map1= imread('occupancyGrid_1.bmp'); % Wall = 0, Room = 255
map1 = imcomplement(map1);

for y =  1:wayPointCount
    
    if(wayPoints(y,1)>0 && wayPoints(y,2)>0)
    map1(wayPoints(y,1),wayPoints(y,2))=100;
    end
end

figure(2)
imshow(map1)












function [newPosition,endFlag,startFlag] = getNewPosition(currentPosition,sizeKernel,world,direction,endFlag,startFlag,endPoint)

persistent turns directionSwitched throughDoor specialFlag
if(isempty(turns) | isempty(directionSwitched))
    turns = 0; 
    throughDoor = 0;
    directionSwitched=0;
    specialFlag = 0;
end

surroundings = getSurroundings(sizeKernel,currentPosition,world);
  if( surroundings >0)
       newDirection = direction;     
  else
     if(direction(1)==1)
       if(surroundings(1,2)>0)
          [newDirection,throughDoor]= doorCheck(sizeKernel,direction,surroundings,endFlag,turns,throughDoor);        
       else
          %% First if is new
          if(surroundings(1,1)>0&&surroundings(1,3)>0)
           newDirection = bestDirection(currentPosition,endPoint,direction);
           
          elseif(surroundings(2,1)==0 && surroundings(2,3)==0)
          newDirection = [0 0 1 0];
          elseif(surroundings(2,1)==0 || surroundings(2,3)>0)
          newDirection = [0 1 0 0];
          else
          newDirection = [0 0 0 1];   
          end      
       end 
     end
        
     if(direction(2)==1)  
       if(surroundings(2,3)>0)
          [newDirection,throughDoor]= doorCheck(sizeKernel,direction,surroundings,endFlag,turns,throughDoor); 
       else   
          %% First if is new
          if(surroundings(1,3)>0&&surroundings(3,3)>0)
           newDirection = bestDirection(currentPosition,endPoint,direction);
           
          elseif(surroundings(1,2)==0 && surroundings(3,2)==0)
          newDirection = [0 0 0 1];
          elseif(surroundings(1,2)==0 || surroundings(3,2)>0)
          newDirection = [0 0 1 0];
          else
          newDirection = [1 0 0 0];   
          end      
       end   
     end
      
     if(direction(3)==1)

       if(surroundings(3,2)>0)           
          [newDirection,throughDoor] = doorCheck(sizeKernel,direction,surroundings,endFlag,turns,throughDoor);  
       else
          %% First if is new
          if(surroundings(3,1)>0&&surroundings(3,3)>0)
           newDirection = bestDirection(currentPosition,endPoint,direction);
           
          elseif(surroundings(2,1)==0 && surroundings(2,3)==0)
          newDirection = [1 0 0 0];
          elseif(surroundings(2,3)==0 || surroundings(2,1)>0)
          newDirection = [0 0 0 1];
          else
          newDirection = [0 1 0 0];   
          end      
       end 
     end
              
              
     if(direction(4)==1)
       if(surroundings(2,1)>0)
          [newDirection,throughDoor] = doorCheck(sizeKernel,direction,surroundings,endFlag,turns,throughDoor); 
       else
          %% First if is new
          if(surroundings(1,1)>0&&surroundings(3,1)>0)
           newDirection = bestDirection(currentPosition,endPoint,direction);
           
          elseif(surroundings(1,2)==0 && surroundings(3,2)==0)
          newDirection = [0 1 0 0];
          elseif(surroundings(3,2)==0 || surroundings(1,2)>0)
          newDirection = [1 0 0 0];
          else
          newDirection = [0 0 1 0];   
          end      
       end           
     end
  end
  if(endFlag ==1 & startFlag ==1)
      turns = 0;
      directionSwitched = 0;
      specialFlag = 1;
      startFlag = 0;
  end
  
  % End Point on same Axis in X or Y
  if(endFlag == 1 || startFlag == 1)
      if(direction == newDirection)
      % ~= doesn't work
      else
      turns = turns+1;   
      end
      if((turns ==2 && directionSwitched == 0 && throughDoor == 0))
         if(direction(1) == 1)
            newDirection = [0 0 1 0];
          elseif(direction(2) == 1)
             newDirection = [0 0 0 1];
          elseif(direction(3) == 1)
             newDirection = [1 0 0 0];
          elseif(direction(4) == 1)
             newDirection = [0 1 0 0];
         end
       
       directionSwitched = 1;      
       elseif(throughDoor == 1)
           directionSwitched = 0;
           specialFlag = 0;
           turns = 0;
           endFlag = 0;
     end  
  end 
  
  if(specialFlag == 1)
      %Have to be tested an optimised
     if(direction(1) == 1 && surroundings(1,2) == 0)
         newDirection = [0 1 0 0];    
     
     elseif(direction(2) == 1 && surroundings(2,3) == 0)
         newDirection = [1 0 0 0];    
     
     elseif(direction(3) == 1 && surroundings(3,2) == 0)
         newDirection = [0 0 0 1];    
    
     elseif(direction(4) == 1 && surroundings(2,1) == 0)
         newDirection = [0 0 1 0];    
     end
     specialFlag = 0; 
  end
  
  if(newDirection(1) == 1)
  newPosition = currentPosition+[-1  0];
  elseif(newDirection(2) == 1)
  newPosition = currentPosition+[ 0  1];
  elseif(newDirection(3) == 1)
  newPosition = currentPosition+[ 1  0];
  elseif(newDirection(4) == 1)
  newPosition = currentPosition+[ 0 -1];
  end  
end

function [direction,throughDoor] = doorCheck(sizeKernel,direction,surroundings,endFlag,turns,throughDoor)
persistent cnt
if(isempty(cnt))
    cnt = 0;
end
middle = (sizeKernel+1)/2;
newDirection = direction;

if(direction(1) == 1)
    if(surroundings(middle,1) > 0 && surroundings(3,1)==0 && (turns ~= 0 || endFlag == 0)&& throughDoor == 0)
        newDirection = [0 0 0 1];
        throughDoor = 1;
    elseif(surroundings(middle,3) > 0 && surroundings(3,3)==0 && (turns ~= 0 || endFlag == 0)&& throughDoor == 0)
        newDirection = [0 1 0 0];
        throughDoor = 1;
    end   
end
if(direction(2) == 1)
    if(surroundings(1,middle) > 0 && surroundings(1,1)==0 && (turns ~= 0 || endFlag == 0)&& throughDoor == 0)
        newDirection = [1 0 0 0];
        throughDoor = 1;
    elseif(surroundings(3,middle) > 0 && surroundings(3,1)==0 && (turns ~= 0 || endFlag == 0)&& throughDoor == 0)
        newDirection = [0 0 1 0];
        throughDoor = 1;
    end   
end
if(direction(3) == 1)
    if(surroundings(middle,1) > 0 && surroundings(1,1)==0 && (turns ~= 0 || endFlag == 0) && throughDoor == 0)
        newDirection = [0 0 0 1]; 
        throughDoor = 1;
    elseif(surroundings(middle,3) > 0 && surroundings(1,3)==0 && (turns ~= 0 || endFlag == 0) && throughDoor == 0)
        newDirection = [0 1 0 0];
        throughDoor = 1;
    end   
end
if(direction(4) == 1)
    if(surroundings(1,middle) > 0 && surroundings(1,3)==0 && (turns ~= 0 || endFlag == 0)&& throughDoor == 0)
        newDirection = [1 0 0 0];
        throughDoor = 1;
    elseif(surroundings(3,middle) > 0 && surroundings(3,3)==0 && (turns ~= 0 || endFlag == 0)&& throughDoor == 0)
        newDirection = [0 0 1 0]; 
        throughDoor = 1;
    end    
end

if(throughDoor == 1 && cnt >=2 && endFlag == 0)
throughDoor = 0;
cnt = 0;
elseif(throughDoor == 1 && cnt >2)
throughDoor = 0;
cnt = 0;
elseif(throughDoor == 1)
cnt = cnt+1;
end
direction = newDirection;
end

function kernel = getSurroundings(sizeKernel,currentPosition,world)
kernel= zeros(sizeKernel,sizeKernel);
for n = 1:sizeKernel
    for i = 1:sizeKernel    
         kernel(n,i) = world(currentPosition(1)-(sizeKernel-1-n),currentPosition(2)-(sizeKernel-1-i));
    end  
end
end

function direction = getDirection(currentPosition, oldPosition)

deltaPos = currentPosition-oldPosition;
if(deltaPos(1)>0)
    newDirection = [0 0 1 0];
elseif(deltaPos(1)<0)
    newDirection = [1 0 0 0];
elseif(deltaPos(2)>0)
    newDirection = [0 1 0 0];
elseif(deltaPos(2)<0)
    newDirection = [0 0 0 1];
else
    newDirection = [1 0 0 0];
end
direction = newDirection;
end

function direction = searchEndPoint(deltaEndPoint,direction)
    %endDirection = direction;  
    %if(deltaEndPoint(1) == 0 && (direction(1) == 1 || direction(3) == 1) && deltaEndPoint(2)<0)
    if(deltaEndPoint(1) == 0  && deltaEndPoint(2)<0)
        endDirection = [0 1 0 0];
    %elseif(deltaEndPoint(1) == 0 && (direction(1) == 1 || direction(3) == 1) && deltaEndPoint(2)>0)
    elseif(deltaEndPoint(1) == 0  && deltaEndPoint(2)>0)
        endDirection = [0 0 0 1];          
    %elseif(deltaEndPoint(2) == 0 && (direction(2) == 1 || direction(4) == 1) && deltaEndPoint(1)<0)   
    elseif(deltaEndPoint(2) == 0 && deltaEndPoint(1)<0) 
        endDirection = [0 0 1 0];
    else
        endDirection = [1 0 0 0];
    end
    direction = endDirection;
end

function direction = startDirection(startPoint, endPoint)
delta = startPoint-endPoint;
%NewDirection = [0 0 0 0];
if(abs(delta(1))<abs(delta(2)))
    if(delta(2)<0)
        newDirection = [0 1 0 0];
    else
        newDirection = [0 0 0 1];
    end    
else
    if(delta(1)<0)
        newDirection = [0 0 1 0];
    else
        newDirection = [1 0 0 0];
    end   
end
direction = newDirection;
end

function direction = bestDirection(currentPosition,EndPoint,currentDirection)
    if(currentDirection(1)==1 || currentDirection(3)==1)
        if(currentPosition(2)-EndPoint(2)>0)
          newDirection = [0,0,0,1];
        else 
          newDirection = [0,1,0,0];
        end
    else
        if(currentPosition(1)-EndPoint(1)>=0)
          newDirection = [0,0,1,0];
        else 
          newDirection = [1,0,0,0];
        end      
    end
  
direction = newDirection;
end
