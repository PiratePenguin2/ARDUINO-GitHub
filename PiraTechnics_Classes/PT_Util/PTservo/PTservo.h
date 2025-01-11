#ifndef PTSERVO_H
#define PTSERVO_H

#include <Adafruit_PWMServoDriver.h>

class PTservo {
  // Define the channel for the servo (0-15) 320 mid, +-225
  #define SERVOMIN  95 // This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX  545 // This is the 'maximum' pulse length count (out of 4096)

public:
  PTservo(Adafruit_PWMServoDriver& driver, uint8_t channel);

  void write(int angle);

private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
};

#endif // PTSERVO_H
