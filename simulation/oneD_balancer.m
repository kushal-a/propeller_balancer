classdef oneD_balancer
    properties
        
        % Params
        params


        % Model parameters for simulation
        L
        H

        % control input      
        u
        
        % Control Handles
        RT_plot
        controller_on
        trajectory_on
               
        % Graphs Handles
        graph_handles

        % Function Handlers
        controller
        dynamics
        get_pe
        get_ke
        get_te
        traj

    end

    methods
        function obj = oneD_balancer(handles,params)

            % Init Graphics

            obj.graph_handles           = obj.init_graphics();

            % Load parameters
            
            obj.params = params;

            obj.L      = params.model.balancer.L;
            obj.H      = params.model.balancer.H;
            
            obj.u          = [0;0];

            obj.RT_plot        = params.simulator.RT_plot;
            obj.controller_on  = params.simulator.controller_on;
            obj.trajectory_on  = params.simulator.trajectory_on;

            % Load Handles

            obj.controller  = handles.controller;
            obj.dynamics    = handles.system.dynamics;
            obj.get_ke      = handles.system.get_ke;
            obj.get_pe      = handles.system.get_pe;
            obj.get_te      = handles.system.get_te; 
            obj.traj        = handles.trajectory;

        end
        
        function s_dot = sdot(obj,t,s)
            
            % Extract states
            y = s;

            % Extract reference
            yd = obj.traj(t);

            % Run the controller to calculate required torques
            if(obj.controller_on)
                if(obj.trajectory_on)
                    obj.u = obj.controller(obj,t,y,yd);
                end
            end         
            
            % Run the torques and the current state to obtain the state change
            s_dot = obj.dynamics(t,y,obj.u);
                
        end

        function animate(obj,time,state)
            
            N = size(time(:,1));
            N = N(1);
            n = idivide(N,int16(100));
            if n==0
                n = 1;
            end

            h = obj.graph_handles;
            
            for i = 1:min(100,N)
                t = time(i*n);
                x = state(i*n,:)';
                ke = obj.get_ke(x);
                pe = obj.get_pe(x);
                te = ke+pe;

                clearpoints(h.h1)
                clearpoints(h.h2)
            
                theta = x(1);
                x1 = obj.H*[-sin(theta) cos(theta)];
                l = obj.L*[cos(theta) sin(theta)];
                x2 = x1-l;
                x3 = x1+l;
                addpoints(h.h1,[0 x1(1)],[0 x1(2)])
                addpoints(h.h2,[x2(1) x3(1)],...
                             [x2(2) x3(2)])
                drawnow;
                frame = getframe(2);
                  im = frame2im(frame);
                  [imind,cm] = rgb2ind(im,256);
                  if i == 1
                      imwrite(imind,cm,"move.gif",'gif','Loopcount',inf);
                  else
                      imwrite(imind,cm,"move.gif",'gif','WriteMode','append');
                  end

                addpoints(h.h3,t,ke)
                addpoints(h.h4,t,pe)
                addpoints(h.h5,t,te)
                addpoints(h.h6,t,theta*180/pi)
                yd = obj.traj(t);
                addpoints(h.h7,t,yd(1)*180/pi)
                input = obj.controller(obj,t,x,yd);
                addpoints(h.h8,t,input(1))
                addpoints(h.h9,t,input(2))
                addpoints(h.h10,t,obj.params.model.balancer.M*obj.params.model.g)
                addpoints(h.h11,t,(input(1)+input(2)*cos(theta)))

                drawnow;
                
            end

        end
    end
    methods (Static)
        function h = init_graphics()
        
            f1 = figure(1);
            
            subplot(2,2,1);
            title('Energy')
            h.h3 = animatedline('Color','r');
            h.h4 = animatedline('Color','g');
            h.h5 = animatedline('Color','b');
            ylabel("J")
            legend("KE","PE","TE")
            %ylim([-40 40])
            grid on
            
            subplot(2,2,2);
            title('angles')
            h.h6 = animatedline('Color','r');
            h.h7 = animatedline('Color','k','LineStyle','--');
            ylabel("degrees")
%             ylim([-3.14 3.14]*2)
            grid on
            
            subplot(2,2,3);
            title('forces')
            h.h8 = animatedline('Color','r');
            h.h9 = animatedline('Color','b');
            h.h11 = animatedline('Color','g');
            h.h10 = animatedline('Color','k','LineStyle','--');
            legend("uL","uR","thrust","weight")
            ylabel("N")
            grid on
            

            f2 = figure(2);
            
            title("Animation")
            h.h1 = animatedline('Color','r','LineWidth',3);
            h.h2 = animatedline('Color','c','LineWidth',3);
            axis([-0.3,0.3,-0.1,0.3])
            grid on
        
        end
    end
end