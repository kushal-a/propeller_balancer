#include "propeller_balancer.h"

float kp = 1;
float ki = 0;
float kd = 0;

int timer;
float Theta;
int traj = 0;
int error;
float f_diff;
float u[2];

void setup(){
    init_devices();
    timer = 0;
}

void loop(){


    // SENSE
    gyro_signals();

    // COMPUTE
    error = Theta - traj;
    // f_diff = grav_force_diff();
    f_diff = pid_force_diff(timer, error);
    // f_diff = net_force_diff(timer, error);

    u[0] = max(0,f_diff);
    u[1] = abs(f_diff) - u[0];

    // ACTUATE
    actuate_motors(u);


    timer++;
}