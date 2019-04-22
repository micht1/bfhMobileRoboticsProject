function followPath(pathVector,yellow)
viaCnt=1;
    matSize=size(pathVector)
    while(viaCnt<=matSize(1))
        driveToPosition(pathVector(viaCnt,2),pathVector(viaCnt,1),pathVector(viaCnt,3),yellow);
        pause(10)
        viaCnt=viaCnt+1;
    end
end