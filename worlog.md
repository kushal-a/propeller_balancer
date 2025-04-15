# 15/04

## Testing of motor to get motor constant

### Test 1
#### Aim 
Checking variability of speed of motor (without propeller)
#### Setup
1. Test conducted without propeller. 
2. Code run: motor.ino. 
3. Speed given as % input from Serial monitor.
#### Observations
1. As motor speed input was increasing the motor speed was monotonically increasing. The speed was judged by manually hearing the sound made by the motor. Higher frequency implying faster rotation.
2. Motor only started rotating when motor speed was >=10%

### Test 2

Checking variability of thrust by varying speed of motor-propeller setup
#### Setup
1. Test conducted with propeller. 
2. Code run: motor.ino. 
3. Speed given as % input from Serial monitor.
4. The motor was mounted to a wooden plank and the wooden plank was taped to an iron block of mass ~2.8Kgs. The entire setup is placed on a weighing scale and set to 0 when the motor is not rotating.
#### Observations
1. As motor speed input was increasing the motor-propeller sped up until 40% after which it was abmigious. The speed was judged by manually hearing the sound made by the motor. Higher frequency implying faster rotation.
    1. After this observation, the ESC was recallibrated and test was run again. Same observations were noted.
    2. The propeller was then removed and test 1 was run again. The earlier made observations of test 1 stood again.
2. Motor only started rotating when motor speed was >=10%.
3. Raw data collected from the test is available in `data`>`thrust_test`.

#### Conclusion
1. There is some interference in the motor speed phenomenon on adding the propeller.
2. Current reading should be noted to eliminate current limitng effects.

### Test 3

Checking variability of thrust and current by varying speed of motor-propeller setup
#### Setup
1. Test conducted with propeller. 
2. Code run: motor.ino. 
3. Speed given as % input from Serial monitor.
4. The motor was mounted to a wooden plank and the wooden plank was taped to an iron block of mass ~2.8Kgs. The entire setup is placed on a weighing scale and set to 0 when the motor is not rotating.
#### Observations
1. As motor speed input was increasing the motor-propeller sped up until 40% after which it was abmigious. The speed was judged by manually hearing the sound made by the motor. Higher frequency implying faster rotation.
2. Current reached 1.88A at 40% speed and saturated there after that. The power supply used had a limiting current of 2A.
3. Raw data collected from the test is available in `data`>`thrust_test`.

#### Conclusion
1. Current saturation was causing a drop in observed speed.
2. Higher amperage power supply is to be used.
3. Quadratic treadline fit for 0-40% speed was 

    $$\textit{Thrust (in g)} = 0.036*\textit{Speed}_{\%}^2 + 1.5723*\textit{Speed}_{\%}+0.6373$$ 

    The quadratic and linear part have significant contribution to the calculated value. The constant contributed to <10\% of the calculated value.

### repeating Test 3 with higher amperage power supply

Acrylic broke and the motor flew in air. Luckily the wire came loose and the motor stopped.

DO NOT USE MOTOR WITH speed > 30% !!!!!
