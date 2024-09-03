#include "DC_Motor.h"

DC_Motor::DC_Motor(Adafruit_PWMServoDriver* pwm, uint8_t pinA, uint8_t pinB)
    : _pwm(pwm), _pinA(pinA), _pinB(pinB) {
    _pwm->setPWM(_pinA, 0, 0);
    _pwm->setPWM(_pinB, 0, 0);
}

void DC_Motor::setSpeed(int16_t speed) {
    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;

    uint16_t pwmValue = map(abs(speed), 0, 100, 0, 4095);

    if (speed > 0) {
        setMotorPWM(_pinA, pwmValue);
        setMotorPWM(_pinB, 0);
    } else if (speed < 0) {
        setMotorPWM(_pinA, 0);
        setMotorPWM(_pinB, pwmValue);
    } else {
        setMotorPWM(_pinA, 0);
        setMotorPWM(_pinB, 0);
    }
}

void DC_Motor::setMotorPWM(uint8_t pin, uint16_t pwm) {
    _pwm->setPWM(pin, 0, pwm);
}
