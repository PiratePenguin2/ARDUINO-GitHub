// LED.h
#ifndef LED_h
#define LED_h

#include <Arduino.h>

class LED {
private:
  int ledPin;

public:
  LED(int pin);
  void turnOn();
  void turnOff();
  void blink(int onDuration, int offDuration);
};

#endif
