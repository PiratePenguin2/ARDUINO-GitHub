#include "ServoHelper.h"
#include <Wire.h>

ServoHelper::ServoHelper() : ServoHelper(0) {
  // Call the other constructor with default parameter value
}

ServoHelper::ServoHelper(uint8_t num) {
  servoNum = num;
  SERVOMIN = 150;
  SERVOMAX = 600;
  SERVO_FREQ = 50;
}

void ServoHelper::begin() {
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);
}

void ServoHelper::setAngle(uint8_t angle) {
  uint16_t pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(servoNum, 0, pulse);
}
