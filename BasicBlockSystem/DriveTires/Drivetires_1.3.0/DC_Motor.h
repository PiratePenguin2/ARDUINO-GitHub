#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class DC_Motor {
public:
    DC_Motor(Adafruit_PWMServoDriver* pwm, uint8_t pinA, uint8_t pinB);
    void setSpeed(int16_t speed);  // Speed from -100 to 100

private:
    Adafruit_PWMServoDriver* _pwm;
    uint8_t _pinA;
    uint8_t _pinB;
    void setMotorPWM(uint8_t pin, uint16_t pwm);
};

#endif
