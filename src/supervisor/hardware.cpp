#include "hardware.h"

/// White Line Sensor Values ///////////
void wls_init() {
  pinMode(Clock, OUTPUT);
  pinMode(Address, OUTPUT);
  pinMode(DataOut, INPUT);
  pinMode(CS, OUTPUT);
}

void AnalogRead(int *sensorValues) {
  char i,j;
  unsigned int channel = 0;
  unsigned int values[] = {0,0,0,0,0,0,0,0};

  for(j = 0;j < 5 + 1;j++)
  {
    digitalWrite(CS,LOW);
    for(i = 0;i < 8;i++)
    {
      if(i<4)
      {
        //0 to 4 clock transfer channel address
        if((j >> (3 - i) & 0x01))
          digitalWrite(Address,HIGH);
        else
          digitalWrite(Address,LOW);
      }
      else
      {
        digitalWrite(Address,LOW);
      }
      

      //0 to 10 clock receives the previous conversion result
      values[j] <<= 1;
      if(digitalRead(DataOut)) 
      values[j] |= 0x01;
      digitalWrite(Clock,HIGH);
      digitalWrite(Clock,LOW);
    }
    //sent 11 to 16 clock 
    for(i = 0;i < 4;i++)
    {
      values[j] <<= 1;
      if(digitalRead(DataOut)) 
      values[j] |= 0x01;
      digitalWrite(Clock,HIGH);
      digitalWrite(Clock,LOW);
    }
    digitalWrite(CS,HIGH);
  }
  for(i = 0;i < 5 + 1;i++)
  {
    values[i] = values[i] >> 2;
  }

  for(i = 0;i < 5;i++)
  {
    sensorValues[i] = values[i+1];
  }
}

/// Motion related ///////////



void motion(bool LF, bool LB, bool RF, bool RB) {
  digitalWrite(INLF, LF);
  digitalWrite(INLB, LB);
  digitalWrite(INRF, RF);
  digitalWrite(INRB, RB);
}

void forward() {
    motion(HIGH, LOW, HIGH, LOW);
}

void backward() {
    motion(LOW, HIGH, LOW, HIGH);
}

void right() {
    motion(HIGH, LOW, LOW, HIGH);
}

void left() {
    motion(LOW, HIGH, HIGH, LOW);
}

void forward_right() {
    motion(HIGH, LOW, LOW, LOW);
}

void forward_left() {
    motion(LOW, LOW, HIGH, LOW);
}

void back_right() {
    motion(LOW, LOW, LOW, HIGH);
}

void back_left() {
    motion(LOW, HIGH, LOW, LOW);
}

void stop() {
    motion(LOW, LOW, LOW, LOW);
}

void SetSpeed(char LSpeed,char RSpeed) {
  analogWrite(ENR, RSpeed);  
  analogWrite(ENL, LSpeed);  
}
void motion_init() {
  pinMode(ENL, OUTPUT);
  pinMode(ENR, OUTPUT);
  pinMode(INLF, OUTPUT);
  pinMode(INLB, OUTPUT);
  pinMode(INRF, OUTPUT);
  pinMode(INRB, OUTPUT);
  // SetSpeed(100, 100);
}

///  Port expander related //////////

void port_expander_init() {
    Wire.begin();
}

void PCF8574Write(byte data)
{
  Wire.beginTransmission(Addr);
  Wire.write(data);
  Wire.endTransmission(); 
}

byte PCF8574Read()
{
  int data = -1;
  Wire.requestFrom(Addr, 1);
  if(Wire.available()) {
    data = Wire.read();
  }
  return data;
}


void beep_on() {
     PCF8574Write(0xDF & PCF8574Read());
}

void beep_off() {
     PCF8574Write(0x20 | PCF8574Read());
}

char joystick_read() {
  char return_val = 'n';
    PCF8574Write(0x1F | PCF8574Read());
  byte value = PCF8574Read() | 0xE0;
  if(value != 0xFF)
  {
    switch(value)
    { 
      case 0xFE:  // up
        return_val = 'u';
        break; 
      case 0xFD:  // right
        return_val = 'r';
        break;
      case 0xFB:  // left
        return_val = 'l';
        break; 
      case 0xF7:  // down
        return_val = 'd';
        break;
      case 0xEF:   // center
        return_val = 'c';
        break;
    }
    while(value != 0xFF)
    {
      PCF8574Write(0x1F | PCF8574Read());
      value = PCF8574Read() | 0xE0;
      delay(10);
    }
  }
  return (return_val);
}

char ir_read() {
  PCF8574Write(0xC0 | PCF8574Read());   //set Pin High
  byte value = PCF8574Read() | 0x3F;         //read Pin
  if(value != 0xFF)
  {
    if (value == 63)
    return ('b');
    if (value == 127)
    return ('l');
    else
    return ('r');
  }
  return('n');
}

///////  Ultrasonic related ///
void ultrasonic_init(){
  pinMode(ECHO, INPUT);    // Define the ultrasonic echo input pin
  pinMode(TRIG, OUTPUT);   // Define the ultrasonic trigger input pin 
}


int Distance_test()         // Measure the distance 
{
  digitalWrite(TRIG, LOW);   // set trig pin low 2μs
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);  // set trig pin 10μs , at last 10us 
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);    // set trig pin low
  float Fdistance = pulseIn(ECHO, HIGH);  // Read echo pin high level time(us)
  Fdistance= Fdistance/58;       //Y m=（X s*344）/2
  // X s=（ 2*Y m）/344 ==》X s=0.0058*Y m ==》cm = us /58       
  return (int)Fdistance;
}  

void init_devices(){
  ultrasonic_init();
  port_expander_init();
  motion_init();
  wls_init();
}
