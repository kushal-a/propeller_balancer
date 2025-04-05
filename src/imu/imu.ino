#include "imu.h"


void setup() {

  Serial.begin(9600);
  
  imu_init();

}

void loop() {

gyro_signals();

Serial.print("Theta [deg] = "); 
Serial.print(Theta); 

Serial.print("    ThetaDot [deg/s] = "); 
Serial.print(RateTheta);

Serial.print("    ThetaDDot [g] = "); 
Serial.print(AccX); 

Serial.println(" ");

delay(100);

}