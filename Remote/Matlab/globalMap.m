%clearvars; clear all; close all; clc
lStart = round(lStart/100);
lEnd = round(lEnd/100);
%lStart = round([-1000 ,-2000;2000,-2000;2000,2000;  100,3000;-600 ,1000;-1000, 1000]/100);
%lEnd =   round([2000  ,-2000;2000, 2000;1500,2000;  500,3000;-1000,1000;-1000,-2000]/100);

orientation = 0;

map = localMap(lStart,lEnd,orientation);


imshow(map)


