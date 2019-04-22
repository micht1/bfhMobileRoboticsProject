
% clear all
% 
% %   lStart1 = round([-700 ,700; 1400, 700; 2500,-1500; 2500,-2600; -500,-2600; -700,-2600; -200,-1000]/100);
% %   lEnd1 =   round([1400 ,700; 1400,-900; 2500,-2600; 2300,-2600; -700,-2600; -700,  700;  900,-1000]/100);
% 
% 
% lStart1 = round([  100,1500;-600 ,1000;-1000,1000]/100);
% lEnd1 =   round([  500,1500;-1000,1000;-1000,100]/100);
% load('workspaceVariables.mat')
% R = Rz(double(pi()/180*0));
% L = [0,0,0]';
% Tmat=TraMat3D(R,L);
% 
% lStart2 = [0,0];
% lEnd2=[0,0];
%   for x = 1:size(lStart1)     
%     rStart = [lStart1(x,1),lStart1(x,2),0,1]*Tmat;
%     lStart2(x,1) = round(rStart(1)); 
%     lStart2(x,2) = round(rStart(2)); 
%     
%     rEnd = [lEnd1(x,1),lEnd1(x,2),0,1]*Tmat;
%     lEnd2(x,:) = round(rEnd(1)); 
%     lEnd2(x,2) = round(rEnd(2));      
%   end  
% 
%   
% [map,zeroPoint] = localMap(lStart1,lEnd1,0);
% figure(2)
% imshow(map)
% size(map);
% pic1 = mat2gray(map);
% 
% lStart1 = round([-1000 ,-2000;2000,-2000;2000,2000; 1500,1500;-600 ,1000;-1000, 1000;-600,1000;1500,1500 ]/100);
% lEnd1 =   round([2000  ,-2000;2000, 2000;1500,2000; -600,1500;-1000,1000;-1000,-2000;-600,1500;1500,2000]/100);
% 
% 
% map = localMap(lStart1,lEnd1,0);
% figure(3)
% imshow(map)
% size(map);
% globalMap= mat2gray(map);
% 
% t = cputime;
% 
% lStart = round([  100,1500;-600 ,1000;-1000,1000]/100);
% lEnd =   round([  500,1500;-1000,1000;-1000,100]/100);
% 
% [coordinate,alpha] = localisation1(lStart2,lEnd2,globalMap);
% alpha 
% coordinate
% time = cputime-t;
% 
% map(coordinate(2),coordinate(1)) = 100;
% 
% figure(6)
% imshow(map)



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

for cnt = 1:matchSize(1)
    possibilityMap(match(cnt,1),match(cnt,2)) = possibilityMap(match(cnt,1),match(cnt,2))+match(cnt,3)*possibilityMap(match(cnt,1),match(cnt,2)); 
end

maxP = max(possibilityMap);
possibilityMap = possibilityMap./maxP;

% figure(3)
% imshow(possibilityMap)

[column,row] = find(match==max(match(:,3)));

% figure(8), surf(c), shading flat
% [ypeak, xpeak] = find(c==max(c(:)));

% ypeak = match(column,1);
% xpeak = match(column,2);
% 
% yoffSet = ypeak-size(localIm,1);
% xoffSet = xpeak-size(localIm,2);

coordinate = [0,0];
coordinate(2) = match(column,1);
coordinate(1) = match(column,2);
orientation = match(column,4);

end

