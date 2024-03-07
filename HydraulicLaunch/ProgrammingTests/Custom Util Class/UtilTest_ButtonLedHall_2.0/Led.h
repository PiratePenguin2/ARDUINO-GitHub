// Led.h
#ifndef LED_H
#define LED_H
#include "Timer.h"

class Led {
    #define ON 0
    #define OFF 1
    #define FLIP 2
    #define BLINK 3
  public:
    Led(int pin);
    Led(int pin, int state);
    void update();
    void setState(int state);
    void setState(int state, int onTime);
    void setState(int state, int onTime, int offTime);
    void turnOn();
    void turnOff();
    int getState();
    bool getLampState();
  private:
    bool isOn;
    int ledPin;
    int onTime;
    int offTime;
    int state;
    Timer blinkTimer; // Declare blinkTimer as a member variable
};
  
#endif // LED_H
