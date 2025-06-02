function out = generate_dynamics(parameters)
    %% State Space Parameter

    % Let x = [theta, thetaDot]^T
    % Let xDot = [thetaDot, thetaDDot]^T
    % Let u = [uL, uR]^T
    % Let y = [theta, thetaDot]^T

    %% Unloading parameters

    M = parameters.model.balancer.M;
    h = parameters.model.balancer.h;
    L = parameters.model.balancer.L;
    I = parameters.model.balancer.I0;
    g = parameters.model.g;

    %% Symbolic Caluclation of Lagrange

    syms theta(t);
    thetaDot = diff(theta,t);
    
    ke = 0.5*(I*thetaDot^2);
    pe = M*g*h*cos(theta);
    
    Lagrange = ke - pe;

    %% Symbolic calulation of torque and using lagrange equation
    
    syms uL uR;
    tau = (uR-uL)*L;
    eq = tau == simplify(diff(diff(Lagrange,thetaDot),t) - diff(Lagrange,theta));
    
    %% Conversion to State Space
    [V,S] = odeToVectorField(eq);

    % S gives:
    % S1 = theta  S2 = Dtheta   S -> state often referred as x
    
    % S_dot = V(S)  in V, terms of S are written as Y

    ke = subs(ke,diff(theta(t),t),S(2));
    k = subs(ke,theta(t),S(1));

    pe = subs(pe,diff(theta(t),t),S(2));
    p = subs(pe,theta(t),S(1));

    state = matlabFunction(S,'vars',{'theta','Dtheta'});

    dynamics_ = matlabFunction(V,'vars',{'t','Y','uL','uR'});

    out.dynamics = @(t,y,tau) dynamics_(t,y,tau(1),tau(2));

    get_ke_ = matlabFunction(k,'vars',{'t','theta','Dtheta'});

    out.get_ke = @(x) get_ke_(0,x(1),x(2));

    get_pe_ = matlabFunction(p,'vars',{'t','theta','Dtheta'});

    out.get_pe = @(x) get_pe_(0,x(1),x(2));
    
    out.get_te = @(x) get_ke(x)+get_pe(x);

end