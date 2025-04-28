#ifndef PB_MOTOR
#define PB_MOTOR

#include <Servo.h>
#include <Arduino.h>

extern Servo motors[2];

void callibrate_motors();
void init_motors();
void write_speed(int motorNum, int speed);
void write_speeds(int* speeds);
void callibrate_motor(int motorNum);

#endif