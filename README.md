# propeller_balancer
This repository contains the software required to supervise the `propeller_balancer` developed as a part of my Bachelor's Thesis at Indian Institute of Technology Bombay under the guidance of Prof. Vivek Sangwan. 

# How to use the hardware
The mechanical parts of the project include a semi-circular cylinder on the bottom along with a3D printed part to house the electronics. A 2020T Aluminum profile supports the motors and the end-stops. The acrylic on top of the profile provides space for electronics which are to remain accessible for testing, development and learning.

## Components used
1. Teensy 4.1 microcontroller
2. MPU 6050 IMU sensor for acceleration and gyrometry data
3. 30A BLDC ESC (x2)
4. CC3D BEC (Battery Eliminator Circuit) /Z Power Distribution Board

## Connections
A 10 row port is installed in the hood of the bot. The schematic is shown below.

Internally, the `5V` and `GND` for MUC and IMU are shorted and connected to the Power Distribution board. The `SDA`, `SCL` wires are shorted with jumpers to connect the MUC to the IMU. The `PWMx` pins are connected to the ESC. The `GND` of the ESC's are also connected to the common ground. 

Connect a 10-wire F-F jumper ribbon to the port. First 2 wire connect to `pin1` and `pin2` of the MUC. Next 4 connect to `pins17-14` without twisting. The final 4 connect to the IMU. TODO: Order.

# How to use the package (software)





## Getting started with Teensy

1. Install Arduino IDE
2. Copy and paste the following link in `Arduino IDE`>`File`>`Preferences`>`Additional board manager URLs`
``` html
https://www.pjrc.com/teensy/package_teensy_index.json
```
3. In Arduino IDE go to `Tools`>`Board`>`Board Manager`. Search for Teensy and install the board.
4. Try out your setup with the blink example.
5. Press the button on the Teensy after uploading for it to go into Program mode to receive the compiled code. Once you see Reboot OK, the upload is done.

Ref: https://www.pjrc.com/teensy/tutorial.html

## Setting up IMU
IMU used: MPU 6050 standard IMU sensor

### Power and Communication
Power the IMU with 5V (and GND) from the microcontroller or the power distribution board. For best results, use 5V supply from the power distribution board. 

MPU 6050 uses I2C communication (SDA and SCL) lines. The I2C address of the sensor is 0x68. Connect the SDA and SCL lines of the microcontroller with that of the IMU.

### Software
To communicate with the MPU, we will I2C communication, known as wire communcation in arduino software. Hence, the standard `Wire.h` library will be used. `src/imu` directory has source code for IMU functionality. Import `src/imu/imu.h` for access to IMU functionality. The library provides access to `Theta`, `RateTheta`, `AccX`, `AccY` and `AccZ`. Here, $\theta$ is the nominal angle required for the project. $\theta$ is 0 when the bot balances perfectly.

### Callibration
TODO


## Setting us ESC

### Power and communication
ESC required a 12V input. Connect the two input wires of the ESC with the power supply. ESC provides 3 phase output for motor control; connect the 3 output wires to the motor. It also provides a 5V output (and GND) and takes in a throttle input via jumpers. Ensure to connect the ground of the ESC(s) (and IMU) and microcontroller. The 5V supply of the ESC is unrellibale and hence not used. Throttle is provided as a PWM signal. Speed is proportional to the width of the PWM pulse.

### Software
A BLDC motor with a ESC taking PWM input essentially acts like a servo motor and hence the standard `Servo.h` library is used for producing the PWM. `src/motor` directory has source code for running the motor. Import `src/motor/motor.h` for access to motor functionality. The library provides access to functions to directly produce required PWM signal.

50Hz PWM has is a 20ms period. 
| Duration of high signal per period | Effect in Servo | Effect in BLDC |
| :-----| :----: | :----: |
|1ms|0 degrees|min RPM|
|2ms| 180 degrees|max RPM|

### Callibration 
Every ESC has to caallibrated. The input PWM frequency can vary from 50-60Hz and min max pulse width can vary about 1ms and 2ms respectively. 

For some reason the callibration of both motors simulataneously by code 

## Using the Power Distribution Board
The power distribution board needs a 12V supply. Adjacent to the spots for 12V supply to the ESC. These lines are shorted. On the other end, the 5V terminals will be used to power the microcontroller. The power distribution board has a battery eliminator circuit (BEC) to eliminated the need of a seperate battery for the microcontroller.

# Resources
[1] Teensy KiCAD footprint @ https://github.com/XenGi/teensy.pretty

[2] Teensy KiCAD symbol @ https://github.com/XenGi/teensy_library
# Credits
[1] __Muskan Patel__ and __Kyari Ponkiya__ for initial work on the project.

[2] __Mechatronics Lab__, IIT Bombay for workspace and technological support. __Mr. Tejas__ and __Mr. Vijay__ from Mechatronics Lab.

[3] Members of __INDUS Lab__, IIT Bombay for their support.

[4] __Microfactory__, IIT Bombay with machinary support.
