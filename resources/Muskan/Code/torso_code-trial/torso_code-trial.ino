#include <Wire.h>

int pin1 = 9;
int pin2 = 10;
int frequency = 50;
#define max_signal 26
#define min_signal 13

//variables for mpu6050
float RateRoll, RatePitch, RateYaw;
float AccX, AccY, AccZ;
float AngleRoll, AnglePitch;

//variables for pid
unsigned long timePrev; 
unsigned long elapsedTime;
int i;
float rad_to_deg = 180/3.141592654;

float PID, pwmLeft, pwmRight, error, previous_error;
float pid_p=0;
float pid_i=0;
float pid_d=0;

//double kp=10;//3.55
//double ki=0.8;//0.005
//double kd=8;//2.05

double kp=10;//3.55
double ki=1.5;//0.005
double kd=8;//2.05

int pwm1, pwm2;

double throttle=1100; //initial value of throttle to the motors
float desired_angle = 0; //steady state


void setup() {
  // put your setup code here, to run once:
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);

  analogWriteFrequency(pin1, frequency);
  analogWriteFrequency(pin2, frequency);

  Wire.setClock (400000);  //specification on mcu6050
  Wire.begin();
  delay(250);

  setup_mpu_6050_registers();

  Serial.begin(9600);
  Serial.println("Program begin...");
  delay(1000);
  Serial.println("This program will start the ESC.");

  Serial.print("Now writing maximum output: (");Serial.print(max_signal);Serial.print(" in this case)");Serial.print("\n");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  analogWrite(pin1, max_signal);
  analogWrite(pin2, max_signal);

  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("\n");
  Serial.println("\n");
  Serial.print("Sending minimum output: (");Serial.print(min_signal);Serial.print(" us in this case)");Serial.print("\n");
  analogWrite(pin1, min_signal);
  analogWrite(pin2, min_signal);

  Serial.println("The ESC is calibrated");
  Serial.println("----");

  delay(2000);

  //unsigned long time = millis(); //Start counting time in milliseconds

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long time = millis();  // actual time read
  //double elapsedTime = (double)((time - timePrev) / 1000);

  read_mpu_6050_data();
  Serial.print(AngleRoll);
  Serial.print(",");

  //PID
  error = desired_angle - AngleRoll;
  /*Next the proportional value of the PID is just a proportional constant
*multiplied by the error*/

pid_p = kp*error;

/*The integral part should only act if we are close to the
desired position but we want to fine tune the error. That's
why I've made a if operation for an error between -2 and 2 degree.
To integrate we just sum the previous integral value with the
error multiplied by  the integral constant. This will integrate (increase)
the value each loop till we reach the 0 point*/
/*if(-3 <error <3)
{
  pid_i = pid_i+(ki*error);  
}*/

pid_i = ki*error*elapsedTime;

/*The last part is the derivate. The derivate acts upon the speed of the error.
As we know the speed is the amount of error that produced in a certain amount of
time divided by that time. For taht we will use a variable called previous_error.
We substract that value from the actual error and divide all by the elapsed time. 
Finnaly we multiply the result by the derivate constant*/

pid_d = kd*((error - previous_error)/elapsedTime);
//pid_d = kd*(error - previous_error);

//Serial.print(pid_p);
//Serial.print(",");
//Serial.print(pid_i);
//Serial.print(",");
//Serial.print(pid_d);
//Serial.print(",");

/*The final PID values is the sum of each of this 3 parts*/
PID = pid_p + pid_i + pid_d;

Serial.print(PID);
Serial.print(",");

/*We know taht the min value of PWM signal is 1000us and the max is 2000. So that
tells us that the PID value can/s oscilate more than -1000 and 1000 because when we
have a value of 2000us the maximum value taht we could sybstract is 1000 and when
we have a value of 1000us for the PWM sihnal, the maximum value that we could add is 1000
to reach the maximum 2000us*/
if(PID < -1000)
{
  PID=-1000;
}
if(PID > 1000)
{
  PID=1000;
}

/*Finnaly we calculate the PWM width. We sum the desired throttle and the PID value*/
pwmLeft = throttle + PID;
pwmRight = throttle - PID;


/*Once again we map the PWM values to be sure that we won't pass the min
and max values. Yes, we've already maped the PID values. But for example, for 
throttle value of 1300, if we sum the max PID value we would have 2300us and
that will mess up the ESC.*/
//Right
if(pwmRight < 1000)
{
  pwmRight= 1000;
}
if(pwmRight > 2000)
{
  pwmRight=2000;
}
//Left
if(pwmLeft < 1000)
{
  pwmLeft= 1000;
}
if(pwmLeft > 2000)
{
  pwmLeft=2000;
}

pwm1 = map(pwmRight, 1000, 2000, 13, 26);
pwm2 = map(pwmLeft, 1000, 2000, 13, 26);
/*Finnaly using the servo function we create the PWM pulses with the calculated
width for each pulse*/

analogWrite(pin1, pwm1);
analogWrite(pin2, pwm2);

//Serial.print("pwm1 = ");
Serial.print(pwm1);
Serial.print(",");
//Serial.print("pwm2 = ");
Serial.println(pwm2);

previous_error = error; //Remember to store the previous error.
elapsedTime = time - timePrev;
timePrev = time;

//Serial.print(time);
//Serial.print(",");
//Serial.print(timePrev);
//Serial.print(",");
//Serial.println(elapsedTime);

}

void setup_mpu_6050_registers(){

  //Activate the MPU-6050
  Wire.beginTransmission(0x68);
  Wire.write (0x6B);  //start gyro in power mode using power management register
  Wire.write (0x00);  //set to zero for device to start and continue in power mode
  Wire.endTransmission();
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68); 
  //switch to low pass filter                                       
  Wire.write(0x1A);  
  //set the cutoff freq of the gyro to 10Hz                                                  
  Wire.write(0x05);
  //End the transmission                                                    
  Wire.endTransmission(); 
                                              
  //Configure the accelerometer (+/-8g)
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68); 
  //Send the requested starting register                                       
  Wire.write(0x1C);   
  //Configure the accelerometer output                                                 
  Wire.write(0x10); 
  //set the full scale range of 8g = LSB sensitivity = 4096LSB/g                                                   
  Wire.endTransmission(); 
                                              
  //Configure the gyro (500dps full scale)
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68);
  //Send the requested starting register                                        
  Wire.write(0x1B);
  //Set the requested starting register                                                    
  Wire.write(0x8); 
  //End the transmission                                                  
  Wire.endTransmission(); 
                                              
}

void read_mpu_6050_data(){ 

  //Read the raw gyro and accelerometer data

  //Start communicating with the MPU-6050                                          
  Wire.beginTransmission(0x68);  
  //Send the requested starting register                                      
  Wire.write(0x3B);
  //End the transmission                                                    
  Wire.endTransmission(); 
                               
  Wire.requestFrom(0x68,6);  //pull info from six registers   

  int16_t AccXLSB=Wire.read()<<8 | Wire.read(); //measurement of the acc is set to 16-bit and read measurements around x-axis
  int16_t AccYLSB=Wire.read()<<8 | Wire.read(); //measurement of the acc is set to 16-bit and read measurements around y-axis
  int16_t AccZLSB=Wire.read()<<8 | Wire.read(); //measurement of the acc is set to 16-bit and read measurements around z-axis

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

  AccX = (float)AccXLSB/4096; //Convert measurements to physical values
  AccY = (float)AccYLSB/4096; //Convert measurements to physical values
  AccZ = (float)AccZLSB/4096; //Convert measurements to physical values

  AngleRoll = (atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*180/3.142)+4;
  AnglePitch = (atan(AccX/sqrt(AccY*AccY+AccZ*AccZ))*180/3.142)-3;

}
