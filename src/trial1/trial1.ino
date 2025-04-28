#include "propeller_balancer.h"

float kp = 1;
float ki = 0;
float kd = 0;

int timer;
int traj = 0;
int error;
float f_diff;
float u[2];
int vel[2];

void reset_pid_test(int error){
    pid_P = 0;
    pid_I = 0;
    pid_D = 0;

    pid_last_e = error;
    pid_dt = 1;
}

int pid_test(int error){
    pid_P = kp*error;
    pid_I += ki*error;
    pid_D = kd*(error-pid_last_e)/pid_dt;
    pid_last_e = error;

    Serial.print("    P: ");
    Serial.print(pid_P);
    Serial.print("    I: ");
    Serial.print(pid_I);
    Serial.print("    D: ");
    Serial.print(pid_D);
    
    int pidVal = pid_P + pid_I + pid_D;

    Serial.print("    PID: ");
    Serial.print(pidVal);
    
    return pidVal;

}

int run_pid_test(int timer, int error){
    if (timer == 0) reset_pid_test(error);

    return pid_test(error);
}

void setup(){
    init_devices();
    timer = 0;
}

void loop(){
    Serial.print(timer);
    Serial.print("    ");

    // SENSE
    gyro_signals();

    Serial.print("Reading angle with vertical: ");
    Serial.print(Theta);
    Serial.print("    ");


    // COMPUTE
    error = traj - Theta;

    Serial.print("Error: ");
    Serial.print(error);


    // f_diff = grav_force_diff();
    // f_diff = pid_force_diff(timer, error);
    // f_diff = net_force_diff(timer, error);

    f_diff = run_pid_test(timer,error);


    u[0] = max(0,f_diff);
    u[1] = abs(f_diff) - u[0];

    // ACTUATE
    Serial.print("    uL: ");
    Serial.print(u[0]);
    Serial.print("    uR: ");
    Serial.print(u[1]);


    actuate_motors(u,vel);

    Serial.print("    velL: ");
    Serial.print(vel[0]);
    Serial.print("    velR: ");
    Serial.println(vel[1]);


    timer++;
}