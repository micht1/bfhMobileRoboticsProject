function followPath(pathVector,yellow)
viaCnt=1;
    matSize=size(pathVector)
    while(viaCnt<=matSize(1))
        driveToPosition(pathVector(viaCnt,2),pathVector(viaCnt,1),pathVector(viaCnt,3),yellow);
        while(isAtPosition(pathVector(viaCnt,2),pathVector(viaCnt,1),pathVector(viaCnt,3),0.1,yellow)==true)
            
        end
        viaCnt=viaCnt+1;
    end
end