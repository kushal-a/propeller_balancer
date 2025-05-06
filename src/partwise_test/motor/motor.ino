#include "motor.h"

const int frequency = 50; // Frequency in Hz

#define MAX_SIGNAL 26
#define MIN_SIGNAL 13
//Servo motor1;

void setup() {

    Serial.begin(9600);

    init_motors(); 
    callibrate_motors(); 
    // callibrate_motor(0);

    delay(2000);

}
// 123 1    11 1_
void loop() {

  while (!Serial.available());
  int v = Serial.parseInt();
  
  if (v>0){
      Serial.println(v);
      int vel[2] = {v,v};
      write_speeds(vel); // in %
      delay(2000);
  }
  else if (v==-1) {
    callibrate_motors();
  }
}
