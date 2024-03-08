// PT_Util::Led implementation
#include <Arduino.h>
#include "Led.h"
#include "Timer.h"

Led::Led(int pin) : ledPin(pin) {
  state = OFF;
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

Led::Led(int pin, int newState) : ledPin(pin), state(newState) {
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

void Led::update() {
  switch (state) {
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
        state = ON;
      else
        state = OFF;
      break;
    case BLINK:
      if (blinkTimer.timerFinished())
      {
        Serial.println(blinkTimer.getElapsedTime());
        if (!isOn)
        {
          isOn = true;
          digitalWrite(ledPin, HIGH);
          blinkTimer.setTimer(onTime);
        }
        else
        {
          isOn = false;
          digitalWrite(ledPin, LOW);
          blinkTimer.setTimer(offTime);
          Serial.println();
        }
      }
      break;
    default:
      Serial.println("ERROR: Unknown LED State: " + state);
      break;
  }
}

void Led::setState(int newState) {
  state = newState;
  //update();
}

void Led::setState(int newState, int newOnTime) {
  state = newState;
  onTime = newOnTime;
  offTime = newOnTime;
  //update();
}

void Led::setState(int newState, int newOnTime, int newOffTime) {
  state = newState;
  onTime = newOnTime;
  offTime = newOffTime;
  //update();
}

void Led::turnOn() {
  state = ON;
  update();
}

void Led::turnOff() {
  state = OFF;
  update();
}

int Led::getState() {
    return state;
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
