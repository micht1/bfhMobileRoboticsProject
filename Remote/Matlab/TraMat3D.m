function  T = TraMat3D(R,L)  % R = Rotationsmatrix  L = Transformation => [x,y,z]'
T = [R,L;0 0 0 1];

end



