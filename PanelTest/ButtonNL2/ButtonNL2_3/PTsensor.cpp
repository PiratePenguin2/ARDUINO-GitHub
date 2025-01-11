#include "PTsensor.h"
#include <Wire.h>

Sensor::Sensor() {}

void Sensor::attach(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
}

/*void Sensor::update() {  
  oldState = currentState;
  currentState = digitalRead(_pin);
}*/

bool Sensor::read() {
  return _currentState;
}

/*bool Sensor::isTripped() {
  if (oldState == HIGH && currentState == LOW)
  {
    return true;
  }
  return false;
}*/

/*bool Sensor::isUntripped() {
  if (_oldState == LOW && _currentState == HIGH)
  {
    return true;
  }
  return false;
}*/

void Sensor::count() {
  _count += 1;
}

void Sensor::count(int count) {
  _count = count;
}

int Sensor::getCount() {
  return _count;
}



void Sensor::update() {
  int stableState = digitalRead(_pin);
  delay(10);  // Debounce delay
  if (stableState == digitalRead(_pin)) {
    if (_currentState != stableState) {
      _oldState = _currentState;
      _currentState = stableState;

      Serial.print("Pin: "); Serial.print(_pin);
      Serial.print(" State Changed - OldState: "); Serial.print(_oldState);
      Serial.print(", CurrentState: "); Serial.println(_currentState);
    }
  }
}



bool Sensor::isTripped() {
  return (_oldState == LOW && _currentState == HIGH);
}

bool Sensor::isUntripped() {
  return (_oldState == HIGH && _currentState == LOW);
}



bool Sensor::changed() {
  return _oldState != _currentState;
}
