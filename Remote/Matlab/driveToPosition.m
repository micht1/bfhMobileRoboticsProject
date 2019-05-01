function driveToPosition(xPos,yPos,alpha, yellow)
clear constString s2
constString = 'state { stateName: AUTO_POSITION },desiredPose ';
s1 = sprintf('{ x: %f, y: %f, alpha: %f}',xPos,yPos,alpha)
s2 = strcat(constString,s1);
yellow.append(s2)

%yellow.set('state { stateName: AUTO_POSITION },desiredPose { x: %f, y: %f, alpha: %f} ')