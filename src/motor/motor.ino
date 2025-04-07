#include "motor.h"

const int frequency = 50; // Frequency in Hz

#define MAX_SIGNAL 26
#define MIN_SIGNAL 13
//Servo motor1;

void setup() {

    Serial.begin(9600);

    callibrate_motors(); // includes init

    delay(2000);

}

void loop() {

    write_speeds([50,50]); // in %

    delay(2000);

}
