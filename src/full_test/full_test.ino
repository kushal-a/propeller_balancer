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
    

    f_diff = run_pid(timer,error,RateError);


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