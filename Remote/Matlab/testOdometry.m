
yellow.set('state{stateName: MANUAL}, velocities{linearSpeed:-0.5, angularSpeed:0}')

for k=1:10
    yellow.receive
    pause (1)
end

yellow.set('state{stateName: OFF}')
yellow.receive
