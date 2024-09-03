#include "PTdcmotor.h"
#include <Arduino.h>

PTdcmotor::PTdcmotor(Adafruit_PWMServoDriver& driver, uint8_t channel) : pwmDriver(driver), pwmChannel(channel) {}

void PTdcmotor::initializePins(uint8_t in1, uint8_t in2) {
  pin1 = in1;
  pin2 = in2;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  usePcf = false;
}

void PTdcmotor::initializePins(uint8_t in1, uint8_t in2, Adafruit_PCF8574& pcf) {
  pin1 = in1;
  pin2 = in2;
  pcfBoard = &pcf;
  pcfBoard->pinMode(pin1, OUTPUT);
  pcfBoard->pinMode(pin2, OUTPUT);
  usePcf = true;
}

void PTdcmotor::write(int speed) {
  // Constrain speed to range -100 to 100
  speed = constrain(speed, -100, 100);

  // Set corresponding IN pins
  if (usePcf) {
    pcfBoard->digitalWrite(pin1, speed > 0 ? HIGH : LOW);
    pcfBoard->digitalWrite(pin2, speed < 0 ? HIGH : LOW);
  } else {
    digitalWrite(pin1, speed > 0 ? HIGH : LOW);
    digitalWrite(pin2, speed < 0 ? HIGH : LOW);
  }
  
  // Map pulse width to PCA9685 PWM range (0-4095)
  int pwmValue = map(abs(speed), 0, 100, 0, 4095);

  pwmDriver.setPWM(pwmChannel, 0, pwmValue);
}
