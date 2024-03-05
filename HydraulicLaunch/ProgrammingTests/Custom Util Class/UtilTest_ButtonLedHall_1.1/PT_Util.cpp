#include "PT_Util.h"
#include <Arduino.h>

// PT_Util::Timer implementation
PT_Util::Timer::Timer() {
}

PT_Util::Timer::Timer(int mSec) {
  setTimer(mSec);
}

void PT_Util::Timer::setTimer(int mSec) {
  duration = mSec;
  startTime = millis();
}

unsigned long PT_Util::Timer::getStartTime() {
  return startTime;
}

unsigned long PT_Util::Timer::getEndTime() {
  return startTime + duration;  //
}

int PT_Util::Timer::getElapsedTime() {
  return millis() - startTime;
}

int PT_Util::Timer::getTimeLeft() {
  int timeLeft = getEndTime() - getElapsedTime();
  if (timeLeft <= 0) {
    return 0; // Timer finished
  } else {
    return timeLeft;
  }
}

bool PT_Util::Timer::timerFinished() {
  return (getEndTime() - getElapsedTime() <= 0);
}

// PT_Util::Stopwatch implementation
PT_Util::Stopwatch::Stopwatch() : startTime(0) {}

void PT_Util::Stopwatch::restartStopwatch() {
  startTime = millis();
}

unsigned long PT_Util::Stopwatch::getTimeElapsed() {
  return millis() - startTime;
}

// PT_Util::Button implementation
PT_Util::Button::Button(int pin) : buttonPin(pin) {
  pinMode(buttonPin, INPUT);
  mode = PUSH;  // Set default mode
}

PT_Util::Button::Button(int pin, int mode) : buttonPin(pin), mode(mode) {
  pinMode(buttonPin, INPUT);
}

bool PT_Util::Button::isPressed() {
  return (digitalRead(buttonPin) == LOW);
}

bool PT_Util::Button::isEnabled() {
  bool isPushed = isPressed();
  switch (mode) {
    case PUSH:
      enabled = isPushed;
    case TAP:
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
  };
  return enabled;
}

// PT_Util::Led implementation
PT_Util::Led::Led(int pin) : ledPin(pin) {
  isOn = false;
  pinMode(ledPin, OUTPUT);
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

// PT_Util::HallEffectSensor implementation
PT_Util::HallEffectSensor::HallEffectSensor(int pin) : sensorPin(pin) {
  pinMode(sensorPin, INPUT);
}

int PT_Util::HallEffectSensor::readSensorValue() {
  return digitalRead(sensorPin);
}
