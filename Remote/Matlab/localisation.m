
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
orientation = 0;
globalIm = mat2gray(globalMap);
c = 0;
for angle = 0:5:359
clear 'localMap'
[map,localZeroPoint] = localMap(lStart,lEnd,double((pi()/180)*angle));
localIm= mat2gray(map);
% size(localIm)
% size(globalIm)

cnew = normxcorr2(localIm,globalIm);
    if(max(cnew(:))>max(c(:)))
        c = cnew;
        zeroPoint = localZeroPoint;
        orientation = angle;
    end
end
% figure(8), surf(c), shading flat
[ypeak, xpeak] = find(c==max(c(:)));

yoffSet = ypeak-size(localIm,1);
xoffSet = xpeak-size(localIm,2);


coordinate = [0,0];
zeroPoint;
coordinate(2) = yoffSet+zeroPoint(1);
coordinate(1) = xoffSet+zeroPoint(2);



end

