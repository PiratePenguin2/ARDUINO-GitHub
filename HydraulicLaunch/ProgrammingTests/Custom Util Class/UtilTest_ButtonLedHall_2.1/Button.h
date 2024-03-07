// Button.h
#ifndef BUTTON_H
#define BUTTON_H
#include "Timer.h"

class Button {
  #define PUSH          000
  #define TAP           001
  #define TAP_RELEASE   002
  #define LATCH         003

  /*#define NO              100
  #define NORMALLY_OPEN   101
  #define NC              102
  #define NORMALLY_CLOSED 103*/
  public:
    Button(int pin);
    Button(int pin, int mode);
    //void controlLed(Led led);
    //void controlLed(Led led, int ledMode);
    bool isPressed();
    bool isEnabled();
  private:
    int buttonPin;
    bool enabled;
    int buttonLatchDelay = 500;
    int mode;
    bool lastPushed = true;
    Timer buttonDelay; // Declare buttonLatch as a member variable
};
  
#endif // BUTTON_H
