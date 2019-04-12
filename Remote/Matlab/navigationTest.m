testmap = imread('occupancyGrid_1.bmp');
%testmap =~testmap;
imshow(testmap);
%testmap =[zeros(1,9);testmap;zeros(1,9)];
%testmap =[zeros(11,1) testmap zeros(11,1)];

[viaPoints] = navToPoint(testmap,[-0.1,-0.1],0.01,[0.2,0.2],[0.45-0.2,-0.05]);

