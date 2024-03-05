#pragma once
#include <Arduino.h>

class PT_Util {
public:
  class Button {
  public:
    Button(int pin);
    bool isPressed();
    int buttonPin;
  };

  class Led {
  public:
    Led(int pin);
    void turnOn();
    void turnOff();
    void blink(int onTime, int offTime);
    bool isON(); // New function
  private:
    bool isOn;
    int ledPin;
  };

  class HallEffectSensor {
  public:
    HallEffectSensor(int pin);
    int readSensorValue();
  private:
    int sensorPin;
  };
};
