#include "Sensor.h"
#include <Wire.h>

Sensor::Sensor() : _pcf(nullptr), _usingPCF(false) {}

void Sensor::attach(uint8_t pin) {
  _pin = pin;
  _usingPCF = false;
  pinMode(_pin, INPUT);
}

void Sensor::attach(uint8_t pin, Adafruit_PCF8574 &pcf) {
  _pin = pin;
  _pcf = &pcf;
  _usingPCF = true;
  _pcf->pinMode(_pin, INPUT);
}

bool Sensor::read() {
  if (_usingPCF) {
    _pcf->begin();
    return _pcf->digitalRead(_pin); // Assuming active-low for buttons/sensors
  } else {
    return digitalRead(_pin);
  }
}

int Sensor::analogRead() {
  if (_usingPCF) {
    // Analog reading is not possible through PCF8574; return -1 or handle accordingly
    return -1;
  } else {
    return ::analogRead(_pin);
  }
}
