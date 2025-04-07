#include "../propeller_balancer.h"

int timer;
int traj = 0;
int error;
float f_diff;
float u;

void setup(){
    init_devices();
    timer = 0
}

void loop(){


    // SENSE
    gyro_signals();

    // COMPUTE
    error = Theta - traj;
    f_diff = grav_force_diff();
    f_diff = pid_force_diff(timer, error);
    f_diff = net_force_diff(timer, error);

    u = [0,f_diff];

    // ACTUATE
    actuate_motors(u);


    timer++:
}