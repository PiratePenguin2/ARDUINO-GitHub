#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "MotorServoControl.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
MotorServoControl control(pwm, 0, 1, 8);

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setup started");

  pwm.begin();
  pwm.setPWMFreq(1600);
  
  Serial.println("PCA9685 initialized with 1.6 kHz frequency");
}

void loop() {
  Serial.println("Testing Motors and Servo");

  control.setMotorSpeed(50, -50);
  delay(2000);

  control.setMotorSpeed(0, 0);
  delay(2000);

  control.setServoAngle(90);
  delay(2000);

  control.setServoAngle(45);
  delay(2000);

  control.setServoAngle(135);
  delay(2000);
}
