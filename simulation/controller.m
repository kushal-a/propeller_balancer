function u = controller(obj,t,y,yd)
    
    M = obj.params.model.balancer.M;
    h = obj.params.model.balancer.h;
    L = obj.params.model.balancer.L;
    I = obj.params.model.balancer.I0;
    g = obj.params.model.g;

%     thetaMax = obj.params.controller.theta_max;
%     thetaDotMax = obj.params.controller.thetaDot_max;
    mTWr = obj.params.controller.mTWr;
    bottom_sat_ratio = obj.params.controller.bottom_sat_ratio;
    top_sat_ratio = obj.params.controller.top_sat_ratio;
    epsilon_power = obj.params.controller.epsilon_power;
    avail_power_ratio = obj.params.controller.avail_power_ratio;

    Kp = 20;
    Kd = 4.8;

    theta = y(1);
    thetaDot = y(2);

    desTheta = yd(1);
    desThetaDot = yd(2);
    desThetaDDot = yd(3);

    theta_e = theta - desTheta;
    thetaDot_e = thetaDot - desThetaDot;

    u0 = (I/L)*(desThetaDDot - (Kp*theta_e + Kd*thetaDot_e + (M*g*h*sin(theta))/I));
    um = mTWr*M*g;

    function r = saturate(r,alpha)

        % Let r be any number. When r>alpha (some ratio), we want r to
        % saturate to 1 exponentially

        % Let r' be corrected r. For r>alpha let r' = a - b*exp(-c*r)
        % Using continuity and differentiability we calculate a,b,c

        if (r>alpha)
            a = 1;
            c = 1/(1-alpha);
            b = exp(c*alpha)/c;

            r = a-b*exp(-c*r);

        end
    end


    if (u0>0)
        u0 = um*saturate(u0/um,top_sat_ratio);
    else
        u0 = -um*saturate(-u0/um,bottom_sat_ratio);
    end
    
    % Let us solve for power limits
    % P = (Kt/Kf^1.5)*(uL*1.5+uR^1.5)
    % To simplify our expressions we will assume x^1.5 ~ x
    % Pmin occurs when uR = max(ud,0), uL = -min(ud,0)
    % Pmax occurs when uR = (um+ud)/2, uL = (um-ud)/2
    % We will optmize the choice of u1 and u2 such that there is enough
    % power available on either side

    % First we always want power of a motor to be greater than a min
    % percent epsilon
    % Second we want atleast certain amount of power available on either
    % side. Let this be x% given by ratio avail_power_ratio
    % We want to operate at epsilon+avail_power_ratio

    function r = interpolate(r1,r2,alpha)

        % r1 = [x1,y1]
        % r2 = [x2,y2]
        % alpha = interpolation ratio

        r = r1 + alpha*(r2 - r1);
    end

    if (u0>0)

        % Pmin occurs when uR = ud, uL = 0;
        % Pmax occurs when uR = (um+ud)/2, uL = (um-ud)/2    uR>uL

        uR_min = u0;
        uL_min = 0;

    else

        % Pmin occurs when uR = 0, uL = -ud;
        % Pmax occurs when uR = (um+ud)/2, uL = (um-ud)/2    uL>uR

        uR_min = 0;
        uL_min = -u0;

    end

    uR_max = (um+u0)/2;
    uL_max = (um-u0)/2;

    u_min = [uL_min;uR_min];
    u_max = [uL_max;uR_max];

    u = interpolate(u_min,u_max,epsilon_power+avail_power_ratio);

end