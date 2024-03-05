#pragma once
#include <Arduino.h>

/*
 * Button Class
 * -------------
 * Represents a simple button with methods to check if it's pressed.
 */
class Util {
public:
  class Button {
  public:
    Button(int pin);
    bool isPressed();
    int buttonPin;
  };

  /*
   * Led Class
   * -----------
   * Represents an LED with methods to control its state.
   */
  class Led {
  public:
    Led(int pin);
    void turnOn();
    void turnOff();
    void blink(int onTime, int offTime);

  private:
    bool isOn;
    int ledPin;
  };

  /*
   * HallEffectSensor Class
   * -----------------------
   * Represents a Hall Effect Sensor with methods to read its state.
   */
  class HallEffectSensor {
  public:
    HallEffectSensor(int pin);
    int readSensorValue();

  private:
    int sensorPin;
  };
};
