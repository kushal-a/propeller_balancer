#include <Wire.h>
#include "imu.h"

float RateTheta;

float AccX;
float AccY;
float AccZ;
float Theta = 0; 

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
    // int16_t GyroY=Wire.read()<<8 | Wire.read(); //measurement of the gyro is set to 16-bit and read measurements around y-axis
    // int16_t GyroZ=Wire.read()<<8 | Wire.read(); //measurement of the gyro is set to 16-bit and read measurements around z-axis
  
    RateTheta=((float)GyroX/65.5); //Convert measurements to deg/sec
  
    AccX = (float)AccXLSB/4096; //Convert measurements to physical values
    AccY = (float)AccYLSB/4096; //Convert measurements to physical values
    AccZ = (float)AccZLSB/4096; //Convert measurements to physical values
  
    Theta = (atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*180/3.142)+4;
  
  }


void init_imu(){
    Wire.setClock (400000);  //specification on mcu6050
    Wire.begin();
    delay(250);

    Wire.beginTransmission(0x68);
    Wire.write (0x6B);  //start gyro in power mode using power management register
    Wire.write (0x00);  //set to zero for device to start and continue in power mode
    Wire.endTransmission();
}

