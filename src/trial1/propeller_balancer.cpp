#include "propeller_balancer.h"
#include <math.h>

float pid_P = 0;
float pid_I = 0;
float pid_D = 0;
int pid_last_e = 0;
float pid_dt = 0.000005;

int um,alpha1,I;

void init_consts(){
    um = KAPPA * MASS * GRAVITY;
    alpha1 = 2*H_COM/(KAPPA*L_PP);
    I = INERTIA + MASS*H_COM*H_COM;
}

void init_devices(){
    init_imu();
    init_motors();
    init_consts();
}

void reset_pid(float error){
    pid_P = 0;
    pid_I = 0;
    pid_D = 0;

    pid_last_e = error;
    pid_dt = 0.000005;
}

int pid(float error){
    pid_P = kp*error;
    pid_I += ki*error*pid_dt;
    pid_D = kd*(error-pid_last_e)/pid_dt;
    pid_last_e = error;

    return pid_P + pid_I + pid_D;

}

int run_pid(int timer, float error){
    if (timer == 0) reset_pid(error);

    return pid(error);
}

float saturation(float r){
    if (r< ALPHA2) return r;

    return 1 - (1 - ALPHA2) * exp( (ALPHA2 - r) / (1 - ALPHA2));
}

int thrust_to_speed(float thrust){
    return sqrt(thrust/KF);
}

void actuate_motors(float* thrusts){
    int vel[2];

    actuate_motors(thrusts,vel);

}

void actuate_motors(float* thrusts, int* vel){

    // vel[0] = thrust_to_speed(thrusts[0]);
    // vel[1] = thrust_to_speed(thrusts[1]);

    vel[0] = thrusts[0];
    vel[1] = thrusts[1];

    // if (vel[0]>30) vel[0] = 30;
    // if (vel[1]>30) vel[1] = 30;
    

    write_speeds(vel);

}

int actuate_motor(int motorNum, float thrust){
    int vel;
    vel = thrust_to_speed(thrust);

    if (vel>30) vel = 30;
    write_speed(motorNum, vel);

    return vel;
}

int grav_force_diff(){
    return -alpha1*um*sin(PI*Theta/180);
}

int pid_force_diff(int timer, float error){
    return (2*I/L_PP)*run_pid(timer,error);
}

int net_force_diff(int timer, float error){
    return pid_force_diff(timer,error) + grav_force_diff();
}











