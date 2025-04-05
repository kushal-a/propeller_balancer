#include "Arduino.h"
#include <Wire.h>


#define Clock     13
#define Address   12
#define DataOut   11
#define CS        10

#define NUM_SENSORS 5

#define DefaultSpeed 255
#define ENL 6
#define ENR 5

#define INLF A0
#define INLB A1
#define INRF A3
#define INRB A2

#define Addr  0x20

#define ECHO   2
#define TRIG   3

#define PIN 7

void sensor_init(void);
void AnalogRead(int *);

void motion_init(void);
void forward(void);
void backward();
void right();
void left();
void forward_right();
void forward_left();
void back_right();
void back_left();
void stop();
void SetSpeed(char ,char );

void beep_on();
void beep_off();

char joystick_read();
char ir_read();

void ultrasonic_init();
int Distance_test();

void init_devices();
