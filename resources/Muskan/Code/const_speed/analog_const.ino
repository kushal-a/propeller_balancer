//#include <Servo.h>

const int pwmPin = 9; // Choose any PWM capable pin
const int pwmPin1 = 10;
const int frequency = 50; // Frequency in Hz
//const int dutyCycle = 100; // Duty cycle percentage

#define MAX_SIGNAL 26
#define MIN_SIGNAL 13
//Servo motor1;

void setup() {
  // Initialize PWM pin
  pinMode(pwmPin, OUTPUT);
  pinMode(pwmPin1, OUTPUT);

  // Configure PWM frequency
  analogWriteFrequency(pwmPin, frequency);
  analogWriteFrequency(pwmPin1, frequency);

  Serial.begin(9600);

  Serial.println("Program begin...");
  delay(1000);
  Serial.println("This program will start the ESC.");

  //motor1.attach(pwmPin);
  //motor2.attach(pin2);

  Serial.print("Now writing maximum output: (");Serial.print(MAX_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  //motor1.writeMicroseconds(MAX_SIGNAL);
  analogWrite(pwmPin, MAX_SIGNAL);
  analogWrite(pwmPin1, MAX_SIGNAL);
  //motor2.writeMicroseconds(MAX_SIGNAL);
  //analogWrite(pin2,MAX_SIGNAL);

  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("\n");
  Serial.println("\n");
  Serial.print("Sending minimum output: (");Serial.print(MIN_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
  //motor1.writeMicroseconds(MIN_SIGNAL);
  analogWrite(pwmPin, MIN_SIGNAL);
  analogWrite(pwmPin1, MIN_SIGNAL);
  //motor2.writeMicroseconds(MIN_SIGNAL);
  //analogWrite(pin2,MIN_SIGNAL);
  Serial.println("The ESC is calibrated");
  Serial.println("----");
  
  delay(2000);

}

void loop() {
  // Calculate the duty cycle value
  //int dutyCycleValue = (5 * 255) / 100;
  
  // Set PWM duty cycle
  analogWrite(pwmPin, 16);
  //analogWrite(pwmPin1, 16);
  delay(2000);

}
