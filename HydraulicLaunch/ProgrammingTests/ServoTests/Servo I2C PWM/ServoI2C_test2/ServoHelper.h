#ifndef PT_UTIL_SERVO_H
#define PT_UTIL_SERVO_H

#include <Adafruit_PWMServoDriver.h>

class ServoHelper {
  public:
    ServoHelper();
    ServoHelper(uint8_t num);
    void begin();
    void setAngle(uint8_t angle);
    
  private:
    Adafruit_PWMServoDriver pwm;
    uint8_t servoNum;
    uint16_t SERVOMIN;
    uint16_t SERVOMAX;
    uint16_t SERVO_FREQ;
};

#endif
