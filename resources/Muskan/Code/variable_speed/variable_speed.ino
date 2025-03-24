const int pin = 9;
const int freq = 50;

#define max_signal 26
#define min_signal 13

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  analogWriteFrequency(pin, freq);

  Serial.begin(9600);

  Serial.println("Program begin...");
  delay(1000);
  Serial.println("This program will start the ESC.");
  Serial.print("Now writing maximum output: (");Serial.print(max_signal);Serial.print(" us in this case)");Serial.print("\n");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  analogWrite(pin, max_signal);

  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("\n");
  Serial.println("\n");
  Serial.print("Sending minimum output: (");Serial.print(min_signal);Serial.print(" us in this case)");Serial.print("\n");
  analogWrite(pin, min_signal);

  Serial.println("The ESC is calibrated");
  Serial.println("----");
  
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(pin, 14);
  delay(500);
  analogWrite(pin, 15);
  delay(500);
  analogWrite(pin, 16);
  delay(500);
  analogWrite(pin, 17);
  delay(500);
  analogWrite(pin, 18);
  delay(500);
  analogWrite(pin, 19);
  delay(500);

}
