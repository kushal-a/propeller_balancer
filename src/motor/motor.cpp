#include "motor.h"
#include "../propeller_balancer.h"

Servo[2] motors;

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000

void callibrate_motor(int motorNum){

    Serial.print("Now writing maximum output: (");Serial.print(MAX_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
    Serial.println("Turn on power source, then wait 2 seconds and press any key.");
    motor[motorNum].writeMicroseconds(MAX_SIGNAL);
  
    // Wait for input
    while (!Serial.available());
    Serial.read();
  
    // Send min output
    Serial.println("\n");
    Serial.println("\n");
    Serial.print("Sending minimum output: (");Serial.print(MIN_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
    motor[motorNum].writeMicroseconds(MIN_SIGNAL);
    Serial.println("The ESC is calibrated");
    Serial.println("----");
    Serial.println("Now, type a values between 1000 and 2000 and press enter");
    Serial.println("and the motor will start rotating.");
    Serial.println("Send 1000 to stop the motor and 2000 for full throttle");
  
}

void callibrate_motors(){
    init_motors();
    motor_callibrate(0);
    motor_callibrate(1);
}

Servo init_motor(int pin){
    Servo motor;
    motor.attach(pin,MIN_SIGNAL,MAX_SIGNAL);
    return motor;
}

void init_motors(){
    pinMode(MOTOR_L, OUTPUT);
    pinMode(MOTOR_R, OUTPUT);

    analogWriteFrequency(MOTOR_L, ESC_FREQ);
    analogWriteFrequency(MOTOR_R, ESC_FREQ);

    motors = [init_motor(MOTOR_L),init_motor(MOTOR_R)];
}

void write_speed(int motorNum, int speed){
    motors[motorNum].writeMicroseconds((MAX_SIGNAL-MIN_SIGNAL)*speed/100 + MIN_SIGNAL);
}

void write_speeds(int* speeds){
    write_speed(0,speeds[0]);
    write_speed(1,speeds[1]);
}

