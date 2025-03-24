#include <Wire.h>

float RateRoll, RatePitch, RateYaw;

float caliroll, calipitch, caliyaw;
int Ratecalinumber;

void gyro_signals(void) {

  Wire.beginTransmission(0x68);  //Start i2c communication with gyro

  Wire.write(0x1A);  //switch to low pass filter
  Wire.write(0x05);  //set the cutoff freq of the gyro to 10Hz
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x1B);  //set sensitivity scale factor
  Wire.write(0x8);  //set lsb sensivity to 65.5lsb/deg/s
  Wire.endTransmission();
  
  Wire.beginTransmission(0x68);
  Wire.write(0x43);  //use the first register to get measurements of gyro
  Wire.endTransmission();
  
  Wire.requestFrom(0x68,6);  //pull info from six registers 67-72
  
  int16_t GyroX=Wire.read()<<8 | Wire.read(); //measurement of the gyro is set to 16-bit and read measurements around x-axis
  int16_t GyroY=Wire.read()<<8 | Wire.read(); //measurement of the gyro is set to 16-bit and read measurements around y-axis
  int16_t GyroZ=Wire.read()<<8 | Wire.read(); //measurement of the gyro is set to 16-bit and read measurements around z-axis

  RateRoll=(float)GyroX/65.5; //Convert measurements to deg/sec
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;

}

void setup() {

  Serial.begin(57600);
  pinMode(13, OUTPUT);
  digitalWrite (13,HIGH);
  
  Wire.setClock (400000);  //specification on mcu6050
  Wire.begin();
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write (0x6B);  //start gyro in power mode using power management register
  Wire.write (0x00);  //set to zero for device to start and continue in power mode
  Wire.endTransmission();

  for(Ratecalinumber=0;Ratecalinumber<2000;Ratecalinumber++){

    gyro_signals();
    caliroll+=RateRoll;
    calipitch+=RatePitch;
    caliyaw+=RateYaw;
    delay(1);
  }

  caliroll/=2000;
  calipitch/=2000;
  caliyaw/=2000;

}

void loop() {

gyro_signals();

RateRoll-=caliroll;
RatePitch-=calipitch;
RateYaw-=caliyaw;

Serial.print("Roll rate [deg/s] = "); 
Serial.print(RateRoll); 
Serial.print("Pitch Rate [deg/s] = "); 
Serial.print(RatePitch);
Serial.print("Yaw Rate [deg/s] = ");
Serial.println(RateYaw);

delay(50);

}