// Led.cpp
#include <Arduino.h>
#include "Led.h"
#include "Timer.h"

Led::Led(int pin) : ledPin(pin), ledState(OFF), ledMode(NO) {
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

Led::Led(int pin, LedState newState) : ledPin(pin), ledState(newState), ledMode(NO) {
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

Led::Led(int pin, LedState ledS, LedMode ledM) : ledPin(pin), ledState(ledS), ledMode(ledM) {
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

void Led::update() {
  switch (ledState) {
    case ON:
      isOn = true;
      digitalWrite(ledPin, HIGH);
      break;
    case OFF:
      isOn = false;
      digitalWrite(ledPin, LOW);
      break;
    case FLIP:
      isOn = !isOn;
      digitalWrite(ledPin, isOn ? HIGH : LOW);
      if (isOn)
        ledState = ON;
      else
        ledState = OFF;
      break;
    case BLINK:
      if (blinkTimer.timerFinished()) {
        Serial.println(blinkTimer.getElapsedTime());
        if (!isOn) {
          isOn = true;
          digitalWrite(ledPin, HIGH);
          blinkTimer.setTimer(onTime);
        } else {
          isOn = false;
          digitalWrite(ledPin, LOW);
          blinkTimer.setTimer(offTime);
          Serial.println();
        }
      }
      break;
    default:
      Serial.println("ERROR: Unknown LED State: " + static_cast<int>(ledState));
      break;
  }
}

void Led::setLedState(LedState ledS) {
  ledState = ledS;
}

void Led::setLedState(LedState ledS, int newOnTime) {
  ledState = ledS;
  onTime = newOnTime;
  offTime = newOnTime;
}

void Led::setLedState(LedState ledS, int newOnTime, int newOffTime) {
  ledState = ledS;
  onTime = newOnTime;
  offTime = newOffTime;
}

void Led::turnOn() {
  ledState = ON;
}

void Led::turnOff() {
  ledState = OFF;
}

int Led::getLedState() {
  return static_cast<int>(ledState);
}

bool Led::getLampState() {
  return isOn;
}

Led::LedMode Led::getLedMode() const {
  return ledMode;
}

void Led::setLedMode(LedMode mode) {
  ledMode = mode;
}
