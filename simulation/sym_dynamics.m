M = params.model.balancer.M;
h = params.model.balancer.h;
L = params.model.balancer.L;
I = params.model.balancer.I0;
g = params.model.g;

syms theta(t);
thetaDot = diff(theta,t);

ke = 0.5*(I*thetaDot^2);
pe = M*g*h*cos(theta);

inerta_vec = simplify(diff(diff(ke,thetaDot),t));
corriolis_vec = simplify(-diff(ke,theta));
gravity_vec = simplify(-diff(pe,theta));

x = sym('x',[3,1]);
inerta_vec = substitute(inerta_vec,x,theta,t);
corriolis_vec = substitute(corriolis_vec,x,theta,t);
gravity_vec = substitute(gravity_vec,x,theta,t);

mass_mat = coeffs(inerta_vec,x(3));
corriolis_mat = coeffs(corriolis_vec,x(2));

syms uL uR;
tau = (uR-uL)*L;

thetaDDot = inv(mass_mat)*(tau-corriolis_vec-gravity_vec);


matlabFunction(thetaDDot,'File','dynamics', ...
    'Vars',[t x(1) x(2) uL uR],'Outputs',{'thetaDDot'});

function ex = substitute(ex,x,theta,t)
    ex = subs(ex,diff(theta(t),t,t),x(3));
    ex = subs(ex,diff(theta(t),t),x(2));
    ex = simplify(subs(ex,theta(t),x(1)));
end
