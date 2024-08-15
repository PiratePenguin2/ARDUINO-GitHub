#ifndef MY_PCF8574_H
#define MY_PCF8574_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class MyPCF8574 : public Adafruit_PWMServoDriver {
public:
    MyPCF8574(uint8_t addr) : Adafruit_PWMServoDriver(addr) {}
    uint8_t read8();
};

#endif
