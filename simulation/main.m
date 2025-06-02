%% Generating function handles & Initialization

% Loading parameters
params = parameters();

% Provides function handles for dynamics, KE, PE, TE
handles.system = generate_dynamics(params);

% % Generates function to extract trajectory
handles.trajectory = generate_trajectory();
% handles.trajectory = @(t) [pi/6;0;0];

% Retrives controller to be used for simulation
handles.controller = @controller;

% Inititalizing 
mybalancer = oneD_balancer(handles,params);

x0 =  [0.1;0];

%% Integrate

opts = odeset('RelTol',1e-6,'AbsTol',1e-6);

[t,y] = ode45(@(t,y) mybalancer.sdot(t,y), [0 10],x0,opts);

%% Animate

if ~mybalancer.RT_plot
    mybalancer.animate(t,y);
end