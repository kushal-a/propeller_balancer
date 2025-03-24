#include <Wire.h>

float RateRoll, RatePitch, RateYaw;

float AccX, AccY, AccZ;
float AngleRoll, AnglePitch; 

float LoopTimer;

void gyro_signals(void) {

  Wire.beginTransmission(0x68);  //Start i2c communication with gyro
  Wire.write(0x1A);  //switch to low pass filter
  Wire.write(0x05);  //set the cutoff freq of the gyro to 10Hz
  Wire.endTransmission();

  Wire.beginTransmission(0x68);  //Start i2c communication with gyro
  Wire.write(0x1C);  //Configure the accelerometer output
  Wire.write(0x10);  //set the full scale range of 8g = LSB sensitivity = 4096LSB/g
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x3B); //Accelerometer measurements register
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);  //pull info from six registers
  
  int16_t AccXLSB=Wire.read()<<8 | Wire.read(); //measurement of the acc is set to 16-bit and read measurements around x-axis
  int16_t AccYLSB=Wire.read()<<8 | Wire.read(); //measurement of the acc is set to 16-bit and read measurements around y-axis
  int16_t AccZLSB=Wire.read()<<8 | Wire.read(); //measurement of the acc is set to 16-bit and read measurements around z-axis

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

  RateRoll=((float)GyroX/65.5); //Convert measurements to deg/sec
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;

  AccX = (float)AccXLSB/4096; //Convert measurements to physical values
  AccY = (float)AccYLSB/4096; //Convert measurements to physical values
  AccZ = (float)AccZLSB/4096; //Convert measurements to physical values

  AngleRoll = (atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*180/3.142)+4;
  AnglePitch = (atan(AccX/sqrt(AccY*AccY+AccZ*AccZ))*180/3.142)-3;

}

void setup() {

  Serial.begin(9600);
  //pinMode(13, OUTPUT);
  //digitalWrite (13,HIGH);
  
  Wire.setClock (400000);  //specification on mcu6050
  Wire.begin();
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write (0x6B);  //start gyro in power mode using power management register
  Wire.write (0x00);  //set to zero for device to start and continue in power mode
  Wire.endTransmission();

}

void loop() {

gyro_signals();

//Serial.print("Roll angle [deg] = "); 
Serial.print(AngleRoll); 
Serial.print(",");

//Serial.print("Pitch angle [deg] = "); 
Serial.println(AnglePitch);
//Serial.print(",");

//Serial.print(RateRoll);
//Serial.print(",");

//Serial.print(RatePitch);
//Serial.print(",");

//Serial.print("Roll acc [g] = "); 
//Serial.print(AccX); 
//Serial.print(",");

//Serial.print("Pitch acc [g] = "); 
//Serial.println(AccY);
//Serial.println(" ");
//Serial.print("Yaw acc [g] = ");
//Serial.println(AccZ);

delay(100);

}