# Servo Sonar Scanner

An Arduino-based sonar system that mounts an HC-SR04 ultrasonic sensor on a servo motor to sweep and detect objects. Detected objects are visualized on a real-time radar display built in Processing.

## Modes
- **Mode 0:** Continuous sweep with proximity alerts
- **Mode 1:** Sweep pauses when object detected, resumes when clear
- **Mode 2:** Manual joystick control of servo angle

## Controls
- **Button tap:** cycle through modes
- **Joystick:** controls servo angle in mode 2
- **LED:** turns on within 20cm
- **Buzzer:** turns on within 10cm

## Components
- Arduino Uno
- HC-SR04 ultrasonic sensor
- 9g servo motor
- Joystick module
- 7-segment display (5161AS)
- LED
- Passive buzzer
- Tactile button
- 220R resistor x3
- 10K resistor

## Wiring
| Component | Arduino Pin |
|---|---|
| Servo signal | 11 |
| SR04 TRIG | 12 |
| SR04 ECHO | 13 |
| Buzzer | A1 |
| LED | 9 |
| Button | 2 |
| Joystick X | A0 |
| 7-seg a-g | 3-10 |

## Software
- Arduino IDE — upload `ServoSonarScanner.ino`
- Processing — run `radar.pde`, update COM port to match your Arduino

## Skills
Arduino, Servo Control, Ultrasonic Sensing, Serial Communication, Processing Visualization, Non-blocking Timing, State Machine