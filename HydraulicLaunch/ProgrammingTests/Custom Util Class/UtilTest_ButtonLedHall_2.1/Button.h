// Button.h
#ifndef BUTTON_H
#define BUTTON_H
#include "Timer.h"

class Button {
  /*#define PUSH          000
  #define TAP           001
  #define TAP_RELEASE   002
  #define LATCH         003*/

  /*#define NO              100
  #define NORMALLY_OPEN   101
  #define NC              102
  #define NORMALLY_CLOSED 103*/
  public:
    enum ButtonMode {
      PUSH,
      TAP,
      TAP_RELEASE,
      LATCH
    };
    
    Button(int pin);
    Button(int pin, ButtonMode m);
    //void controlLed(Led led);
    //void controlLed(Led led, int ledMode);
    bool isPressed();
    bool isEnabled();
  private:
    int buttonPin;
    bool enabled;
    int buttonLatchDelay = 500;
    ButtonMode mode;
    bool lastPushed = true;
    Timer buttonDelay; // Declare buttonLatch as a member variable
};
  
#endif // BUTTON_H
