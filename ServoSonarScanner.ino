#include <Servo.h>

const int servoPin = 11;
const int trigPin = 12;
const int echoPin = 13;
const int buzzerPin = A1;
const int ledPin = 9;
const int buttonPin = 2;
const int joyXPin = A0;
const int A = 3;
const int B = 4;
const int C = 5;
const int D = 6;
const int E = 7;
const int F = 8;
const int G = 10;

// Servo
Servo myServo;
int servoAngle = 90;
int sweepDir = 1;

// Mode
int mode = 0;

// Button
int buttonState = LOW;
int lastButtonState = LOW;

// Proximity
int distance = 0;
int ledRange = 20;
int buzzRange = 10;

// Joystick
int deadZone = 100;

// Timing
int sweepSpeed = 25;
int pingDelay = 50;
int joySpeed = 15;
unsigned long now = 0;
unsigned long lastSweepTime = 0;
unsigned long lastPingTime = 0;
unsigned long lastJoyTime = 0;

// Function declarations
long getDistance();
void displayMode(int m);
void zero();
void one();
void two();

void setup() {
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  myServo.write(servoAngle);
  displayMode(mode);
  Serial.begin(9600);
}

void loop() {
  now = millis();

  // Button
  buttonState = digitalRead(buttonPin);
  bool risingEdge = (buttonState == HIGH && lastButtonState == LOW);

  if (risingEdge) {
    mode = (mode + 1) % 3;
    displayMode(mode);
  }

  // Ping
  if (now - lastPingTime >= pingDelay) {
    lastPingTime = now;
    distance = getDistance();
    Serial.print(servoAngle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

  // Buzzer
  if (distance > 0 && distance <= buzzRange) {
    tone(buzzerPin, 1000);
  } else {
    noTone(buzzerPin);
  }

  // LED
  if (distance > 0 && distance <= ledRange) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Mode 0 - Sweep
  if (mode == 0) {
    if (now - lastSweepTime >= sweepSpeed) {
      lastSweepTime = now;
      servoAngle += sweepDir;
      if (servoAngle >= 180 || servoAngle <= 0) sweepDir = -sweepDir;
      myServo.write(servoAngle);
    }
  }
  // Mode 1 - Pause on detection
  else if (mode == 1) {
    if (distance == 0 || distance > ledRange) {
      if (now - lastSweepTime >= sweepSpeed) {
        lastSweepTime = now;
        servoAngle += sweepDir;
        if (servoAngle >= 180 || servoAngle <= 0) sweepDir = -sweepDir;
        myServo.write(servoAngle);
      }
    }
  }
  // Mode 2 - Joystick
  else if (mode == 2) {
    if (now - lastJoyTime >= joySpeed) {
      lastJoyTime = now;
      int joyVal = analogRead(joyXPin);
      if (joyVal > 512 + deadZone) {
        servoAngle = constrain(servoAngle + 1, 0, 180);
        myServo.write(servoAngle);
      } else if (joyVal < 512 - deadZone) {
        servoAngle = constrain(servoAngle - 1, 0, 180);
        myServo.write(servoAngle);
      }
    }
  }

  lastButtonState = buttonState;
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 10000);
  return duration * 0.034 / 2;
}

void displayMode(int m) {
  if (m == 0) zero();
  else if (m == 1) one();
  else if (m == 2) two();
}

void zero() {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void one() {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void two() {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}