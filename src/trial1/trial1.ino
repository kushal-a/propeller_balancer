#include "propeller_balancer.h"

float kp = 1.4;
float ki = 80;
float kd = 1.2;

int timer;
int traj = 0;
float error = 0;
float RateError = 0;
float f_diff;
float u[2];
int vel[2];
int pidVal = 0;

void reset_pid_test(float error){
    pid_P = 0;
    pid_I = 0;
    pid_D = 0;

    pid_last_e = error;
    pid_dt = 0.000005;
}

int pid_test(float error, float RateError){
    if (abs(error)<40){
    
      pid_P = kp*error;
      pid_I += ki*error*pid_dt;
      if (abs(RateError) > 1.0 ){
        pid_D = -kd*RateError;///pid_dt;
      } else {
        pid_D = 0;
      }
      pid_last_e = error;
      pidVal = pid_P + pid_I + pid_D;
    
    } else {
      pid_P = 0;
      // pid_I += ki*error*pid_dt;
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

int run_pid_test(int timer, float error, float RateError){
    if (timer == 0) reset_pid_test(error);

    return pid_test(error,RateError);
}

void setup(){
    init_devices();
    timer = 0;
    Serial.println("Turn on power supply within 5 seconds");
    delay(5000);
    Serial.println("Running in 3 seconds");
    delay(3000);
}

void loop(){
    Serial.print(timer);

    // SENSE
    gyro_signals();

    Serial.print("\t");
    Serial.print("Angle:");
    Serial.print(Theta);
    Serial.print("\t");
    Serial.print("AngleRate:");
    Serial.print(RateTheta);


    // COMPUTE
    error = traj - Theta;
    RateError = traj - RateTheta;

    Serial.print("\t");
    Serial.print("Error:");
    Serial.print(error);
    Serial.print("\t");
    Serial.print("ErrorRate:");
    Serial.print(RateError);
    


    // f_diff = grav_force_diff();
    // f_diff = pid_force_diff(timer, error);
    // f_diff = net_force_diff(timer, error);

    f_diff = run_pid_test(timer,error,RateError);


    u[0] = max(0,f_diff);
    u[1] = abs(f_diff) - u[0];

    // ACTUATE
    // Serial.print("uL:");
    // Serial.print(u[0]);
    // Serial.print("uR:");
    // Serial.print(u[1]);


    actuate_motors(u,vel);

    Serial.print("\t");
    Serial.print("velL:");
    Serial.print(vel[0]);
    Serial.print("\t");
    Serial.print("velR:");
    Serial.println(vel[1]);


    timer++;
}