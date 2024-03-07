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
  return startTime + duration;
}

unsigned long PT_Util::Timer::getElapsedTime() {
  unsigned long currentTime = millis();
  if (currentTime >= startTime) {
    return currentTime - startTime;
  } else {
    // Handle rollover
    return (4294967295UL - 1 - startTime) + currentTime + 1;
  }
}

unsigned long PT_Util::Timer::getTimeLeft() {
  unsigned long elapsedTime = getElapsedTime();
  if (elapsedTime >= duration) {
    return 0; // Timer finished
  } else {
    return duration - elapsedTime;
  }
}

bool PT_Util::Timer::timerFinished() {
  unsigned long currentTime = millis();
  if (currentTime >= startTime) {
    return (currentTime - startTime >= duration);
  } else {
    // Handle rollover
    return (4294967295UL - startTime + currentTime >= duration);
  }
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
      break;
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
  state = OFF;
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

PT_Util::Led::Led(int pin, int newState) : ledPin(pin), state(newState) {
  isOn = false;
  pinMode(ledPin, OUTPUT);
}

void PT_Util::Led::update() {
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

void PT_Util::Led::setState(int newState) {
  state = newState;
  //update();
}

void PT_Util::Led::setState(int newState, int newOnTime) {
  state = newState;
  onTime = newOnTime;
  offTime = newOnTime;
  //update();
}

void PT_Util::Led::setState(int newState, int newOnTime, int newOffTime) {
  state = newState;
  onTime = newOnTime;
  offTime = newOffTime;
  //update();
}

void PT_Util::Led::turnOn() {
  state = ON;
  update();
}

void PT_Util::Led::turnOff() {
  state = OFF;
  update();
}

int PT_Util::Led::getState() {
    return state;
}

bool PT_Util::Led::getLampState() {
  return isOn;
}

// PT_Util::HallEffectSensor implementation
PT_Util::HallEffectSensor::HallEffectSensor(int pin) : sensorPin(pin) {
  pinMode(sensorPin, INPUT);
}

int PT_Util::HallEffectSensor::readSensorValue() {
  return digitalRead(sensorPin);
}
