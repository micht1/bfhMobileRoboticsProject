


point1 = bestSpot1(gMap);

function point = bestSpot1(globalMap)
t = cputime;
sizeMap = size(globalMap);
percent = 20;
imshow(globalMap)
whitePoint = [0,0];
cnt = 1;
for c = 1:sizeMap(1)
    for r = 1:sizeMap(2)
        if(globalMap(c,r) == 255)
        whitePoint(cnt,1)= c;
        whitePoint(cnt,2)= r;
        cnt = cnt+1;
        end
    end
end

%Choose points to check grey spots
sizeWP=size(whitePoint);
numberOfPoints = (round((sizeWP(1)/100)*percent));
random = randi([1 sizeWP(1)],numberOfPoints,1);
sizeR = size(random);

%360° directions
directions = [0,0];%zeros(360,2);
for x = 1:1:360
directions(x,2)=cosd(x); %x
directions(x,1)=sind(x); %y  
end
directions = directions/1;
sizeDirections=size(directions);
greyPoints = zeros(numberOfPoints,1);

for x = 1:sizeR(1)
    countGrey = 0;
    startPoint = whitePoint(random(x),:);
    for k = 1:sizeDirections(1)
    newPoint = startPoint;   
    new = newPoint;
    old = new;
        while (1) 
        new=directions(k,:)+new;    
        newPoint = round(new);      
        if(newPoint(1)<= sizeMap(1) & newPoint(2)<= sizeMap(2) & newPoint(1)>0 & newPoint(2)>0 )
            if(globalMap(newPoint(1),newPoint(2))==0)
               break;          
            elseif(globalMap(newPoint(1),newPoint(2))==200 & newPoint~=old)
                old = newPoint;
                countGrey=countGrey+1;
            end
        else
            break;
        end    
        end
    end
    greyPoints(x) = countGrey;
end

%searchMax
biggestCnt = 1;
biggest = 0;
for x = 1:sizeR(1)
if(greyPoints(x)>biggest)
    biggestCnt = x;
    biggest = greyPoints(x);
end
end

point = whitePoint(random(biggestCnt,:),:);
time = cputime-t
globalMap(point(1),point(2))=150;
figure(2)
imshow(globalMap)

end