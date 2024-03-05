#include "PT_Util.h"
#include <Arduino.h>

PT_Util::Button::Button(int pin) : buttonPin(pin) {
  pinMode(buttonPin, INPUT);
}

bool PT_Util::Button::isPressed() {
  return digitalRead(buttonPin) == LOW;
}

PT_Util::Led::Led(int pin) : ledPin(pin) {
  pinMode(ledPin, OUTPUT);
  isOn = false;
}

void PT_Util::Led::turnOn() {
  isOn = true;
  digitalWrite(ledPin, HIGH);
}

void PT_Util::Led::turnOff() {
  isOn = false;
  digitalWrite(ledPin, LOW);
}

void PT_Util::Led::blink(int onTime, int offTime) {
  digitalWrite(ledPin, HIGH);
  delay(onTime);
  digitalWrite(ledPin, LOW);
  delay(offTime);
}

bool PT_Util::Led::isON() {
  return isOn;
}

PT_Util::HallEffectSensor::HallEffectSensor(int pin) : sensorPin(pin) {
  pinMode(sensorPin, INPUT);
}

int PT_Util::HallEffectSensor::readSensorValue() {
  return digitalRead(sensorPin);
}
