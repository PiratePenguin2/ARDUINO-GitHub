#ifndef PTDCMOTOR_H
#define PTDCMOTOR_H

#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_PCF8574.h>

class PTdcmotor {
public:
  PTdcmotor(Adafruit_PWMServoDriver& driver, uint8_t channel);

  void initializePins(uint8_t in1, uint8_t in2);
  void initializePins(uint8_t in1, uint8_t in2, Adafruit_PCF8574& pcf);

  void write(int speed);

private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
  Adafruit_PCF8574* pcfBoard = nullptr;  // Use a pointer for the PCF8574 instance
  uint8_t pin1;
  uint8_t pin2;
  bool usePcf = false;  // Flag to check whether to use PCF8574 or regular digital pins
};

#endif // PTDCMOTOR_H
