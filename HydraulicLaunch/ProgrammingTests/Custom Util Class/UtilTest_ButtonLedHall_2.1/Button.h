// Button.h
#ifndef BUTTON_H
#define BUTTON_H
#include "Timer.h"
#include "Led.h"

class Button {
  public:
    enum ButtonMode {
      PUSH,
      TAP,
      TAP_RELEASE,
      LATCH
    };
    
    Button(int pin);
    Button(int pin, ButtonMode m);
    void controlLed(Led& led);
    void controlLed(Led& led, Led::LedMode ledM);
    bool isPressed();
    bool isEnabled();
  
  private:
    ButtonMode mode;
    Timer buttonDelay;
    int buttonPin;
    bool enabled;
    int buttonLatchDelay = 500;
    bool lastPushed = true;
};
  
#endif // BUTTON_H
