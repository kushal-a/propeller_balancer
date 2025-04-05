#include "propeller_balancer.h"
#include "hardware.h"

#define NUM_SENSORS 5
int sensorValue;


#define MOTOR_MIN [24, 22]

Propeller_balancer__main_out _res;
Propeller_balancer__main_mem _mem;





void callibrate(){
  
}



void setup()
{
  init_devices();

  Serial.begin(115200);
}

void loop()
{
  AnalogRead(sensorValues);
  Propeller_balancer__main_step(sensorValues, &_res, &_mem);
  // // callibrate();



  // delay(20);

}
