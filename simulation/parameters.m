function params = parameters()
    %% This file contails all the parameters for a 1D balancer  %%
    
    %% Model Parameters
    
    % Environmental parameters
    g = 10;             % units: m/s^2  % Acceleration due to gravity
    
    % Balancer parameters
    l = 0.348;          % units: m      % Distance between propellors
    h = 0.09;           % units: m      % Height of COM above ground
    H = 0.124;          % units: m      % Height of lowest point of propellor mount above ground
    I = 0.005;          % units: kg/m^2 % Moment of inertia about axis passing though COM and parallel to line of contact
    M = 1;              % units: Kg     % Mass of balancer
    
    % Propellor parameters
    Kf = 1;             % units: Ns^2   % F = kf*w^2 force constant of propellor
    Kt = 1;             % units: Nms^2  % T = kf*w^2 torque constant of propellor
    w_max = 1;          % units: RPM    % Max speed of propellor
    
    %% Controller Parameters
    
    % Explicit parameters
    max_KE = 2;         % units: J      % Max Kinetic energy possesed by balancer at any instant.
                                        % This is approximately equal to dropping 1Kg mass from a height of 20cm. This ensures safety.

    max_thrust_to_weight_ratio  =  0.7; % max ratio of weight that the propellors are allowed to put   
    bottom_sat_ratio = 0.7;             % what ratio of max permissible torque above which leads to saturation of control when control is -ve
    top_sat_ratio = 0.7;                % what ratio of max permissible torque above which leads to saturation of control when control is +ve
    epsilon_power = 0.05;               % minimum ratio of max power that motors should run at
    avail_power_ratio = 0.25;           % ratio of max power that is available on either side of control point
    
    %% Simulation Parameters
    
    RT_plot = 0;                        % To enable or disable plotting in real time
    controller_on = 1;                  % To enable or disable controller
    trajectory_on = 1;                  % To enable or disable trajectory tracking
 
    %% Loading parameteres
    
    % Model
    
    balancer.L = l/2;                       % units: m      % Half distance between propellors
    balancer.h = h;                         % units: m      % Height of COM above ground
    balancer.H = H;                         % units: m      % Height of lowest point of propellor mount above ground
    balancer.Ic = I;                        % units: kg/m^2 % Moment of inertia about axis passing though COM and parallel to line of contact
    balancer.M = M;                         % units: Kg     % Mass of balancer
    balancer.I0 = I+M*h^2;                  % units: kg/m^2 % Moment of inertia about axis passing though COM and parallel to line of contact
    
    propellor.Kf = Kf;                      % units: Ns^2   % F = kf*w^2 force constant of propellor
    propellor.Kt = Kt;                      % units: Nms^2  % T = kf*w^2 torque constant of propellor
    propellor.w_max = w_max*2*pi/60;        % units: rad/s  % Max speed of propellor
    propellor.F_max = Kf*propellor.w_max^2; % units: N      % Max force by propellor
    propellor.T_max = Kt*propellor.w_max^2; % units: Nm     % Max torque by propellor
    
    model.balancer = balancer;              % balancer
    model.propellor = propellor;            % propellor
    model.g = g;                            % units: m/s^2  % Acceleration due to gravity
    
    % Controller
    
    controller.theta_max = pi/2 - atan2(balancer.L,balancer.H);   % units: rad    % Max angle deviation from vertical
    controller.thetaDot_max = sqrt(2*max_KE/balancer.I0);         % units: rad/s  % Max angular velocity of balancer by limiting KE of system
    controller.mTWr = max_thrust_to_weight_ratio;                 % max ratio of weight that the propellors are allowed to put   
    controller.bottom_sat_ratio = bottom_sat_ratio;               % what ratio of max permissible torque above which leads to saturation of control when control is -ve
    controller.top_sat_ratio = top_sat_ratio;                     % what ratio of max permissible torque above which leads to saturation of control when control is +ve
    controller.epsilon_power = epsilon_power;                     % minimum ratio of max power that motors should run at
    controller.avail_power_ratio = avail_power_ratio;             % ratio of max power that is available on either side of control point

    % Simulation

    simulator.RT_plot = RT_plot;            % To enable or disable plotting in real time
    simulator.controller_on = controller_on;% To enable or disable controller
    simulator.trajectory_on = trajectory_on;% To enable or disable trajectory tracking

    % Combining
    
    params.model = model;                   % model
    params.controller = controller;         % controller
    params.simulator = simulator;           % simulator
    
end