#include "motor.h"
#include "propeller_balancer.h"

Servo motors[2];

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000

void callibrate_motor(int motorNum){

    Serial.print("Now writing maximum output: (");Serial.print(MAX_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
    motors[motorNum].writeMicroseconds(MAX_SIGNAL);
    Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  
    // Wait for input
    while (!Serial.available());
    Serial.println(Serial.read());
  
    // Send min output
    Serial.println("\n");
    Serial.println("\n");
    Serial.print("Sending minimum output: (");Serial.print(MIN_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
    motors[motorNum].writeMicroseconds(MIN_SIGNAL);
    delay(5000);
    Serial.println("The ESC is calibrated");
    Serial.println("----");
}

// void callibrate_motors(){
//     init_motors();
//     callibrate_motor(0);
//     delay(2000);
//     callibrate_motor(1);
// }

void callibrate_motors(){
    Serial.print("Now writing maximum output: (");Serial.print(MAX_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
    motors[0].writeMicroseconds(MAX_SIGNAL);
    delay(1000);
    motors[1].writeMicroseconds(MAX_SIGNAL);
    Serial.println("Turn on power source, then wait 2 seconds and press any key.");
    // Wait for input
    while (!Serial.available());
    Serial.println(Serial.read());
  
    // Send min output
    Serial.println("\n");
    Serial.println("\n");
    delay(2000);
    Serial.print("Sending minimum output: (");Serial.print(MIN_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
    motors[0].writeMicroseconds(MIN_SIGNAL);
    delay(1000);
    motors[1].writeMicroseconds(MIN_SIGNAL);
    delay(5000);
    Serial.println("The ESC is calibrated");
    Serial.println("----");
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

    motors[0] = init_motor(MOTOR_L);
    motors[1] = init_motor(MOTOR_R);
}

void write_speed(int motorNum, int speed){
    motors[motorNum].writeMicroseconds((MAX_SIGNAL-MIN_SIGNAL)*speed/100 + MIN_SIGNAL);
}

void write_speeds(int* speeds){
    write_speed(0,speeds[0]);
    write_speed(1,speeds[1]);
}

