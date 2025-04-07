#include <Servo.h>

extern Servo[2] motors;

void callibrate_motors();
void init_motors();
void write_speed(int motorNum, int speed);
void write_speeds(int* speeds);
