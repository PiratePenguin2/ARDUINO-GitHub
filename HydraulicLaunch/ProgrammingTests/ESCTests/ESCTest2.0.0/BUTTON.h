// BUTTON.h
#ifndef BUTTON_h
#define BUTTON_h

#include <Arduino.h>

class Button {
private:
  int buttonPin;

public:
  Button(int pin);
  bool isPressed();
};

#endif
