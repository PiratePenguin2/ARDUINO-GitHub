#include "Util.h"
#include <Arduino.h>

Util::Button::Button(int pin) : buttonPin(pin) {
  pinMode(buttonPin, INPUT);
}

bool Util::Button::isPressed() {
  return digitalRead(buttonPin) == HIGH;
}

Util::Led::Led() {
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
