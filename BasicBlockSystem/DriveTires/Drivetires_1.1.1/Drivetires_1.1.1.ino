#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PCA9685 object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Pin definitions for Motor 1
const int in1Pin = 2;  // IN1 on H-Bridge
const int in2Pin = 3;  // IN2 on H-Bridge

// Pin definitions for Motor 2
const int in3Pin = 4;  // IN3 on H-Bridge
const int in4Pin = 5;  // IN4 on H-Bridge

// Motor speed (0-4095 for PCA9685)
int motorSpeed1 = 4095; // Set Motor 1 to full speed
int motorSpeed2 = 4095; // Set Motor 2 to full speed

void setup() {
  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(1600);  // Set frequency to 1.6 kHz

  // Set up the pin modes for Motor 1
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  // Set up the pin modes for Motor 2
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // Start with motors stopped
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  pwm.setPWM(0, 0, 0); // Motor 1 stop

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  pwm.setPWM(1, 0, 0); // Motor 2 stop
}

void loop() {
  // Motor 1 Forward
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  pwm.setPWM(0, 0, motorSpeed1);  // Set Motor 1 speed

  // Motor 2 Forward
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  pwm.setPWM(1, 0, motorSpeed2);  // Set Motor 2 speed

  delay(2000);  // Run forward for 2 seconds

  // Stop both motors
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  pwm.setPWM(0, 0, 0);  // Motor 1 stop

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  pwm.setPWM(1, 0, 0);  // Motor 2 stop

  delay(1000);  // Stop for 1 second

  // Motor 1 Backward
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  pwm.setPWM(0, 0, motorSpeed1);  // Set Motor 1 speed

  // Motor 2 Backward
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  pwm.setPWM(1, 0, motorSpeed2);  // Set Motor 2 speed

  delay(2000);  // Run backward for 2 seconds

  // Stop both motors
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  pwm.setPWM(0, 0, 0);  // Motor 1 stop

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  pwm.setPWM(1, 0, 0);  // Motor 2 stop

  delay(1000);  // Stop for 1 second
}
