// PT_Util::HallEffectSensor implementation
#include <Arduino.h>
#include "HallEffectSensor.h"

HallEffectSensor::HallEffectSensor(int pin) : sensorPin(pin) {
  pinMode(sensorPin, INPUT);
}

int HallEffectSensor::readSensorValue() {
  return digitalRead(sensorPin);
}
