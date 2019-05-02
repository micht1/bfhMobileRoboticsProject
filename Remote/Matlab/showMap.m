
%function to cut gray field outside the map
function [smallMap,frontX,frontY]= showMap(gMap)

sizeMap = size(gMap)
frontY = sizeMap(2);
backY = 0;
frontX = sizeMap(1);
backX = 0;

for y = 1: sizeMap(1)
    for x = 1:sizeMap(2)
        if(gMap(y,x) == 0)
            if(frontY>x)
            frontY = x;
            break;
            end
        end  
    end
    
    for x = sizeMap(2):-1:1
        if(gMap(y,x) == 0)
            if(backY<x)
            backY = x;
            break;
            end
        end  
    end
end

for x = 1: sizeMap(2)
    for y = 1:sizeMap(1)
        if(gMap(y,x) == 0)
            if(frontX>y)
            frontX = y;
            break;
            end
        end  
    end
    
    for y = sizeMap(1):-1:1
        if(gMap(y,x) == 0)
            if(backX<y)
            backX = y;
            break;
            end
        end  
    end
end
smallMap = gMap(1:backX+5,1:backY+5);

end


