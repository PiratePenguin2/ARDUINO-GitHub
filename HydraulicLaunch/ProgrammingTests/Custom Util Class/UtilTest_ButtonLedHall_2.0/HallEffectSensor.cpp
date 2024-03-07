// PT_Util::HallEffectSensor implementation
PT_Util::HallEffectSensor::HallEffectSensor(int pin) : sensorPin(pin) {
  pinMode(sensorPin, INPUT);
}

int PT_Util::HallEffectSensor::readSensorValue() {
  return digitalRead(sensorPin);
}
