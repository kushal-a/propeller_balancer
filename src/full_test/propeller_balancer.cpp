#include "propeller_balancer.h"
#include "imu.h"
#include "motor.h"
#include <math.h>

int pid_P;
int pid_I;
int pid_D;
int pid_last_e;
int pid_dt;
int pidVal = 0;

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

int pid(float error, float RateError){
    if (abs(error)<40){
    
      pid_P = kp*error;
      pid_I += ki*error*pid_dt;
      if (abs(RateError) > 1.0 ){
        pid_D = -kd*RateError;
      } else {
        pid_D = 0;
      }
      pid_last_e = error;
      pidVal = pid_P + pid_I + pid_D;
    
    } else {
      pid_P = 0;
      pid_D = 0;
      pidVal = 0;
    }

    Serial.print("\t");
    Serial.print("P:");
    Serial.print(pid_P);
    Serial.print("\t");
    Serial.print("I:");
    Serial.print(pid_I);
    Serial.print("\t");
    Serial.print("D:");
    Serial.print(pid_D);
    
    

    Serial.print("\t");
    Serial.print("PID:");
    Serial.print(pidVal);
    
    return pidVal;

}

int run_pid(int timer, float error, float RateError){
    if (timer == 0) reset_pid(error);

    return pid(error, RateError);
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

// FOR FEEDFORWARD CONTROL
// REQUIRED DEBUGGING - Kushal
// int grav_force_diff(){
//     return -alpha1*um*sin(PI*Theta/180);
// }

// int pid_force_diff(int timer, int error){
//     return (2*I/L_PP)*run_pid(timer,error);
// }

// int net_force_diff(int timer, int error){
//     return pid_force_diff(timer,error) + grav_force_diff();
// }











