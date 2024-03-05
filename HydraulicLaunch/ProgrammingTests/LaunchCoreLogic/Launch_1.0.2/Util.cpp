#include "Util.h"
#include <Arduino.h>

/*
 * BUTTON
 */

Util::Button::Button(int pin) : buttonPin(pin) {
  pinMode(buttonPin, INPUT);
}

bool Util::Button::isPressed() {
  return digitalRead(buttonPin) == LOW;
}


/*
 * LED
 */

Util::Led::Led(int pin) : ledPin(pin) {
  pinMode(ledPin, OUTPUT); // Set the LED pin as OUTPUT in the constructor
  isOn = false;
}

void Util::Led::turnOn(int ledPin) {
  isOn = true;
  digitalWrite(ledPin, HIGH);
}

void Util::Led::turnOff(int ledPin) {
  isOn = false;
  digitalWrite(ledPin, LOW);
}

void Util::Led::blink(int ledPin, int onTime, int offTime) {
  digitalWrite(ledPin, HIGH);
  delay(onTime);
  digitalWrite(ledPin, LOW);
  delay(offTime);
}


/*
 * Hall Effect Sensor
 */
 
Util::HallEffectSensor::HallEffectSensor(int pin) : sensorPin(pin) {
  pinMode(sensorPin, INPUT);
}

int Util::HallEffectSensor::readSensorValue() {
  return digitalRead(sensorPin);
}
