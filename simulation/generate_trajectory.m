function traj = generate_trajectory()
    syms t;
    theta = -(pi/6)*sin(2*pi*t/2);
    T = [theta diff(theta) diff(diff(theta))];
    
    traj = matlabFunction(T,'vars',{'t'});
end