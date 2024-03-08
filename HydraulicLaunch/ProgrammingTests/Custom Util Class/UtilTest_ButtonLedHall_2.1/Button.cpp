// Button.cpp
#include "Button.h"
#include "Timer.h"
#include "Led.h"
#include <Arduino.h>

Button::Button(int pin) : buttonPin(pin), mode(PUSH), enabled(false) {
  pinMode(buttonPin, INPUT);
}

Button::Button(int pin, ButtonMode m) : buttonPin(pin), mode(m), enabled(false) {
  pinMode(buttonPin, INPUT);
}

void Button::controlLed(Led& led) {
  led.setLedMode(Led::NO);
  isEnabled() ? led.turnOn() : led.turnOff();
}

void Button::controlLed(Led& led, Led::LedMode ledM) {
  led.setLedMode(ledM);
  switch (led.getLedMode()) {
    case Led::NO:
    case Led::NORMALLY_OPEN:
      isEnabled() ? led.turnOn() : led.turnOff();
      break;
    case Led::NC:
    case Led::NORMALLY_CLOSED:
      isEnabled() ? led.turnOff() : led.turnOn();
      break;
    default:
      Serial.println("Unknown Button-Controlled Led Mode: " + led.getLedMode());
      break;
  }
}

bool Button::isPressed() {
  return (digitalRead(buttonPin) == LOW);
}

bool Button::isEnabled() {
  bool isPushed = isPressed();
  switch (mode) {
    case PUSH:
      enabled = isPushed;
      break;
    case TAP:
      if (isPushed && buttonDelay.timerFinished()) {
        enabled = true;
        buttonDelay.setTimer(500);
      } else {
        enabled = false;
      }
      break;
    case TAP_RELEASE:
      if (isPushed && buttonDelay.timerFinished()) {
        enabled = true;
        buttonDelay.setTimer(500);
      } else {
        enabled = false;
      }
      break;
    case LATCH:
      if (isPushed && buttonDelay.timerFinished()) {
        enabled = !enabled;
        buttonDelay.setTimer(500);
      }
      break;
    default:
      Serial.println("Unknown Button Mode: " + mode);
      break;
  }
  return enabled;
}
