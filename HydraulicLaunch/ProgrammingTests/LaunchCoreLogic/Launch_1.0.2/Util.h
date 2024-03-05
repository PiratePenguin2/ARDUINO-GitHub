#pragma once

class Util {
public:
  class Button {
  public:
    Button(int pin);
    bool isPressed();
    int buttonPin;
  };

  class Led {
  public:
    Led();
    void turnOn(int ledPin);
    void turnOff(int ledPin);
    void blink(int ledPin, int onTime, int offTime);

  private:
    bool isOn;
  };
};
