#include "PTservo.h"
#include <Arduino.h>

PTservo::PTservo(Adafruit_PWMServoDriver& driver, uint8_t channel) : pwmDriver(driver), pwmChannel(channel) {}

void PTservo::write(int angle) {
  // Constrain angle to range 0 to 180
  angle = constrain(angle, 0, 180);

  int pwmValue = map(angle, 0, 180, SERVOMIN, SERVOMAX);

  pwmDriver.setPWM(pwmChannel, 0, pwmValue);
}
